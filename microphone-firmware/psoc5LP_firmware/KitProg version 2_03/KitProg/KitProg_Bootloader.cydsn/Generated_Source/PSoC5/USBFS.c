/*******************************************************************************
* File Name: USBFS.c
* Version 2.51
*
* Description:
*  API for USBFS Component.
*
* Note:
*  Many of the functions use endpoint number.  RAM arrays are sized with 9
*  elements so they are indexed directly by epNumber.  The SIE and ARB
*  registers are indexed by variations of epNumber - 1.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <CyDmac.h>
#include "USBFS.h"
#include "USBFS_hid.h"
#if(USBFS_DMA1_REMOVE == 0u)
    #include "USBFS_ep1_dma.h"
#endif   /* End USBFS_DMA1_REMOVE */
#if(USBFS_DMA2_REMOVE == 0u)
    #include "USBFS_ep2_dma.h"
#endif   /* End USBFS_DMA2_REMOVE */
#if(USBFS_DMA3_REMOVE == 0u)
    #include "USBFS_ep3_dma.h"
#endif   /* End USBFS_DMA3_REMOVE */
#if(USBFS_DMA4_REMOVE == 0u)
    #include "USBFS_ep4_dma.h"
#endif   /* End USBFS_DMA4_REMOVE */
#if(USBFS_DMA5_REMOVE == 0u)
    #include "USBFS_ep5_dma.h"
#endif   /* End USBFS_DMA5_REMOVE */
#if(USBFS_DMA6_REMOVE == 0u)
    #include "USBFS_ep6_dma.h"
#endif   /* End USBFS_DMA6_REMOVE */
#if(USBFS_DMA7_REMOVE == 0u)
    #include "USBFS_ep7_dma.h"
#endif   /* End USBFS_DMA7_REMOVE */
#if(USBFS_DMA8_REMOVE == 0u)
    #include "USBFS_ep8_dma.h"
#endif   /* End USBFS_DMA8_REMOVE */


/***************************************
* External data references
***************************************/

extern volatile uint8 USBFS_configuration;
extern volatile uint8 USBFS_interfaceNumber;
extern volatile uint8 USBFS_configurationChanged;
extern volatile uint8 USBFS_interfaceSetting[];
extern volatile uint8 USBFS_interfaceSetting_last[];
extern volatile uint8 USBFS_deviceAddress;
extern volatile uint8 USBFS_deviceStatus;
extern volatile uint8 USBFS_device;
extern volatile uint8 USBFS_transferState;
extern volatile uint8 USBFS_lastPacketSize;

extern volatile T_USBFS_EP_CTL_BLOCK USBFS_EP[];

#if defined(USBFS_ENABLE_HID_CLASS)
    extern volatile uint8 USBFS_hidProtocol[];
#endif /* USBFS_ENABLE_HID_CLASS */


/***************************************
* External function references
***************************************/

CY_ISR_PROTO(USBFS_EP_0_ISR);
#if(USBFS_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_1_ISR);
#endif /* End USBFS_EP1_ISR_REMOVE */
#if(USBFS_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_2_ISR);
#endif /* End USBFS_EP2_ISR_REMOVE */
#if(USBFS_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_3_ISR);
#endif /* End USBFS_EP3_ISR_REMOVE */
#if(USBFS_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_4_ISR);
#endif /* End USBFS_EP4_ISR_REMOVE */
#if(USBFS_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_5_ISR);
#endif /* End USBFS_EP5_ISR_REMOVE */
#if(USBFS_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_6_ISR);
#endif /* End USBFS_EP6_ISR_REMOVE */
#if(USBFS_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_7_ISR);
#endif /* End USBFS_EP7_ISR_REMOVE */
#if(USBFS_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_EP_8_ISR);
#endif /* End USBFS_EP8_ISR_REMOVE */
CY_ISR_PROTO(USBFS_BUS_RESET_ISR);
#if(USBFS_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USBFS_SOF_ISR);
#endif /* End USBFS_SOF_ISR_REMOVE */
#if(USBFS_EP_MM != USBFS__EP_MANUAL)
    CY_ISR_PROTO(USBFS_ARB_ISR);
#endif /* End USBFS_EP_MM */


/***************************************
* Global data allocation
***************************************/

uint8 USBFS_initVar = 0u;
#if(USBFS_EP_MM != USBFS__EP_MANUAL)
    uint8 USBFS_DmaChan[USBFS_MAX_EP];
    uint8 USBFS_DmaTd[USBFS_MAX_EP];
#endif /* End USBFS_EP_MM */


