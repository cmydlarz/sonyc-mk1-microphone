/*******************************************************************************
* File Name: Droop_Filter.c
* Version 2.10
*
* Description:
*  This file provides the API source code for the FILT component.
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


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

uint8 Droop_Filter_initVar = 0u;


/*******************************************************************************
* Function Name: Droop_Filter_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Droop_Filter_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Droop_Filter_Init(void) 
{
        /* Power on DFB before initializing the RAMs */
    Droop_Filter_PM_ACT_CFG_REG |= Droop_Filter_PM_ACT_MSK;

    /* Turn off Run Bit */
    Droop_Filter_CR_REG &= ~Droop_Filter_RUN_MASK;
                
    /* Enable the DFB RAMS */
    Droop_Filter_RAM_EN_REG = Droop_Filter_RAM_DIR_BUS;
        
    /* Put DFB RAM on the bus */
    Droop_Filter_RAM_DIR_REG = Droop_Filter_RAM_DIR_BUS;
        
    /* Write DFB RAMs */
    /* Control Store RAMs */
    memcpy( Droop_Filter_CSA_RAM,
        Droop_Filter_control, Droop_Filter_CSA_RAM_SIZE); 
    memcpy(Droop_Filter_CSB_RAM,
        Droop_Filter_control, Droop_Filter_CSB_RAM_SIZE); 
    /* CFSM RAM */
    memcpy(Droop_Filter_CFSM_RAM,
        Droop_Filter_cfsm, Droop_Filter_CFSM_RAM_SIZE); 
    /* DAta RAMs */
    memcpy(Droop_Filter_DA_RAM,
        Droop_Filter_data_a, Droop_Filter_DA_RAM_SIZE); 
    memcpy(Droop_Filter_DB_RAM,
        Droop_Filter_data_b, Droop_Filter_DB_RAM_SIZE); 
    /* ACU RAM */
    memcpy(Droop_Filter_ACU_RAM,
        Droop_Filter_acu, Droop_Filter_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    Droop_Filter_RAM_DIR_REG = Droop_Filter_RAM_DIR_DFB;

    /* Set up interrupt and DMA events */
    Droop_Filter_SetInterruptMode(Droop_Filter_INIT_INTERRUPT_MODE);
    Droop_Filter_SetDMAMode(Droop_Filter_INIT_DMA_MODE);
        
    /* Clear any pending interrupts */
    /* Bits [2..0] of this register are readonly. */
    Droop_Filter_SR_REG = 0xf8;   
}


/*******************************************************************************
* Function Name: Droop_Filter_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DFB run bit.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Droop_Filter_Enable(void) 
{
    /* Power on DFB in Active mode */
    Droop_Filter_PM_ACT_CFG_REG |= Droop_Filter_PM_ACT_MSK;
        
    /* Power on DFB in Alternative Active mode */
    Droop_Filter_PM_STBY_CFG_REG |= Droop_Filter_PM_STBY_MSK;

    /* Turn on Run Bit */
    Droop_Filter_CR_REG |= Droop_Filter_RUN_MASK;
}


/*******************************************************************************
* Function Name: Droop_Filter_Start
********************************************************************************
*
* Summary:
*  This method does the prep work necessary to setup DFB.  This includes loading 
*
* Parameters:  
*  void
* 
* Return: 
*  void
*
* Global variables:
*  Droop_Filter_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Note: 
*  Use Droop_Filter_InterruptConfig to control which events trigger 
*  interrupts in the DFB. 
*
*******************************************************************************/
void Droop_Filter_Start() 
{
     /* If not Initialized then initialize all required hardware and software */
    if(Droop_Filter_initVar == 0u)
    {
        Droop_Filter_Init();
        Droop_Filter_initVar = 1u;
    }

    /* Enable the DFB block */
    Droop_Filter_Enable();
}


