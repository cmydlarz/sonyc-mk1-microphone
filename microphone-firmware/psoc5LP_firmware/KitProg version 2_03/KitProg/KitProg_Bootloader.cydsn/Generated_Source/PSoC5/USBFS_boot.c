/*******************************************************************************
* File Name: USBFS_boot.c
* Version 2.51
*
* Description:
*  Boot loader API for USBFS Component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBFS.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USBFS) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*    Bootloader defines
***************************************/

#define USBFS_CyBtLdrStarttimer(X, T)         {USBFS_universalTime = T * 10; X = 0u;}
#define USBFS_CyBtLdrChecktimer(X)            ((X++ < USBFS_universalTime) ? 1u : 0u)

#define USBFS_BTLDR_OUT_EP      (0x01u)
#define USBFS_BTLDR_IN_EP       (0x02u)


/***************************************
*    Bootloader Variables
***************************************/

uint16 USBFS_universalTime = 0u;
uint8 USBFS_started = 0u;


/*******************************************************************************
* Function Name: USBFS_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the component and enables the interupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function starts the USB with 3V or 5V operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_CyBtldrCommStart(void) 
{
    CyGlobalIntEnable;      /* Enable Global Interrupts */

    /*Start USBFS Operation/device 0 and with 5V or 3V operation depend on Voltage Congiguration in DWR */
    USBFS_Start(0u, USBFS_DWR_VDDD_OPERATION);

    /* USB componet started, the correct enumeration will be checked in first Read operation */
    USBFS_started = 1u;

}


/*******************************************************************************
* Function Name: USBFS_CyBtldrCommStop.
********************************************************************************
*
* Summary:
*  Disable the component and disable the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USBFS_CyBtldrCommStop(void) 
{
    USBFS_Stop();
}


/*******************************************************************************
* Function Name: USBFS_CyBtldrCommReset.
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication Buffers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_CyBtldrCommReset(void) 
{
    USBFS_EnableOutEP(USBFS_BTLDR_OUT_EP);  /* Enable the OUT endpoint */
}


/*******************************************************************************
* Function Name: USBFS_CyBtldrCommWrite.
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the boot loader host. The function will
*  handle polling to allow a block of data to be completely sent to the host
*  device.
*
* Parameters:
*  pData:    A pointer to the block of data to send to the device
*  size:     The number of bytes to write.
*  count:    Pointer to an unsigned short variable to write the number of
*             bytes actually written.
*  timeOut:  Number of units to wait before returning because of a timeout.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No.
*
*******************************************************************************/
cystatus USBFS_CyBtldrCommWrite(uint8 *pData, uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    uint16 time;
    cystatus status;

    /* Enable IN transfer */
    USBFS_LoadInEP(USBFS_BTLDR_IN_EP, pData, USBFS_BTLDR_SIZEOF_READ_BUFFER);

    /* Start a timer to wait on. */
    USBFS_CyBtLdrStarttimer(time, timeOut);

    /* Wait for the master to read it. */
    while((USBFS_GetEPState(USBFS_BTLDR_IN_EP) == USBFS_IN_BUFFER_FULL) && \
           USBFS_CyBtLdrChecktimer(time))
    {
        CyDelay(1); /* 1ms delay */
    }

    if (USBFS_GetEPState(USBFS_BTLDR_IN_EP) == USBFS_IN_BUFFER_FULL)
    {
        status = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        status = CYRET_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: USBFS_CyBtldrCommRead.
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the boot loader host. The function will
*  handle polling to allow a block of data to be completely received from the
*  host device.
*
* Parameters:
*  pData:    A pointer to the area to store the block of data received
*             from the device.
*  size:     The number of bytes to read.
*  count:    Pointer to an unsigned short variable to write the number
*             of bytes actually read.
*  timeOut:  Number of units to wait before returning because of a timeOut.
*            Timeout is measured in 10s of ms.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No.
*
*******************************************************************************/
cystatus USBFS_CyBtldrCommRead(uint8 *pData, uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus status;
    uint16 time;

    if(size > USBFS_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = USBFS_BTLDR_SIZEOF_WRITE_BUFFER;
    }
    /* Start a timer to wait on. */
    USBFS_CyBtLdrStarttimer(time, timeOut);

    /* Wait on enumeration in first time */
    if(USBFS_started)
    {
        /* Wait for Device to enumerate */
        while(!USBFS_GetConfiguration() && USBFS_CyBtLdrChecktimer(time))
        {
            CyDelay(1); /* 1ms delay */
        }
        /* Enable first OUT, if enumeration complete */
        if(USBFS_GetConfiguration())
        {
            USBFS_IsConfigurationChanged();  /* Crear configuration changes state status */
            USBFS_CyBtldrCommReset();
            USBFS_started = 0u;
        }
    }
    else /* Check for configuration changes has been done by Host */
    {
        if(USBFS_IsConfigurationChanged() != 0) /* Host could send double SET_INTERFACE request or RESET */
        {
            if(USBFS_GetConfiguration() != 0)    /* Init IN endpoints when device configured */
            {
                USBFS_CyBtldrCommReset();
            }
        }    
    }

    /* Wait on next packet */
    while((USBFS_GetEPState(USBFS_BTLDR_OUT_EP) != USBFS_OUT_BUFFER_FULL) && \
           USBFS_CyBtLdrChecktimer(time))
    {
        CyDelay(1); /* 1ms delay */
    }

    /* OUT EP has completed */
    if (USBFS_GetEPState(USBFS_BTLDR_OUT_EP) == USBFS_OUT_BUFFER_FULL)
    {
        *count = USBFS_ReadOutEP(USBFS_BTLDR_OUT_EP, pData, size);
        status = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        status = CYRET_TIMEOUT;
    }
    return(status);
}

#endif /* End CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USBFS */


/* [] END OF FILE */
