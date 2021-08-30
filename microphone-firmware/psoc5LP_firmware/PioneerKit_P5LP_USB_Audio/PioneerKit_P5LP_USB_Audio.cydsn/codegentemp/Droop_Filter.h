/*******************************************************************************
* File Name: Droop_Filter.h
* Version 2.10
*
* Description:
*  This header file contains definitions associated with the FILT component.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(Droop_Filter_H) /* FILT Header File */
#define Droop_Filter_H

#include "cyfitter.h"
#include "CyLib.h"


/***************************************
*     Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct _Droop_Filter_backupStruct 
{
    uint8 enableState;
    uint8 cr;
    uint8 sr;
    uint8 sema;
}   Droop_Filter_BACKUP_STRUCT;


/***************************************
* FILT component function prototypes.
****************************************/

void   Droop_Filter_Start(void) ;
void   Droop_Filter_Stop(void) ;
uint8 Droop_Filter_Read8(uint8 channel) ;
uint16 Droop_Filter_Read16(uint8 channel) ;
uint32 Droop_Filter_Read24(uint8 channel) ;
void Droop_Filter_Write8(uint8 channel, uint8 sample) ;
void Droop_Filter_Write16(uint8 channel, uint16 sample) ;
void Droop_Filter_Write24(uint8 channel, uint32 sample) ;
void Droop_Filter_Sleep(void) ;
void Droop_Filter_Wakeup(void) ;
void Droop_Filter_SaveConfig(void) ;
void Droop_Filter_RestoreConfig(void) ;
void Droop_Filter_Init(void) ;
void Droop_Filter_Enable(void) ;
void Droop_Filter_SetCoherency(uint8 channel, uint8 byteSelect) ;
void Droop_Filter_RestoreACURam(void) ;


/*****************************************
* FILT component API Constants.
******************************************/

/* Channel Definitions */
#define Droop_Filter_CHANNEL_A             (0u)
#define Droop_Filter_CHANNEL_B             (1u)

#define Droop_Filter_CHANNEL_A_INTR        (0x08u)
#define Droop_Filter_CHANNEL_B_INTR        (0x10u)

#define Droop_Filter_ALL_INTR              (0xf8u)

#define Droop_Filter_SIGN_BIT              (0x00800000u)
#define Droop_Filter_SIGN_BYTE             (0xFF000000u)

/* Component's enable/disable state */
#define Droop_Filter_ENABLED               (0x01u)
#define Droop_Filter_DISABLED              (0x00u)

/* SetCoherency API constants */
#define Droop_Filter_KEY_LOW               (0x00u)
#define Droop_Filter_KEY_MID               (0x01u)
#define Droop_Filter_KEY_HIGH              (0x02u)


/*******************************************************************************
* FILT component macros.
*******************************************************************************/

#define Droop_Filter_ClearInterruptSource() \
   (Droop_Filter_SR_REG = Droop_Filter_ALL_INTR )

#define Droop_Filter_IsInterruptChannelA() \
    (Droop_Filter_SR_REG & Droop_Filter_CHANNEL_A_INTR)

#define Droop_Filter_IsInterruptChannelB() \
    (Droop_Filter_SR_REG & Droop_Filter_CHANNEL_B_INTR)


/*******************************************************************************
* FILT component DFB registers.
*******************************************************************************/

/* DFB Status register */
#define Droop_Filter_SR_REG             (* (reg8 *) Droop_Filter_DFB__SR)
#define Droop_Filter_SR_PTR             (  (reg8 *) Droop_Filter_DFB__SR)

/* DFB Control register */
#define Droop_Filter_CR_REG             (* (reg8 *) Droop_Filter_DFB__CR)
#define Droop_Filter_CR_PTR             (  (reg8 *) Droop_Filter_DFB__CR)


/*******************************************************************************
* DFB.COHER bit field defines.
*******************************************************************************/

/* STAGEA key coherency mask */
#define Droop_Filter_STAGEA_COHER_MASK    0x03u

/* HOLDA key coherency mask */
#define Droop_Filter_HOLDA_COHER_MASK    (0x03u << 4)

/* STAGEB key coherency mask */
#define Droop_Filter_STAGEB_COHER_MASK    0x0Cu

/* HOLDB key coherency mask */
#define Droop_Filter_HOLDB_COHER_MASK    (0x0Cu << 4)

#endif /* End FILT Header File */


/* [] END OF FILE */