/*******************************************************************************
* Function Name: USBFS_Start
********************************************************************************
*
* Summary:
*  This function initialize the USB SIE, arbiter and the
*  endpoint APIs, including setting the D+ Pullup
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of 
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       USBFS_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       USBFS_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       USBFS_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*  The USBFS_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time USBFS_Start() is called.
*  This allows for component Re-Start without unnecessary re-initialization
*  in all subsequent calls to the USBFS_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of UART_Start() routine, or the user may call
*  USBFS_Init() and USBFS_InitComponent() as done
*  in the USBFS_Start() routine.
*
* Side Effects:
*   This function will reset all communication states to default.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_Start(uint8 device, uint8 mode) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(USBFS_initVar == 0u)
    {
        USBFS_Init();
        USBFS_initVar = 1u;
    }
    USBFS_InitComponent(device, mode);
}


/*******************************************************************************
* Function Name: USBFS_Init
********************************************************************************
*
* Summary:
*  Initialize component's hardware. Usually called in USBFS_Start().
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
void USBFS_Init(void) 
{
    uint8 enableInterrupts;
    #if(USBFS_EP_MM != USBFS__EP_MANUAL)
        uint16 i;
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

    enableInterrupts = CyEnterCriticalSection();

    /* Enable USB block  */
    USBFS_PM_ACT_CFG_REG |= USBFS_PM_ACT_EN_FSUSB;
    /* Enable USB block for Standby Power Mode */
    USBFS_PM_STBY_CFG_REG |= USBFS_PM_STBY_EN_FSUSB;

    #if(CY_PSOC5A)
        /* Disable USBIO for TO3 */
        USBFS_PM_AVAIL_CR_REG &= ~USBFS_PM_AVAIL_EN_FSUSBIO;
    #endif /* End CY_PSOC5A */

    /* Enable core clock */
    USBFS_USB_CLK_EN_REG = USBFS_USB_CLK_ENABLE;

    USBFS_CR1_REG = USBFS_CR1_ENABLE_LOCK;

    #if(CY_PSOC5A)
        /* Enable USBIO for TO3 */
        USBFS_PM_AVAIL_CR_REG |= USBFS_PM_AVAIL_EN_FSUSBIO;
        /* Bus Reset Length, It has correct default value in ES3 */
        USBFS_BUS_RST_CNT_REG = USBFS_BUS_RST_COUNT;
    #endif /* End CY_PSOC5A */

    /* ENABLING USBIO PADS IN USB MODE FROM I/O MODE */
    #if(!CY_PSOC5A)
        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        USBFS_USBIO_CR0_REG &= ~USBFS_USBIO_CR0_TEN;
        CyDelayUs(0);  /*~50ns delay */
        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted)
        *  high. This will have been set low by the power manger out of reset.
        *  Also confirm USBIO pull-up disabled
        */
        USBFS_PM_USB_CR0_REG &= ~(USBFS_PM_USB_CR0_PD_N |USBFS_PM_USB_CR0_PD_PULLUP_N);

        /* Select iomode to USB mode*/
        USBFS_USBIO_CR1_REG &= ~ USBFS_USBIO_CR1_IOMODE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USBFS_PM_USB_CR0_REG |= USBFS_PM_USB_CR0_REF_EN;
        /* The reference will be available 1 us after the regulator is enabled */
        CyDelayUs(1);
        /* OR 40us after power restored */
        CyDelayUs(40);
        /* Ensure the single ended disable bits are low (PRT15.INP_DIS[7:6])(input receiver enabled). */
        USBFS_DM_INP_DIS_REG &= ~USBFS_DM_MASK;
        USBFS_DP_INP_DIS_REG &= ~USBFS_DP_MASK;

        /* Enable USBIO */
        USBFS_PM_USB_CR0_REG |= USBFS_PM_USB_CR0_PD_N;
        CyDelayUs(2);
        /* Set the USBIO pull-up enable */
        USBFS_PM_USB_CR0_REG |= USBFS_PM_USB_CR0_PD_PULLUP_N;

    #endif /* End !CY_PSOC5A */

    /* Write WAx */
    CY_SET_REG8(&USBFS_ARB_RW1_WA_PTR[0u],     0u);
    CY_SET_REG8(&USBFS_ARB_RW1_WA_MSB_PTR[0u], 0u);

    #if(USBFS_EP_MM != USBFS__EP_MANUAL)
        /* Init transfer descriptor. This will be used to detect the DMA state - initialized or not. */
        for (i = 0u; i < USBFS_MAX_EP; i++)
        {
            USBFS_DmaTd[i] = DMA_INVALID_TD;
        }
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

    CyExitCriticalSection(enableInterrupts);


    /* Set the bus reset Interrupt. */
    CyIntSetVector(USBFS_BUS_RESET_VECT_NUM,   USBFS_BUS_RESET_ISR);
    CyIntSetPriority(USBFS_BUS_RESET_VECT_NUM, USBFS_BUS_RESET_PRIOR);

    /* Set the SOF Interrupt. */
    #if(USBFS_SOF_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_SOF_VECT_NUM,   USBFS_SOF_ISR);
        CyIntSetPriority(USBFS_SOF_VECT_NUM, USBFS_SOF_PRIOR);
    #endif   /* End USBFS_SOF_ISR_REMOVE */

    /* Set the Control Endpoint Interrupt. */
    CyIntSetVector(USBFS_EP_0_VECT_NUM,   USBFS_EP_0_ISR);
    CyIntSetPriority(USBFS_EP_0_VECT_NUM, USBFS_EP_0_PRIOR);

    /* Set the Data Endpoint 1 Interrupt. */
    #if(USBFS_EP1_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_1_VECT_NUM,   USBFS_EP_1_ISR);
        CyIntSetPriority(USBFS_EP_1_VECT_NUM, USBFS_EP_1_PRIOR);
    #endif   /* End USBFS_EP1_ISR_REMOVE */

    /* Set the Data Endpoint 2 Interrupt. */
    #if(USBFS_EP2_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_2_VECT_NUM,   USBFS_EP_2_ISR);
        CyIntSetPriority(USBFS_EP_2_VECT_NUM, USBFS_EP_2_PRIOR);
    #endif   /* End USBFS_EP2_ISR_REMOVE */

    /* Set the Data Endpoint 3 Interrupt. */
    #if(USBFS_EP3_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_3_VECT_NUM,   USBFS_EP_3_ISR);
        CyIntSetPriority(USBFS_EP_3_VECT_NUM, USBFS_EP_3_PRIOR);
    #endif   /* End USBFS_EP3_ISR_REMOVE */

    /* Set the Data Endpoint 4 Interrupt. */
    #if(USBFS_EP4_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_4_VECT_NUM,   USBFS_EP_4_ISR);
        CyIntSetPriority(USBFS_EP_4_VECT_NUM, USBFS_EP_4_PRIOR);
    #endif   /* End USBFS_EP4_ISR_REMOVE */

    /* Set the Data Endpoint 5 Interrupt. */
    #if(USBFS_EP5_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_5_VECT_NUM,   USBFS_EP_5_ISR);
        CyIntSetPriority(USBFS_EP_5_VECT_NUM, USBFS_EP_5_PRIOR);
    #endif   /* End USBFS_EP5_ISR_REMOVE */

    /* Set the Data Endpoint 6 Interrupt. */
    #if(USBFS_EP6_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_6_VECT_NUM,   USBFS_EP_6_ISR);
        CyIntSetPriority(USBFS_EP_6_VECT_NUM, USBFS_EP_6_PRIOR);
    #endif   /* End USBFS_EP6_ISR_REMOVE */

     /* Set the Data Endpoint 7 Interrupt. */
    #if(USBFS_EP7_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_7_VECT_NUM,   USBFS_EP_7_ISR);
        CyIntSetPriority(USBFS_EP_7_VECT_NUM, USBFS_EP_7_PRIOR);
    #endif   /* End USBFS_EP7_ISR_REMOVE */

    /* Set the Data Endpoint 8 Interrupt. */
    #if(USBFS_EP8_ISR_REMOVE == 0u)
        CyIntSetVector(USBFS_EP_8_VECT_NUM,   USBFS_EP_8_ISR);
        CyIntSetPriority(USBFS_EP_8_VECT_NUM, USBFS_EP_8_PRIOR);
    #endif   /* End USBFS_EP8_ISR_REMOVE */

    #if((USBFS_EP_MM != USBFS__EP_MANUAL) && (USBFS_ARB_ISR_REMOVE == 0u))
        /* Set the ARB Interrupt. */
        CyIntSetVector(USBFS_ARB_VECT_NUM,   USBFS_ARB_ISR);
        CyIntSetPriority(USBFS_ARB_VECT_NUM, USBFS_ARB_PRIOR);
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

}