/*******************************************************************************
* Function Name: Droop_Filter_Stop
********************************************************************************
*
* Summary:
*  Turn off the run bit.  If DMA control is used to feed the channels, allow 
*  arguments to turn one of the TD channels off. 
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Droop_Filter_Stop() 
{
    Droop_Filter_CR_REG &= ~(Droop_Filter_RUN_MASK);

    /* Power off DFB in Active mode */
    Droop_Filter_PM_ACT_CFG_REG &= ~Droop_Filter_PM_ACT_MSK;
    
    /* Power off DFB in Alternative Active mode */
    Droop_Filter_PM_STBY_CFG_REG &= ~Droop_Filter_PM_STBY_MSK;
}


/*******************************************************************************
* Function Name: Droop_Filter_Read8
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  Droop_Filter_CHANNEL_A or Droop_Filter_CHANNEL_B
*            
* Return: 
*  The most significant 8 bits of the current output value sitting in the 
*  selected channel's holding register or 0x00 for invalid channel numbers.
*
*******************************************************************************/
uint8 Droop_Filter_Read8(uint8 channel) 
{
    uint8 value;

    if (channel == Droop_Filter_CHANNEL_A)
    {
        value = Droop_Filter_HOLDAH_REG;
    }
    else if (channel == Droop_Filter_CHANNEL_B)
    {
        value = Droop_Filter_HOLDBH_REG;
    }
    else
    {
        value = 0x0u;
    }
    return value;
}


