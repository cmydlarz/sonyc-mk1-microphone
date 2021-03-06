/*******************************************************************************
* File Name: I2CHW_PM.c
* Version 3.30
*
* Description:
*  This file provides Low power mode APIs for I2C component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CHW_PVT.h"

I2CHW_BACKUP_STRUCT I2CHW_backup =
{
    I2CHW_DISABLE, /* enableState */

    #if(I2CHW_FF_IMPLEMENTED)
        I2CHW_DEFAULT_XCFG,  /* xcfg */
        I2CHW_DEFAULT_CFG,   /* cfg  */

        #if(I2CHW_MODE_SLAVE_ENABLED)
            I2CHW_DEFAULT_ADDR, /* addr */
        #endif /* (I2CHW_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            LO8(I2CHW_DEFAULT_DIVIDE_FACTOR),  /* div */
        #else
            LO8(I2CHW_DEFAULT_DIVIDE_FACTOR), /* div1 */
            HI8(I2CHW_DEFAULT_DIVIDE_FACTOR), /* div2 */
        #endif /* (CY_PSOC5A) */

    #else  /* (I2CHW_UDB_IMPLEMENTED) */
        I2CHW_DEFAULT_CFG,    /* control */

        #if(CY_UDB_V0)
            I2CHW_INT_ENABLE_MASK, /* aux_ctl */

            #if(I2CHW_MODE_SLAVE_ENABLED)
                I2CHW_DEFAULT_ADDR, /* addr_d0 */
            #endif /* (I2CHW_MODE_SLAVE_ENABLED) */
        #endif /* (CY_UDB_V0) */
    #endif /* (I2CHW_FF_IMPLEMENTED) */

    #if(I2CHW_TIMEOUT_ENABLED)
        I2CHW_DEFAULT_TMOUT_PERIOD,
        I2CHW_DEFAULT_TMOUT_INTR_MASK,

        #if(I2CHW_TIMEOUT_PRESCALER_ENABLED && CY_UDB_V0)
            I2CHW_DEFAULT_TMOUT_PRESCALER_PRD,
        #endif /* (I2CHW_TIMEOUT_PRESCALER_ENABLED) */

    #endif /* (I2CHW_TIMEOUT_ENABLED) */
};

#if((I2CHW_FF_IMPLEMENTED) && (I2CHW_WAKEUP_ENABLED))
    volatile uint8 I2CHW_wakeupSource;