/*******************************************************************************
* Function Name: USBFS_InitComponent
********************************************************************************
*
* Summary:
*  Initialize the component, except for the HW which is done one time in
*  the Start function.  This function pulls up D+.
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of 
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       USBFS_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       USBFS_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       USBFS_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*   USBFS_device: Contains the device number of the desired device
*       descriptor. The device number can be found in the Device Descriptor Tab 
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   USBFS_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   USBFS_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USBFS_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USBFS_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USBFS_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_InitComponent(uint8 device, uint8 mode) 
{
    /* Initialize _hidProtocol variable to comply with
    *  HID 7.2.6 Set_Protocol Request:
    *  "When initialized, all devices default to report protocol."
    */
    #if defined(USBFS_ENABLE_HID_CLASS)
        uint8 interface;

        for (interface = 0u; interface < USBFS_MAX_INTERFACES_NUMBER; interface++)
        {
            USBFS_hidProtocol[interface] = USBFS_PROTOCOL_REPORT;
        }
    #endif /* USBFS_ENABLE_HID_CLASS */

    /* Enable Interrupts. */
    CyIntEnable(USBFS_BUS_RESET_VECT_NUM);
    CyIntEnable(USBFS_EP_0_VECT_NUM);
    #if(USBFS_EP1_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_1_VECT_NUM);
    #endif   /* End USBFS_EP1_ISR_REMOVE */
    #if(USBFS_EP2_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_2_VECT_NUM);
    #endif   /* End USBFS_EP2_ISR_REMOVE */
    #if(USBFS_EP3_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_3_VECT_NUM);
    #endif   /* End USBFS_EP3_ISR_REMOVE */
    #if(USBFS_EP4_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_4_VECT_NUM);
    #endif   /* End USBFS_EP4_ISR_REMOVE */
    #if(USBFS_EP5_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_5_VECT_NUM);
    #endif   /* End USBFS_EP5_ISR_REMOVE */
    #if(USBFS_EP6_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_6_VECT_NUM);
    #endif   /* End USBFS_EP6_ISR_REMOVE */
    #if(USBFS_EP7_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_7_VECT_NUM);
    #endif   /* End USBFS_EP7_ISR_REMOVE */
    #if(USBFS_EP8_ISR_REMOVE == 0u)
        CyIntEnable(USBFS_EP_8_VECT_NUM);
    #endif   /* End USBFS_EP8_ISR_REMOVE */
    #if((USBFS_EP_MM != USBFS__EP_MANUAL) && (USBFS_ARB_ISR_REMOVE == 0u))
        /* usb arb interrupt enable */
        USBFS_ARB_INT_EN_REG = USBFS_ARB_INT_MASK;
        CyIntEnable(USBFS_ARB_VECT_NUM);
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

    /* Arbiter congiguration for DMA transfers */
    #if(USBFS_EP_MM != USBFS__EP_MANUAL)

        #if(USBFS_EP_MM == USBFS__EP_DMAMANUAL)
            USBFS_ARB_CFG_REG = USBFS_ARB_CFG_MANUAL_DMA;
        #endif   /* End USBFS_EP_MM == USBFS__EP_DMAMANUAL */
        #if(USBFS_EP_MM == USBFS__EP_DMAAUTO)
            /*Set cfg cmplt this rises DMA request when the full configuration is done */
            USBFS_ARB_CFG_REG = USBFS_ARB_CFG_AUTO_DMA | USBFS_ARB_CFG_AUTO_MEM;
        #endif   /* End USBFS_EP_MM == USBFS__EP_DMAAUTO */
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

    USBFS_transferState = USBFS_TRANS_STATE_IDLE;

    /* USB Locking: Enabled, VRegulator: depend on mode or DWR Voltage configuration*/
    switch(mode)
    {
        case USBFS_3V_OPERATION:
            USBFS_CR1_REG = USBFS_CR1_ENABLE_LOCK;
            break;
        case USBFS_5V_OPERATION:
            USBFS_CR1_REG = USBFS_CR1_ENABLE_LOCK | USBFS_CR1_REG_ENABLE;
            break;
        default:   /*USBFS_DWR_VDDD_OPERATION */
            #if(USBFS_VDDD_MV < USBFS_3500MV)
                USBFS_CR1_REG = USBFS_CR1_ENABLE_LOCK;
            #else
                USBFS_CR1_REG = USBFS_CR1_ENABLE_LOCK | USBFS_CR1_REG_ENABLE;
            #endif /* End USBFS_VDDD_MV < USBFS_3500MV */
            break;
    }

    /* Record the descriptor selection */
    USBFS_device = device;

    /* Clear all of the component data */
    USBFS_configuration = 0u;
    USBFS_interfaceNumber = 0u;
    USBFS_configurationChanged = 0u;
    USBFS_deviceAddress  = 0u;
    USBFS_deviceStatus = 0u;

    USBFS_lastPacketSize = 0u;

    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(USBFS_EP0_CR_PTR, USBFS_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(USBFS_CR0_PTR, USBFS_CR0_ENABLE);

    /* Workarond for PSOC5LP */
    CyDelayCycles(1);
    
    /* Finally, Enable d+ pullup and select iomode to USB mode*/
    CY_SET_REG8(USBFS_USBIO_CR1_PTR, USBFS_USBIO_CR1_USBPUEN);
}


