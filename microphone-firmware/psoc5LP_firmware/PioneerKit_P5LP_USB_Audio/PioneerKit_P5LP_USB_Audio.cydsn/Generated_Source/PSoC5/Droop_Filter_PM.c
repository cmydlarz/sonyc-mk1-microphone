/*******************************************************************************
* File Name: Droop_Filter_PM.c
* Version 2.10
*
* Description:
*  This file provides the power managaer API source code for the FILT component.
*
* Note:
*  
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Droop_Filter_PVT.h"

static Droop_Filter_BACKUP_STRUCT  Droop_Filter_backup = 
{
    Droop_Filter_DISABLED,
    Droop_Filter_RUN_MASK,
    
};


/*******************************************************************************
* Function Name: Droop_Filter_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Droop_Filter_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void Droop_Filter_SaveConfig(void) 
{
    Droop_Filter_backup.cr = Droop_Filter_CR_REG;
    Droop_Filter_backup.sr = Droop_Filter_SR_REG;
    Droop_Filter_backup.sema = Droop_Filter_SEMA_REG;
}


/*******************************************************************************
* Function Name: Droop_Filter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Droop_Filter_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void Droop_Filter_RestoreConfig(void) 
{
    Droop_Filter_CR_REG = Droop_Filter_backup.cr;
    Droop_Filter_SR_REG = Droop_Filter_backup.sr;
    Droop_Filter_SEMA_REG = Droop_Filter_backup.sema;
    // Restore ACU RAM as this is not retension
    Droop_Filter_RestoreACURam();
}


/*******************************************************************************
* Function Name: Droop_Filter_RestoreACURAM
********************************************************************************
*
* Summary:
*  Restores the contents of ACU ram.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  None.
*
*******************************************************************************/
void Droop_Filter_RestoreACURam() 
{
    /* Power on DFB before initializing the RAMs */
    Droop_Filter_PM_ACT_CFG_REG |= Droop_Filter_PM_ACT_MSK;

    /* Put DFB RAM on the bus */
    Droop_Filter_RAM_DIR_REG = Droop_Filter_RAM_DIR_BUS;

    /* ACU RAM */
    memcpy(Droop_Filter_ACU_RAM,
        Droop_Filter_acu, Droop_Filter_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    Droop_Filter_RAM_DIR_REG = Droop_Filter_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: Droop_Filter_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Droop_Filter_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Droop_Filter_Sleep(void) 
{
    /* Save Filter enable state */
    if(Droop_Filter_PM_ACT_MSK == (Droop_Filter_PM_ACT_CFG_REG & Droop_Filter_PM_ACT_MSK))
    {
        /* Component is enabled */
        Droop_Filter_backup.enableState = Droop_Filter_ENABLED;
    }
    else
    {
        /* Component is disabled */
        Droop_Filter_backup.enableState = Droop_Filter_DISABLED;
    }

    /* Stop the configuration */
    Droop_Filter_Stop();

    /* Save the configuration */
    Droop_Filter_SaveConfig();
}


/*******************************************************************************
* Function Name: Droop_Filter_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Droop_Filter_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Droop_Filter_Wakeup(void) 
{
    /* Restore the configuration */
    Droop_Filter_RestoreConfig();
    
    /* Enable's the component operation */
    if(Droop_Filter_backup.enableState == Droop_Filter_ENABLED)
    {
        Droop_Filter_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