#endif /* ((I2CHW_FF_IMPLEMENTED) && (I2CHW_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: I2CHW_SaveConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: disables I2C Master(if was enabled before go
*  to sleep), enables I2C backup regulator. Waits while on-going transaction be
*  will completed and I2C will be ready go to sleep. All incoming transaction
*  will be NACKed till power down will be asserted. The address match event
*  wakes up the chip.
*  Wakeup on address match disabled: saves I2C configuration and non-retention
*  register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  I2CHW_backup - used to save component configuration and
*       none-retention registers before enter sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void I2CHW_SaveConfig(void) 
{
    #if(I2CHW_FF_IMPLEMENTED)
        #if(I2CHW_WAKEUP_ENABLED)
            uint8 enableInterrupts;
        #endif /* (I2CHW_WAKEUP_ENABLED) */

        /* Store regiters in either Sleep mode */
        I2CHW_backup.cfg  = I2CHW_CFG_REG;
        I2CHW_backup.xcfg = I2CHW_XCFG_REG;

        #if(I2CHW_MODE_SLAVE_ENABLED)
            I2CHW_backup.addr = I2CHW_ADDR_REG;
        #endif /* (I2CHW_MODE_SLAVE_ENABLED) */

        #if(CY_PSOC5A)
            I2CHW_backup.clkDiv   = I2CHW_CLKDIV_REG;
        #else
            I2CHW_backup.clkDiv1  = I2CHW_CLKDIV1_REG;
            I2CHW_backup.clkDiv2  = I2CHW_CLKDIV2_REG;
        #endif /* (CY_PSOC5A) */

        #if(I2CHW_WAKEUP_ENABLED)
            /* Need to disable Master */
            I2CHW_CFG_REG &= ((uint8) ~I2CHW_ENABLE_MASTER);

            /* Enable the I2C regulator backup */
            enableInterrupts = CyEnterCriticalSection();
            I2CHW_PWRSYS_CR1_REG |= I2CHW_PWRSYS_CR1_I2C_REG_BACKUP;
            CyExitCriticalSection(enableInterrupts);

            /* 1) Set force NACK to ignore I2C transactions
               2) Wait while I2C will be ready go to Sleep
               3) These bits are cleared on wake up */
            I2CHW_XCFG_REG |= I2CHW_XCFG_FORCE_NACK;
            while(0u == (I2CHW_XCFG_REG & I2CHW_XCFG_RDY_TO_SLEEP))
            {
                ; /* Wait when block is ready to Sleep */
            }

            /* Setup wakeup interrupt */
            I2CHW_DisableInt();
            (void) CyIntSetVector(I2CHW_ISR_NUMBER, &I2CHW_WAKEUP_ISR);
            I2CHW_wakeupSource = 0u;
            I2CHW_EnableInt();

        #endif /* (I2CHW_WAKEUP_ENABLED) */

    #else
        /* Store only address match bit */
        I2CHW_backup.control = (I2CHW_CFG_REG & I2CHW_CTRL_ANY_ADDRESS_MASK);

        #if(CY_UDB_V0)
            /* Store interrupt mask bits */
            I2CHW_backup.intMask = I2CHW_INT_MASK_REG;

            #if(I2CHW_MODE & I2CHW_MODE_SLAVE)
                I2CHW_backup.addr = I2CHW_ADDR_REG;
            #endif /* (I2CHW_MODE & I2CHW_MODE_SLAVE) */

        #endif /* (CY_UDB_V0) */

    #endif /* (I2CHW_FF_IMPLEMENTED) */

    #if(I2CHW_TIMEOUT_ENABLED)
        I2CHW_TimeoutSaveConfig();   /* Save Timeout config */
    #endif /* (I2CHW_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: I2CHW_Sleep
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: All incoming transaction will be NACKed till
*  power down will be asserted. The address match event wakes up the chip.
*  Wakeup on address match disabled: Disables active mode power template bits or
*  clock gating as appropriate. Saves I2C configuration and non-retention
*  register values.
*  Disables I2C interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void I2CHW_Sleep(void) 
{
    #if(I2CHW_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        I2CHW_backup.enableState = I2CHW_DISABLE;

        #if(I2CHW_TIMEOUT_ENABLED)
            I2CHW_TimeoutStop();
        #endif /* (I2CHW_TIMEOUT_ENABLED) */

    #else

        I2CHW_backup.enableState = ((uint8) I2CHW_IS_ENABLED);

        if(I2CHW_IS_ENABLED)
        {
            I2CHW_Stop();
        }
    #endif /* (I2CHW_WAKEUP_ENABLED) */

    I2CHW_SaveConfig();
}


/*******************************************************************************
* Function Name: I2CHW_RestoreConfig
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep), disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  I2CHW_backup - used to save component configuration and
*  none-retention registers before exit sleep mode.
*
*******************************************************************************/
void I2CHW_RestoreConfig(void) 
{
    #if(I2CHW_FF_IMPLEMENTED)
        uint8 enableInterrupts;

        if(I2CHW_CHECK_PWRSYS_I2C_BACKUP)    /* Enabled if was in Sleep */
        {
            /* Disable back-up regulator */
            enableInterrupts = CyEnterCriticalSection();
            I2CHW_PWRSYS_CR1_REG &= ((uint8) ~I2CHW_PWRSYS_CR1_I2C_REG_BACKUP);
            CyExitCriticalSection(enableInterrupts);

            /* Re-enable Master */
            I2CHW_CFG_REG = I2CHW_backup.cfg;
        }
        else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
        {
            #if(I2CHW_WAKEUP_ENABLED)
                /* Disable power to I2C block before register restore */
                enableInterrupts = CyEnterCriticalSection();
                I2CHW_ACT_PWRMGR_REG  &= ((uint8) ~I2CHW_ACT_PWR_EN);
                I2CHW_STBY_PWRMGR_REG &= ((uint8) ~I2CHW_STBY_PWR_EN);
                CyExitCriticalSection(enableInterrupts);

                /* Enable component after restore complete */
                I2CHW_backup.enableState = I2CHW_ENABLE;
            #endif /* (I2CHW_WAKEUP_ENABLED) */

            /* Restore component registers: Hibernate disable power */
            I2CHW_XCFG_REG = I2CHW_backup.xcfg;
            I2CHW_CFG_REG  = I2CHW_backup.cfg;

            #if(I2CHW_MODE_SLAVE_ENABLED)
                I2CHW_ADDR_REG = I2CHW_backup.addr;
            #endif /* (I2CHW_MODE_SLAVE_ENABLED) */

            #if(CY_PSOC5A)
                I2CHW_CLKDIV_REG  = I2CHW_backup.clkDiv;
            #else
                I2CHW_CLKDIV1_REG = I2CHW_backup.clkDiv1;
                I2CHW_CLKDIV2_REG = I2CHW_backup.clkDiv2;
            #endif /* (CY_PSOC5A) */
        }

        #if(I2CHW_WAKEUP_ENABLED)
            I2CHW_DisableInt();
            (void) CyIntSetVector(I2CHW_ISR_NUMBER, &I2CHW_ISR);
            if(0u != I2CHW_wakeupSource)
            {
                I2CHW_SetPendingInt();   /* Generate interrupt to process incomming transcation */
            }
            I2CHW_EnableInt();
        #endif /* (I2CHW_WAKEUP_ENABLED) */

    #else

        #if(CY_UDB_V0)
            uint8 enableInterrupts;

            I2CHW_INT_MASK_REG |= I2CHW_backup.intMask;

            enableInterrupts = CyEnterCriticalSection();
            I2CHW_INT_ENABLE_REG |= I2CHW_INT_ENABLE_MASK;
            CyExitCriticalSection(enableInterrupts);

            #if(I2CHW_MODE_MASTER_ENABLED)
                /* Restore Master Clock generator */
                I2CHW_MCLK_PRD_REG = I2CHW_DEFAULT_MCLK_PRD;
                I2CHW_MCLK_CMP_REG = I2CHW_DEFAULT_MCLK_CMP;
            #endif /* (I2CHW_MODE_MASTER_ENABLED) */

            #if(I2CHW_MODE_SLAVE_ENABLED)
                I2CHW_ADDR_REG = I2CHW_backup.addr;

                /* Restore slave bit counter period */
                I2CHW_PERIOD_REG = I2CHW_DEFAULT_PERIOD;
            #endif /* (I2CHW_MODE_SLAVE_ENABLED) */

        #endif /* (CY_UDB_V0) */

        I2CHW_CFG_REG = I2CHW_backup.control;

    #endif /* (I2CHW_FF_IMPLEMENTED) */

    #if(I2CHW_TIMEOUT_ENABLED)
        I2CHW_TimeoutRestoreConfig();
    #endif /* (I2CHW_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: I2CHW_Wakeup
********************************************************************************
*
* Summary:
*  Wakeup on address match enabled: enables I2C Master (if was enabled before go
*  to sleep) and disables I2C backup regulator.
*  Wakeup on address match disabled: Restores I2C configuration and
*  non-retention register values. Restores Active mode power template bits or
*  clock gating as appropriate.
*  The I2C interrupt remains disabled after function call.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void I2CHW_Wakeup(void) 
{
    I2CHW_RestoreConfig();   /* Restore I2C register settings */

    /* Restore component enable state */
    if(0u != I2CHW_backup.enableState)
    {
        I2CHW_Enable();
        I2CHW_EnableInt();
    }
    else
    {
        #if(I2CHW_TIMEOUT_ENABLED)
            I2CHW_TimeoutEnable();
        #endif /* (I2CHW_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