/*******************************************************************************
* Function Name: USBFS_ReInitComponent
********************************************************************************
*
* Summary:
*  This function reinitialize the component configuration and is
*  intend to be called from the Reset interrupt.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*   USBFS_device: Contains the device number of the desired device 
*		descriptor. The device number can be found in the Device Descriptor Tab 
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   USBFS_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   USBFS_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USBFS_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USBFS_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USBFS_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_ReInitComponent() 
{
    /* Initialize _hidProtocol variable to comply with HID 7.2.6 Set_Protocol
    *  Request: "When initialized, all devices default to report protocol."
    */
    #if defined(USBFS_ENABLE_HID_CLASS)
        uint8 interface;

        for (interface = 0u; interface < USBFS_MAX_INTERFACES_NUMBER; interface++)
        {
            USBFS_hidProtocol[interface] = USBFS_PROTOCOL_REPORT;
        }
    #endif /* USBFS_ENABLE_HID_CLASS */

    USBFS_transferState = USBFS_TRANS_STATE_IDLE;

    /* Clear all of the component data */
    USBFS_configuration = 0u;
    USBFS_interfaceNumber = 0u;
    USBFS_configurationChanged = 0u;
    USBFS_deviceAddress  = 0u;
    USBFS_deviceStatus = 0u;

    USBFS_lastPacketSize = 0u;


    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(USBFS_EP0_CR_PTR, USBFS_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(USBFS_CR0_PTR, USBFS_CR0_ENABLE);

}


/*******************************************************************************
* Function Name: USBFS_Stop
********************************************************************************
*
* Summary:
*  This function shuts down the USB function including to release
*  the D+ Pullup and disabling the SIE.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*   USBFS_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USBFS_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USBFS_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USBFS_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*   USBFS_intiVar variable is set to zero
*
*******************************************************************************/
void USBFS_Stop(void) 
{

    #if(USBFS_EP_MM != USBFS__EP_MANUAL)
        USBFS_Stop_DMA(USBFS_MAX_EP);     /* Stop all DMAs */
    #endif   /* End USBFS_EP_MM != USBFS__EP_MANUAL */

    /* Disable the SIE */
    USBFS_CR0_REG &= ~USBFS_CR0_ENABLE;
    /* Disable the d+ pullup */
    USBFS_USBIO_CR1_REG &= ~USBFS_USBIO_CR1_USBPUEN;
    #if(CY_PSOC5A)
        /* Disable USBIO block*/
        USBFS_PM_AVAIL_CR_REG &= ~USBFS_PM_AVAIL_EN_FSUSBIO;
    #endif /* End CY_PSOC5A */    
    /* Disable USB in ACT PM */
    USBFS_PM_ACT_CFG_REG &= ~USBFS_PM_ACT_EN_FSUSB;
    /* Disable USB block for Standby Power Mode */
    USBFS_PM_STBY_CFG_REG &= ~USBFS_PM_STBY_EN_FSUSB;

    /* Disable the reset and EP interrupts */
    CyIntDisable(USBFS_BUS_RESET_VECT_NUM);
    CyIntDisable(USBFS_EP_0_VECT_NUM);
    #if(USBFS_EP1_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_1_VECT_NUM);
    #endif   /* End USBFS_EP1_ISR_REMOVE */
    #if(USBFS_EP2_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_2_VECT_NUM);
    #endif   /* End USBFS_EP2_ISR_REMOVE */
    #if(USBFS_EP3_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_3_VECT_NUM);
    #endif   /* End USBFS_EP3_ISR_REMOVE */
    #if(USBFS_EP4_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_4_VECT_NUM);
    #endif   /* End USBFS_EP4_ISR_REMOVE */
    #if(USBFS_EP5_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_5_VECT_NUM);
    #endif   /* End USBFS_EP5_ISR_REMOVE */
    #if(USBFS_EP6_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_6_VECT_NUM);
    #endif   /* End USBFS_EP6_ISR_REMOVE */
    #if(USBFS_EP7_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_7_VECT_NUM);
    #endif   /* End USBFS_EP7_ISR_REMOVE */
    #if(USBFS_EP8_ISR_REMOVE == 0u)
        CyIntDisable(USBFS_EP_8_VECT_NUM);
    #endif   /* End USBFS_EP8_ISR_REMOVE */

    /* Clear all of the component data */
    USBFS_configuration = 0u;
    USBFS_interfaceNumber = 0u;
    USBFS_configurationChanged = 0u;
    USBFS_deviceAddress  = 0u;
    USBFS_deviceStatus = 0u;
    USBFS_initVar = 0u;

}


