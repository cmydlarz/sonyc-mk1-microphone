/*******************************************************************************
* File Name: UART_RX.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UART_RX_H) /* Pins UART_RX_H */
#define CY_PINS_UART_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "UART_RX_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 UART_RX__PORT == 15 && ((UART_RX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    UART_RX_Write(uint8 value) ;
void    UART_RX_SetDriveMode(uint8 mode) ;
uint8   UART_RX_ReadDataReg(void) ;
uint8   UART_RX_Read(void) ;
uint8   UART_RX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UART_RX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define UART_RX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define UART_RX_DM_RES_UP          PIN_DM_RES_UP
#define UART_RX_DM_RES_DWN         PIN_DM_RES_DWN
#define UART_RX_DM_OD_LO           PIN_DM_OD_LO
#define UART_RX_DM_OD_HI           PIN_DM_OD_HI
#define UART_RX_DM_STRONG          PIN_DM_STRONG
#define UART_RX_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define UART_RX_MASK               UART_RX__MASK
#define UART_RX_SHIFT              UART_RX__SHIFT
#define UART_RX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UART_RX_PS                     (* (reg8 *) UART_RX__PS)
/* Data Register */
#define UART_RX_DR                     (* (reg8 *) UART_RX__DR)
/* Port Number */
#define UART_RX_PRT_NUM                (* (reg8 *) UART_RX__PRT) 
/* Connect to Analog Globals */                                                  
#define UART_RX_AG                     (* (reg8 *) UART_RX__AG)                       
/* Analog MUX bux enable */
#define UART_RX_AMUX                   (* (reg8 *) UART_RX__AMUX) 
/* Bidirectional Enable */                                                        
#define UART_RX_BIE                    (* (reg8 *) UART_RX__BIE)
/* Bit-mask for Aliased Register Access */
#define UART_RX_BIT_MASK               (* (reg8 *) UART_RX__BIT_MASK)
/* Bypass Enable */
#define UART_RX_BYP                    (* (reg8 *) UART_RX__BYP)
/* Port wide control signals */                                                   
#define UART_RX_CTL                    (* (reg8 *) UART_RX__CTL)
/* Drive Modes */
#define UART_RX_DM0                    (* (reg8 *) UART_RX__DM0) 
#define UART_RX_DM1                    (* (reg8 *) UART_RX__DM1)
#define UART_RX_DM2                    (* (reg8 *) UART_RX__DM2) 
/* Input Buffer Disable Override */
#define UART_RX_INP_DIS                (* (reg8 *) UART_RX__INP_DIS)
/* LCD Common or Segment Drive */
#define UART_RX_LCD_COM_SEG            (* (reg8 *) UART_RX__LCD_COM_SEG)
/* Enable Segment LCD */
#define UART_RX_LCD_EN                 (* (reg8 *) UART_RX__LCD_EN)
/* Slew Rate Control */
#define UART_RX_SLW                    (* (reg8 *) UART_RX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define UART_RX_PRTDSI__CAPS_SEL       (* (reg8 *) UART_RX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define UART_RX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) UART_RX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define UART_RX_PRTDSI__OE_SEL0        (* (reg8 *) UART_RX__PRTDSI__OE_SEL0) 
#define UART_RX_PRTDSI__OE_SEL1        (* (reg8 *) UART_RX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define UART_RX_PRTDSI__OUT_SEL0       (* (reg8 *) UART_RX__PRTDSI__OUT_SEL0) 
#define UART_RX_PRTDSI__OUT_SEL1       (* (reg8 *) UART_RX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define UART_RX_PRTDSI__SYNC_OUT       (* (reg8 *) UART_RX__PRTDSI__SYNC_OUT) 


#if defined(UART_RX__INTSTAT)  /* Interrupt Registers */

    #define UART_RX_INTSTAT                (* (reg8 *) UART_RX__INTSTAT)
    #define UART_RX_SNAP                   (* (reg8 *) UART_RX__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_UART_RX_H */


/* [] END OF FILE */