/*******************************************************************************
* Function Name: Droop_Filter_Read16
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  Droop_Filter_CHANNEL_A or Droop_Filter_CHANNEL_B
*            
* Return: 
*  The most significant 16 bits of the current output value sitting in the 
*  selected channel's holding register or 0x0000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__) 

    uint16 Droop_Filter_Read16(uint8 channel) 
    {
        uint16 val;
    
        if (channel == Droop_Filter_CHANNEL_A)
        {        
            val = Droop_Filter_HOLDAM_REG;
            val |= (uint16)(Droop_Filter_HOLDAH_REG) << 8;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {      
            val = Droop_Filter_HOLDBM_REG;
            val |= (uint16)Droop_Filter_HOLDBH_REG << 8;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint16 Droop_Filter_Read16(uint8 channel) 
    {
        uint16 val;

        if (channel == Droop_Filter_CHANNEL_A)
        {        
            val = Droop_Filter_HOLDA16_REG;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {      
            val = Droop_Filter_HOLDB16_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: Droop_Filter_Read24
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  Droop_Filter_CHANNEL_A or Droop_Filter_CHANNEL_B
*            
* Return: 
*  The current 24-bit output value sitting in the selected channel's
*  holding register or 0x00000000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    uint32 Droop_Filter_Read24(uint8 channel) 
    {
        uint32 val;
    
        if (channel == Droop_Filter_CHANNEL_A)
        {        
            val = Droop_Filter_HOLDA_REG;
            val |= (uint32)(Droop_Filter_HOLDAM_REG) << 8;
            val |= (uint32)(Droop_Filter_HOLDAH_REG) << 16;
            
            /* SignExtend */
            if(val & Droop_Filter_SIGN_BIT)
                val |= Droop_Filter_SIGN_BYTE;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {      
            val = Droop_Filter_HOLDB_REG;
            val |= (uint32)Droop_Filter_HOLDBM_REG << 8;
            val |= (uint32)Droop_Filter_HOLDBH_REG << 16;
            
            /* SignExtend */
            if(val & Droop_Filter_SIGN_BIT)
                val |= Droop_Filter_SIGN_BYTE;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint32 Droop_Filter_Read24(uint8 channel) 
    {
        uint32 val;
         
        if (channel == Droop_Filter_CHANNEL_A)
        {        
            val = Droop_Filter_HOLDA24_REG;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {      
            val = Droop_Filter_HOLDB24_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: Droop_Filter_Write8
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either Droop_Filter_CHANNEL_A or 
*            Droop_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 8-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
void Droop_Filter_Write8(uint8 channel, uint8 sample) 
{
    if (channel == Droop_Filter_CHANNEL_A)
    {
        Droop_Filter_STAGEAH_REG = sample;
    }
    else if (channel == Droop_Filter_CHANNEL_B)
    {
        Droop_Filter_STAGEBH_REG = sample;
    }
    /* No Final else statement: No value is loaded on bad channel input */
}


/*******************************************************************************
* Function Name: Droop_Filter_Write16
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either Droop_Filter_CHANNEL_A or 
*            Droop_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 16-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void Droop_Filter_Write16(uint8 channel, uint16 sample) 
    {
        /* Write the STAGE MSB reg last as it signals a complete wrote to the 
           DFB.*/
        if (channel == Droop_Filter_CHANNEL_A)
        {
            Droop_Filter_STAGEAM_REG = (uint8)(sample);
            Droop_Filter_STAGEAH_REG = (uint8)(sample >> 8 );
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {
            Droop_Filter_STAGEBM_REG = (uint8)(sample);
            Droop_Filter_STAGEBH_REG = (uint8)(sample >> 8);
        }
        /* No Final else statement: No value is loaded on bad channel input */
    }

#else

    void Droop_Filter_Write16(uint8 channel, uint16 sample) 
    {
        if (channel == Droop_Filter_CHANNEL_A)
        {
            Droop_Filter_STAGEA16_REG = sample;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {
            Droop_Filter_STAGEB16_REG = sample;
        }
        /* No Final else statement: No value is loaded on bad channel input */
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: Droop_Filter_Write24
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either Droop_Filter_CHANNEL_A or 
*            Droop_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 24-bit, right justified input sample inside of a uint32. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void Droop_Filter_Write24(uint8 channel, uint32 sample) 
    {
        /* Write the STAGE LSB reg last as it signals a complete wrote to 
           the DFB.*/
        if (channel == Droop_Filter_CHANNEL_A)
        {
            Droop_Filter_STAGEA_REG  = (uint8)(sample);
            Droop_Filter_STAGEAM_REG = (uint8)(sample >> 8 );
            Droop_Filter_STAGEAH_REG = (uint8)(sample >> 16);
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {
            Droop_Filter_STAGEB_REG = (uint8)(sample);
            Droop_Filter_STAGEBM_REG = (uint8)(sample >> 8);
            Droop_Filter_STAGEBH_REG = (uint8)(sample >> 16);
        }
        /* No Final else statement: No value is loaded on bad channel input */
    }

#else

    void Droop_Filter_Write24(uint8 channel, uint32 sample) 
    {
        if (channel == Droop_Filter_CHANNEL_A)
        {
            Droop_Filter_STAGEA24_REG = sample;
        }
        else if (channel == Droop_Filter_CHANNEL_B)
        {
            Droop_Filter_STAGEB24_REG = sample;
        }
        /* No Final else statement: No value is loaded on bad channel input */
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: Droop_Filter_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the DFB coherency register with the user provided input 
*
* Parameters:  
*  channel:  Droop_Filter_CHANNEL_A or Droop_Filter_CHANNEL_B
*  byteSelect:  High byte, Middle byte or Low byte as the key coherency byte.
*            
* Return: 
*  None.
*
*******************************************************************************/
void Droop_Filter_SetCoherency(uint8 channel, uint8 byteSelect) 
{
    if (channel == Droop_Filter_CHANNEL_A)
    {
        Droop_Filter_COHER_REG &= ~(Droop_Filter_STAGEA_COHER_MASK | Droop_Filter_HOLDA_COHER_MASK);
        Droop_Filter_COHER_REG |= byteSelect;
        Droop_Filter_COHER_REG |= (byteSelect << 4);
    }
    else if (channel == Droop_Filter_CHANNEL_B)
    {
        Droop_Filter_COHER_REG &= ~(Droop_Filter_STAGEB_COHER_MASK | Droop_Filter_HOLDB_COHER_MASK);
        Droop_Filter_COHER_REG |= byteSelect << 2;
        Droop_Filter_COHER_REG |= (byteSelect << 6);
    }
}


/* [] END OF FILE */