/*******************************************************************************
* Function Name: USBFS_CheckActivity
********************************************************************************
*
* Summary:
*  Returns the activity status of the bus.  Clears the status hardware to
*  provide fresh activity status on the next call of this routine.
*
* Parameters:
*  None.
*
* Return:
*  1 - If bus activity was detected since the last call to this function
*  0 - If bus activity not was detected since the last call to this function
*
*******************************************************************************/
uint8 USBFS_CheckActivity(void) 
{
    uint8 r;

    r = CY_GET_REG8(USBFS_CR1_PTR);
    CY_SET_REG8(USBFS_CR1_PTR, (r & ~USBFS_CR1_BUS_ACTIVITY));

    return((r & USBFS_CR1_BUS_ACTIVITY) >> USBFS_CR1_BUS_ACTIVITY_SHIFT);
}


/*******************************************************************************
* Function Name: USBFS_GetConfiguration
********************************************************************************
*
* Summary:
*  Returns the current configuration setting
*
* Parameters:
*  None.
*
* Return:
*  configuration.
*
*******************************************************************************/
uint8 USBFS_GetConfiguration(void) 
{
    return(USBFS_configuration);
}


/*******************************************************************************
* Function Name: USBFS_IsConfigurationChanged
********************************************************************************
*
* Summary:
*  Returns the clear on read configuration state. It is usefull when PC send
*  double SET_CONFIGURATION request with same configuration number.
*
* Parameters:
*  None.
*
* Return:
*  Not zero value when new configuration has been changed, otherwise zero is
*  returned.
*
* Global variables:
*   USBFS_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*
*******************************************************************************/
uint8 USBFS_IsConfigurationChanged(void) 
{
    uint8 res = 0u;

    if(USBFS_configurationChanged != 0u)
    {
        res = USBFS_configurationChanged;
        USBFS_configurationChanged = 0u;
    }

    return(res);
}


/*******************************************************************************
* Function Name: USBFS_GetInterfaceSetting
********************************************************************************
*
* Summary:
*  Returns the alternate setting from current interface
*
* Parameters:
*  uint8 interfaceNumber, interface number
*
* Return:
*  Alternate setting.
*
*******************************************************************************/
uint8  USBFS_GetInterfaceSetting(uint8 interfaceNumber)
                                                    
{
    return(USBFS_interfaceSetting[interfaceNumber]);
}


/*******************************************************************************
* Function Name: USBFS_GetEPState
********************************************************************************
*
* Summary:
*  Returned the state of the requested endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*
* Return:
*  State of the requested endpoint.
*
*******************************************************************************/
uint8 USBFS_GetEPState(uint8 epNumber) 
{
    return(USBFS_EP[epNumber].apiEpState);
}


/*******************************************************************************
* Function Name: USBFS_GetEPCount
********************************************************************************
*
* Summary:
*  This function supports Data Endpoints only(EP1-EP8).
*  Returns the transfer count for the requested endpoint.  The value from
*  the count registers includes 2 counts for the two byte checksum of the
*  packet.  This function subtracts the two counts.
*
* Parameters:
*  epNumber: Data Endpoint Number.
*            Valid values are between 1 and 8.
*
* Return:
*  Returns the current byte count from the specified endpoin or 0 for an
*  invalid endpoint.
*
*******************************************************************************/
uint16 USBFS_GetEPCount(uint8 epNumber) 
{
    uint8 ri;
    uint16 count = 0u;

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);

        count = ((uint16)((CY_GET_REG8(&USBFS_SIE_EP1_CNT0_PTR[ri]) & USBFS_EPX_CNT0_MASK) << 8u)
                         | CY_GET_REG8(&USBFS_SIE_EP1_CNT1_PTR[ri]))
                         - USBFS_EPX_CNTX_CRC_COUNT;
    }
    return(count);
}


#if(USBFS_EP_MM != USBFS__EP_MANUAL)


    /*******************************************************************************
    * Function Name: USBFS_InitEP_DMA
    ********************************************************************************
    *
    * Summary: This function allocate and initializes a EP DMA chanel to be used
    *     by the USBFS_LoadInEP() or USBFS_ReadOutEP() APIs.
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number.
    *            Valid values are between 1 and 8.
    *  *pData: A pointer to a data array which will be related to the EP transfers
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USBFS_InitEP_DMA(uint8 epNumber, uint8 *pData) 
    {
        uint16 src;
        uint16 dst;
        #if (defined(__C51__))          /* PSoC 3 - Source is Flash */
            src = HI16(CYDEV_SRAM_BASE);
            dst = HI16(CYDEV_PERIPH_BASE);
            pData = pData;
        #else                           /* PSoC 5 */
            if((USBFS_EP[epNumber].addr & USBFS_DIR_IN) != 0u )
            {   /* for the IN EP source is the flash memory buffer */
                src = HI16(pData);
                dst = HI16(CYDEV_PERIPH_BASE);
            }
            else
            {   /* for the OUT EP source is the SIE register */
                src = HI16(CYDEV_PERIPH_BASE);
                dst = HI16(pData);
            }
        #endif  /* End C51 */
        switch(epNumber)
        {
            case USBFS_EP1:
                #if(USBFS_DMA1_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep1_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA1_REMOVE */
                break;
            case USBFS_EP2:
                #if(USBFS_DMA2_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep2_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA2_REMOVE */
                break;
            case USBFS_EP3:
                #if(USBFS_DMA3_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep3_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA3_REMOVE */
                break;
            case USBFS_EP4:
                #if(USBFS_DMA4_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep4_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA4_REMOVE */
                break;
            case USBFS_EP5:
                #if(USBFS_DMA5_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep5_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA5_REMOVE */
                break;
            case USBFS_EP6:
                #if(USBFS_DMA6_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep6_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA6_REMOVE */
                break;
            case USBFS_EP7:
                #if(USBFS_DMA7_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep7_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA7_REMOVE */
                break;
            case USBFS_EP8:
                #if(USBFS_DMA8_REMOVE == 0u)
                    USBFS_DmaChan[epNumber] = USBFS_ep8_DmaInitialize(
                        USBFS_DMA_BYTES_PER_BURST, USBFS_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USBFS_DMA8_REMOVE */
                break;
            default:
                /* Do not support EP0 DMA transfers */
                break;
        }
        if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
        {
            USBFS_DmaTd[epNumber] = CyDmaTdAllocate();
        }
    }


    /*******************************************************************************
    * Function Name: USBFS_Stop_DMA
    ********************************************************************************
    *
    * Summary: Stops and free DMA
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number or
    *           USBFS_MAX_EP to stop all DMAs
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USBFS_Stop_DMA(uint8 epNumber) 
    {
        uint8 i;
        i = (epNumber < USBFS_MAX_EP) ? epNumber : USBFS_EP1;
        do
        {
            if(USBFS_DmaTd[i] != DMA_INVALID_TD)
            {
                CyDmaChDisable(USBFS_DmaChan[i]);
                CyDmaTdFree(USBFS_DmaTd[i]);
                USBFS_DmaTd[i] = DMA_INVALID_TD;
            }
            i++;
        }while((i < USBFS_MAX_EP) && (epNumber == USBFS_MAX_EP));
    }

#endif /* End USBFS_EP_MM != USBFS__EP_MANUAL */


/*******************************************************************************
* Function Name: USBFS_LoadInEP
********************************************************************************
*
* Summary:
*  Loads and enables the specified USB data endpoint for an IN interrupt or bulk
*  transfer.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  *pData: A pointer to a data array from which the data for the endpoint space
*          is loaded.
*  length: The number of bytes to transfer from the array and then send as a
*          result of an IN request. Valid values are between 0 and 512.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_LoadInEP(uint8 epNumber, uint8 *pData, uint16 length)
                                                                        
{
    uint8 ri;
    uint8 *p;
    #if(USBFS_EP_MM == USBFS__EP_MANUAL)
        uint16 i;
    #endif /* End USBFS_EP_MM == USBFS__EP_MANUAL */

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);
        p = (uint8 *)&USBFS_ARB_RW1_DR_PTR[ri];

        #if(USBFS_EP_MM != USBFS__EP_DMAAUTO)
            /* Limits length to available buffer space, auto MM could send packets up to 1024 bytes */
            if(length > USBFS_EPX_DATA_BUF_MAX - USBFS_EP[epNumber].buffOffset)
            {
                length = USBFS_EPX_DATA_BUF_MAX - USBFS_EP[epNumber].buffOffset;
            }
        #endif /* End USBFS_EP_MM != USBFS__EP_DMAAUTO */

        /* Set the count and data toggle */
        CY_SET_REG8(&USBFS_SIE_EP1_CNT0_PTR[ri], (length >> 8u) | (USBFS_EP[epNumber].epToggle));
        CY_SET_REG8(&USBFS_SIE_EP1_CNT1_PTR[ri],  length & 0xFFu);

        #if(USBFS_EP_MM == USBFS__EP_MANUAL)
            if(pData != NULL)
            {
                /* Copy the data using the arbiter data register */
                for (i = 0u; i < length; i++)
                {
                    CY_SET_REG8(p, pData[i]);
                }
            }
            USBFS_EP[epNumber].apiEpState = USBFS_NO_EVENT_PENDING;
            /* Write the Mode register */
            USBFS_SIE_EP1_CR0_PTR[ri] = USBFS_EP[epNumber].epMode;
        #else
            /*Init DMA if it was not initialized */
            if(USBFS_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                USBFS_InitEP_DMA(epNumber, pData);
            }
        #endif /* End USBFS_EP_MM == USBFS__EP_MANUAL */

        #if(USBFS_EP_MM == USBFS__EP_DMAMANUAL)
            if((pData != NULL) && (length > 0))
            {

                /* Enable DMA in mode2 for transfering data */
                CyDmaChDisable(USBFS_DmaChan[epNumber]);
                CyDmaTdSetConfiguration(USBFS_DmaTd[epNumber], length, DMA_INVALID_TD,\
                                                                                    TD_TERMIN_EN | TD_INC_SRC_ADR);
                CyDmaTdSetAddress(USBFS_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Enable the DMA */
                CyDmaChSetInitialTd(USBFS_DmaChan[epNumber], USBFS_DmaTd[epNumber]);
                CyDmaChEnable(USBFS_DmaChan[epNumber], 1);
                /* Generate DMA request */
                USBFS_ARB_EP1_CFG_PTR[ri] |= USBFS_ARB_EPX_CFG_DMA_REQ;
                USBFS_ARB_EP1_CFG_PTR[ri] &= ~USBFS_ARB_EPX_CFG_DMA_REQ;
                /* Mode register will be writen in arb ISR after DMA transfer copmlete */
            }
            else
            {
                /* When zero-length packet - write the Mode register directly */
                USBFS_SIE_EP1_CR0_PTR[ri] = USBFS_EP[epNumber].epMode;
            }
        #endif /* End USBFS_EP_MM == USBFS__EP_DMAMANUAL */

        #if(USBFS_EP_MM == USBFS__EP_DMAAUTO)
            if(pData != NULL)
            {
                /* Enable DMA in mode3 for transfering data */
                CyDmaChDisable(USBFS_DmaChan[epNumber]);
                CyDmaTdSetConfiguration(USBFS_DmaTd[epNumber], length, USBFS_DmaTd[epNumber],\
                                                                                    TD_TERMIN_EN | TD_INC_SRC_ADR);
                CyDmaTdSetAddress(USBFS_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
                CyDmaClearPendingDrq(USBFS_DmaChan[epNumber]);
                /* Enable the DMA */
                CyDmaChSetInitialTd(USBFS_DmaChan[epNumber], USBFS_DmaTd[epNumber]);
                CyDmaChEnable(USBFS_DmaChan[epNumber], 1);
            }
            else
            {
                USBFS_EP[epNumber].apiEpState = USBFS_NO_EVENT_PENDING;
                if(length > 0)
                {
                    /* Set Data ready status, This will generate DMA request */
                    USBFS_ARB_EP1_CFG_PTR[ri] |= USBFS_ARB_EPX_CFG_IN_DATA_RDY;
                    /* Mode register will be writen in arb ISR(In Buffer Full) after first DMA transfer copmlete */
                }
                else
                {
                    /* When zero-length packet - write the Mode register directly */
                    USBFS_SIE_EP1_CR0_PTR[ri] = USBFS_EP[epNumber].epMode;
                }
            }
        #endif /* End USBFS_EP_MM == USBFS__EP_DMAAUTO */

    }
}


/*******************************************************************************
* Function Name: USBFS_ReadOutEP
********************************************************************************
*
* Summary:
*  Read data from an endpoint.  The application must call
*  USBFS_GetEPState to see if an event is pending.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  pData: A pointer to a data array from which the data for the endpoint space
*         is loaded.
*  length: The number of bytes to transfer from the USB Out enpoint and loads
*          it into data array. Valid values are between 0 and 1023. The function
*          moves fewer than the requested number of bytes if the host sends
*          fewer bytes than requested.
*
* Returns:
*  Number of bytes received, 0 for an invalid endpoint.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 USBFS_ReadOutEP(uint8 epNumber, uint8 *pData, uint16 length)
                                                                        
{
    uint8 ri;
    uint8 *p;
    #if(USBFS_EP_MM == USBFS__EP_MANUAL)
        uint16 i;
    #endif /* End USBFS_EP_MM == USBFS__EP_MANUAL */
    #if(USBFS_EP_MM != USBFS__EP_DMAAUTO)
        uint16 xferCount;
    #endif /* End USBFS_EP_MM != $INSTANCE_NAME`__EP_DMAAUTO */

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP) && (pData != NULL))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);
        p = (uint8 *)&USBFS_ARB_RW1_DR_PTR[ri];

        #if(USBFS_EP_MM != USBFS__EP_DMAAUTO)
            /* Determine which is smaller the requested data or the available data */
            xferCount = USBFS_GetEPCount(epNumber);
            if (length > xferCount)
            {
                length = xferCount;
            }
        #endif /* End USBFS_EP_MM != USBFS__EP_DMAAUTO */

        #if(USBFS_EP_MM == USBFS__EP_MANUAL)
            /* Copy the data using the arbiter data register */
            for (i = 0u; i < length; i++)
            {
                pData[i] = CY_GET_REG8(p);
            }

            /* (re)arming of OUT endpoint */
            USBFS_EnableOutEP(epNumber);
        #else
            /*Init DMA if it was not initialized */
            if(USBFS_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                USBFS_InitEP_DMA(epNumber, pData);
            }
        #endif /* End USBFS_EP_MM == USBFS__EP_MANUAL */

        #if(USBFS_EP_MM == USBFS__EP_DMAMANUAL)
            /* Enable DMA in mode2 for transfering data */
            CyDmaChDisable(USBFS_DmaChan[epNumber]);
            CyDmaTdSetConfiguration(USBFS_DmaTd[epNumber], length, DMA_INVALID_TD,
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            CyDmaTdSetAddress(USBFS_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));
            /* Enable the DMA */
            CyDmaChSetInitialTd(USBFS_DmaChan[epNumber], USBFS_DmaTd[epNumber]);
            CyDmaChEnable(USBFS_DmaChan[epNumber], 1);

            /* Generate DMA request */
            USBFS_ARB_EP1_CFG_PTR[ri] |= USBFS_ARB_EPX_CFG_DMA_REQ;
            USBFS_ARB_EP1_CFG_PTR[ri] &= ~USBFS_ARB_EPX_CFG_DMA_REQ;
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End USBFS_EP_MM == USBFS__EP_DMAMANUAL */

        #if(USBFS_EP_MM == USBFS__EP_DMAAUTO)
            /* Enable DMA in mode3 for transfering data */
            CyDmaChDisable(USBFS_DmaChan[epNumber]);
            CyDmaTdSetConfiguration(USBFS_DmaTd[epNumber], length, USBFS_DmaTd[epNumber],
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            CyDmaTdSetAddress(USBFS_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));

            /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
            CyDmaClearPendingDrq(USBFS_DmaChan[epNumber]);
            /* Enable the DMA */
            CyDmaChSetInitialTd(USBFS_DmaChan[epNumber], USBFS_DmaTd[epNumber]);
            CyDmaChEnable(USBFS_DmaChan[epNumber], 1);
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End USBFS_EP_MM == USBFS__EP_DMAAUTO */

    }
    else
    {
        length = 0;
    }

    return(length);
}


/*******************************************************************************
* Function Name: USBFS_EnableOutEP
********************************************************************************
*
* Summary:
*  This function enables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*   None.
*
* Global variables:
*  USBFS_EP[epNumber].apiEpState - set to NO_EVENT_PENDING
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_EnableOutEP(uint8 epNumber) 
{
    uint8 ri;

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);
        USBFS_EP[epNumber].apiEpState = USBFS_NO_EVENT_PENDING;
        /* Write the Mode register */
        CY_SET_REG8(&USBFS_SIE_EP1_CR0_PTR[ri], USBFS_EP[epNumber].epMode);
    }
}


/*******************************************************************************
* Function Name: USBFS_DisableOutEP
********************************************************************************
*
* Summary:
*  This function disables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*  None.
*
*******************************************************************************/
void USBFS_DisableOutEP(uint8 epNumber) 
{
    uint8 ri ;

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);
        /* Write the Mode register */
        CY_SET_REG8(&USBFS_SIE_EP1_CR0_PTR[ri], USBFS_MODE_NAK_OUT);
    }
}


/*******************************************************************************
* Function Name: USBFS_Force
********************************************************************************
*
* Summary:
*  Forces the bus state
*
* Parameters:
*  bState
*    USBFS_FORCE_J
*    USBFS_FORCE_K
*    USBFS_FORCE_SE0
*    USBFS_FORCE_NONE
*
* Return:
*  None.
*
*******************************************************************************/
void USBFS_Force(uint8 bState) 
{
    CY_SET_REG8(USBFS_USBIO_CR0_PTR, bState);
}


/*******************************************************************************
* Function Name: USBFS_GetEPAckState
********************************************************************************
*
* Summary:
*  Returns the ACK of the CR0 Register (ACKD)
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Returns
*  0 if nothing has been ACKD, non-=zero something has been ACKD
*
*******************************************************************************/
uint8 USBFS_GetEPAckState(uint8 epNumber) 
{
    uint8 ri;
    uint8 cr = 0;

    if((epNumber > USBFS_EP0) && (epNumber < USBFS_MAX_EP))
    {
        ri = ((epNumber - USBFS_EP1) << USBFS_EPX_CNTX_ADDR_SHIFT);
        cr = CY_GET_REG8(&USBFS_SIE_EP1_CR0_PTR[ri]) & USBFS_MODE_ACKD;
    }

    return(cr);
}


/*******************************************************************************
* Function Name: USBFS_SetPowerStatus
********************************************************************************
*
* Summary:
*  Sets the device power status for reporting in the Get Device Status
*  request
*
* Parameters:
*  powerStatus: USBFS_DEVICE_STATUS_BUS_POWERED(0) - Bus Powered,
*               USBFS_DEVICE_STATUS_SELF_POWERED(1) - Self Powered
*
* Return:
*   None.
*
* Global variables:
*  USBFS_deviceStatus - set power status
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USBFS_SetPowerStatus(uint8 powerStatus) 
{
    if (powerStatus != USBFS_DEVICE_STATUS_BUS_POWERED)
    {
        USBFS_deviceStatus |=  USBFS_DEVICE_STATUS_SELF_POWERED;
    }
    else
    {
        USBFS_deviceStatus &=  ~USBFS_DEVICE_STATUS_SELF_POWERED;
    }
}


#if (USBFS_MON_VBUS == 1u)

    /*******************************************************************************
    * Function Name: USBFS_VBusPresent
    ********************************************************************************
    *
    * Summary:
    *  Determines VBUS presence for Self Powered Devices.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  1 if VBUS is present, otherwise 0.
    *
    *******************************************************************************/
    uint8 USBFS_VBusPresent(void) 
    {
        return((CY_GET_REG8(USBFS_VBUS_PS_PTR) & USBFS_VBUS_MASK) ? 1u : 0u);
    }

#endif /* USBFS_MON_VBUS */


/*******************************************************************************
* Function Name: USBFS_RWUEnabled
********************************************************************************
*
* Summary:
*  Returns TRUE if Remote Wake Up is enabled, otherwise FALSE
*
* Parameters:
*   None.
*
* Return:
*  TRUE -  Remote Wake Up Enabled
*  FALSE - Remote Wake Up Disabled
*
* Global variables:
*  USBFS_deviceStatus - checked to determine remote status
*
*******************************************************************************/
uint8 USBFS_RWUEnabled(void) 
{
    uint8 result = USBFS_FALSE;
    if((USBFS_deviceStatus & USBFS_DEVICE_STATUS_REMOTE_WAKEUP) != 0u)
    {
        result = USBFS_TRUE;
    }

    return(result);
}


/* [] END OF FILE */
