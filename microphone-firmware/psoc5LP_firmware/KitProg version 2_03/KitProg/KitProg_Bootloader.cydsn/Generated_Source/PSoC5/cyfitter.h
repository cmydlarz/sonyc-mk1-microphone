#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* Pin_PSoC4A_XRES */
#define Pin_PSoC4A_XRES__0__MASK 0x10u
#define Pin_PSoC4A_XRES__0__PC CYREG_PRT2_PC4
#define Pin_PSoC4A_XRES__0__PORT 2u
#define Pin_PSoC4A_XRES__0__SHIFT 4
#define Pin_PSoC4A_XRES__AG CYREG_PRT2_AG
#define Pin_PSoC4A_XRES__AMUX CYREG_PRT2_AMUX
#define Pin_PSoC4A_XRES__BIE CYREG_PRT2_BIE
#define Pin_PSoC4A_XRES__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_PSoC4A_XRES__BYP CYREG_PRT2_BYP
#define Pin_PSoC4A_XRES__CTL CYREG_PRT2_CTL
#define Pin_PSoC4A_XRES__DM0 CYREG_PRT2_DM0
#define Pin_PSoC4A_XRES__DM1 CYREG_PRT2_DM1
#define Pin_PSoC4A_XRES__DM2 CYREG_PRT2_DM2
#define Pin_PSoC4A_XRES__DR CYREG_PRT2_DR
#define Pin_PSoC4A_XRES__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_PSoC4A_XRES__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_PSoC4A_XRES__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_PSoC4A_XRES__MASK 0x10u
#define Pin_PSoC4A_XRES__PORT 2u
#define Pin_PSoC4A_XRES__PRT CYREG_PRT2_PRT
#define Pin_PSoC4A_XRES__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_PSoC4A_XRES__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_PSoC4A_XRES__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_PSoC4A_XRES__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_PSoC4A_XRES__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_PSoC4A_XRES__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_PSoC4A_XRES__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_PSoC4A_XRES__PS CYREG_PRT2_PS
#define Pin_PSoC4A_XRES__SHIFT 4
#define Pin_PSoC4A_XRES__SLW CYREG_PRT2_SLW

/* USBFS_bus_reset */
#define USBFS_bus_reset__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_bus_reset__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_bus_reset__INTC_MASK 0x800000u
#define USBFS_bus_reset__INTC_NUMBER 23u
#define USBFS_bus_reset__INTC_PRIOR_NUM 7u
#define USBFS_bus_reset__INTC_PRIOR_REG CYREG_NVIC_PRI_23
#define USBFS_bus_reset__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_bus_reset__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Pin_Status_LED */
#define Pin_Status_LED__0__MASK 0x02u
#define Pin_Status_LED__0__PC CYREG_PRT3_PC1
#define Pin_Status_LED__0__PORT 3u
#define Pin_Status_LED__0__SHIFT 1
#define Pin_Status_LED__AG CYREG_PRT3_AG
#define Pin_Status_LED__AMUX CYREG_PRT3_AMUX
#define Pin_Status_LED__BIE CYREG_PRT3_BIE
#define Pin_Status_LED__BIT_MASK CYREG_PRT3_BIT_MASK
#define Pin_Status_LED__BYP CYREG_PRT3_BYP
#define Pin_Status_LED__CTL CYREG_PRT3_CTL
#define Pin_Status_LED__DM0 CYREG_PRT3_DM0
#define Pin_Status_LED__DM1 CYREG_PRT3_DM1
#define Pin_Status_LED__DM2 CYREG_PRT3_DM2
#define Pin_Status_LED__DR CYREG_PRT3_DR
#define Pin_Status_LED__INP_DIS CYREG_PRT3_INP_DIS
#define Pin_Status_LED__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define Pin_Status_LED__LCD_EN CYREG_PRT3_LCD_EN
#define Pin_Status_LED__MASK 0x02u
#define Pin_Status_LED__PORT 3u
#define Pin_Status_LED__PRT CYREG_PRT3_PRT
#define Pin_Status_LED__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define Pin_Status_LED__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define Pin_Status_LED__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define Pin_Status_LED__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define Pin_Status_LED__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define Pin_Status_LED__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define Pin_Status_LED__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define Pin_Status_LED__PS CYREG_PRT3_PS
#define Pin_Status_LED__SHIFT 1
#define Pin_Status_LED__SLW CYREG_PRT3_SLW

/* USBFS_arb_int */
#define USBFS_arb_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_arb_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_arb_int__INTC_MASK 0x400000u
#define USBFS_arb_int__INTC_NUMBER 22u
#define USBFS_arb_int__INTC_PRIOR_NUM 7u
#define USBFS_arb_int__INTC_PRIOR_REG CYREG_NVIC_PRI_22
#define USBFS_arb_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_arb_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_ord_int */
#define USBFS_ord_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_ord_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_ord_int__INTC_MASK 0x2000000u
#define USBFS_ord_int__INTC_NUMBER 25u
#define USBFS_ord_int__INTC_PRIOR_NUM 7u
#define USBFS_ord_int__INTC_PRIOR_REG CYREG_NVIC_PRI_25
#define USBFS_ord_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_ord_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_sof_int */
#define USBFS_sof_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_sof_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_sof_int__INTC_MASK 0x200000u
#define USBFS_sof_int__INTC_NUMBER 21u
#define USBFS_sof_int__INTC_PRIOR_NUM 7u
#define USBFS_sof_int__INTC_PRIOR_REG CYREG_NVIC_PRI_21
#define USBFS_sof_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_sof_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_dp_int */
#define USBFS_dp_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_dp_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_dp_int__INTC_MASK 0x1000u
#define USBFS_dp_int__INTC_NUMBER 12u
#define USBFS_dp_int__INTC_PRIOR_NUM 7u
#define USBFS_dp_int__INTC_PRIOR_REG CYREG_NVIC_PRI_12
#define USBFS_dp_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_dp_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Clock_LED_1 */
#define Clock_LED_1__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define Clock_LED_1__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define Clock_LED_1__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define Clock_LED_1__CFG2_SRC_SEL_MASK 0x07u
#define Clock_LED_1__INDEX 0x00u
#define Clock_LED_1__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_LED_1__PM_ACT_MSK 0x01u
#define Clock_LED_1__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_LED_1__PM_STBY_MSK 0x01u

/* PWM_PWMUDB */
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B1_UDB04_05_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B1_UDB04_05_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B1_UDB04_05_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B1_UDB04_05_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG CYREG_B1_UDB04_05_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B1_UDB04_05_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B1_UDB04_05_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B1_UDB04_05_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK 0x80u
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS 7
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG CYREG_B1_UDB04_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG CYREG_B1_UDB04_ST_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG CYREG_B1_UDB04_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG CYREG_B1_UDB04_ST_CTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK 0x80u
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B1_UDB04_MSK_ACTL
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG CYREG_B1_UDB04_MSK
#define PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B1_UDB04_MSK_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG CYREG_B1_UDB04_05_A0
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG CYREG_B1_UDB04_05_A1
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG CYREG_B1_UDB04_05_D0
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG CYREG_B1_UDB04_05_D1
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG CYREG_B1_UDB04_05_F0
#define PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG CYREG_B1_UDB04_05_F1
#define PWM_PWMUDB_sP16_pwmdp_u0__A0_A1_REG CYREG_B1_UDB04_A0_A1
#define PWM_PWMUDB_sP16_pwmdp_u0__A0_REG CYREG_B1_UDB04_A0
#define PWM_PWMUDB_sP16_pwmdp_u0__A1_REG CYREG_B1_UDB04_A1
#define PWM_PWMUDB_sP16_pwmdp_u0__D0_D1_REG CYREG_B1_UDB04_D0_D1
#define PWM_PWMUDB_sP16_pwmdp_u0__D0_REG CYREG_B1_UDB04_D0
#define PWM_PWMUDB_sP16_pwmdp_u0__D1_REG CYREG_B1_UDB04_D1
#define PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u0__F0_F1_REG CYREG_B1_UDB04_F0_F1
#define PWM_PWMUDB_sP16_pwmdp_u0__F0_REG CYREG_B1_UDB04_F0
#define PWM_PWMUDB_sP16_pwmdp_u0__F1_REG CYREG_B1_UDB04_F1
#define PWM_PWMUDB_sP16_pwmdp_u0__MSK_DP_AUX_CTL_REG CYREG_B1_UDB04_MSK_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u0__PER_DP_AUX_CTL_REG CYREG_B1_UDB04_MSK_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_A0_REG CYREG_B1_UDB05_06_A0
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_A1_REG CYREG_B1_UDB05_06_A1
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_D0_REG CYREG_B1_UDB05_06_D0
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_D1_REG CYREG_B1_UDB05_06_D1
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB05_06_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_F0_REG CYREG_B1_UDB05_06_F0
#define PWM_PWMUDB_sP16_pwmdp_u1__16BIT_F1_REG CYREG_B1_UDB05_06_F1
#define PWM_PWMUDB_sP16_pwmdp_u1__A0_A1_REG CYREG_B1_UDB05_A0_A1
#define PWM_PWMUDB_sP16_pwmdp_u1__A0_REG CYREG_B1_UDB05_A0
#define PWM_PWMUDB_sP16_pwmdp_u1__A1_REG CYREG_B1_UDB05_A1
#define PWM_PWMUDB_sP16_pwmdp_u1__D0_D1_REG CYREG_B1_UDB05_D0_D1
#define PWM_PWMUDB_sP16_pwmdp_u1__D0_REG CYREG_B1_UDB05_D0
#define PWM_PWMUDB_sP16_pwmdp_u1__D1_REG CYREG_B1_UDB05_D1
#define PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG CYREG_B1_UDB05_ACTL
#define PWM_PWMUDB_sP16_pwmdp_u1__F0_F1_REG CYREG_B1_UDB05_F0_F1
#define PWM_PWMUDB_sP16_pwmdp_u1__F0_REG CYREG_B1_UDB05_F0
#define PWM_PWMUDB_sP16_pwmdp_u1__F1_REG CYREG_B1_UDB05_F1
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__MASK 0x01u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__POS 0
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB05_06_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_REG CYREG_B1_UDB05_06_ST
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__MASK 0x04u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__POS 2
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__MASK 0x08u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__POS 3
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__MASK 0x20u
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__POS 5
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK 0x2Du
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG CYREG_B1_UDB05_MSK
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG CYREG_B1_UDB05_ACTL
#define PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG CYREG_B1_UDB05_ST

/* USBFS_ep_0 */
#define USBFS_ep_0__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_ep_0__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_ep_0__INTC_MASK 0x1000000u
#define USBFS_ep_0__INTC_NUMBER 24u
#define USBFS_ep_0__INTC_PRIOR_NUM 7u
#define USBFS_ep_0__INTC_PRIOR_REG CYREG_NVIC_PRI_24
#define USBFS_ep_0__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_ep_0__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_ep_1 */
#define USBFS_ep_1__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_ep_1__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_ep_1__INTC_MASK 0x01u
#define USBFS_ep_1__INTC_NUMBER 0u
#define USBFS_ep_1__INTC_PRIOR_NUM 7u
#define USBFS_ep_1__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define USBFS_ep_1__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_ep_1__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_ep_2 */
#define USBFS_ep_2__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBFS_ep_2__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBFS_ep_2__INTC_MASK 0x02u
#define USBFS_ep_2__INTC_NUMBER 1u
#define USBFS_ep_2__INTC_PRIOR_NUM 7u
#define USBFS_ep_2__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define USBFS_ep_2__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBFS_ep_2__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* USBFS_USB */
#define USBFS_USB__ARB_CFG CYREG_USB_ARB_CFG
#define USBFS_USB__ARB_EP1_CFG CYREG_USB_ARB_EP1_CFG
#define USBFS_USB__ARB_EP1_INT_EN CYREG_USB_ARB_EP1_INT_EN
#define USBFS_USB__ARB_EP1_SR CYREG_USB_ARB_EP1_SR
#define USBFS_USB__ARB_EP2_CFG CYREG_USB_ARB_EP2_CFG
#define USBFS_USB__ARB_EP2_INT_EN CYREG_USB_ARB_EP2_INT_EN
#define USBFS_USB__ARB_EP2_SR CYREG_USB_ARB_EP2_SR
#define USBFS_USB__ARB_EP3_CFG CYREG_USB_ARB_EP3_CFG
#define USBFS_USB__ARB_EP3_INT_EN CYREG_USB_ARB_EP3_INT_EN
#define USBFS_USB__ARB_EP3_SR CYREG_USB_ARB_EP3_SR
#define USBFS_USB__ARB_EP4_CFG CYREG_USB_ARB_EP4_CFG
#define USBFS_USB__ARB_EP4_INT_EN CYREG_USB_ARB_EP4_INT_EN
#define USBFS_USB__ARB_EP4_SR CYREG_USB_ARB_EP4_SR
#define USBFS_USB__ARB_EP5_CFG CYREG_USB_ARB_EP5_CFG
#define USBFS_USB__ARB_EP5_INT_EN CYREG_USB_ARB_EP5_INT_EN
#define USBFS_USB__ARB_EP5_SR CYREG_USB_ARB_EP5_SR
#define USBFS_USB__ARB_EP6_CFG CYREG_USB_ARB_EP6_CFG
#define USBFS_USB__ARB_EP6_INT_EN CYREG_USB_ARB_EP6_INT_EN
#define USBFS_USB__ARB_EP6_SR CYREG_USB_ARB_EP6_SR
#define USBFS_USB__ARB_EP7_CFG CYREG_USB_ARB_EP7_CFG
#define USBFS_USB__ARB_EP7_INT_EN CYREG_USB_ARB_EP7_INT_EN
#define USBFS_USB__ARB_EP7_SR CYREG_USB_ARB_EP7_SR
#define USBFS_USB__ARB_EP8_CFG CYREG_USB_ARB_EP8_CFG
#define USBFS_USB__ARB_EP8_INT_EN CYREG_USB_ARB_EP8_INT_EN
#define USBFS_USB__ARB_EP8_SR CYREG_USB_ARB_EP8_SR
#define USBFS_USB__ARB_INT_EN CYREG_USB_ARB_INT_EN
#define USBFS_USB__ARB_INT_SR CYREG_USB_ARB_INT_SR
#define USBFS_USB__ARB_RW1_DR CYREG_USB_ARB_RW1_DR
#define USBFS_USB__ARB_RW1_RA CYREG_USB_ARB_RW1_RA
#define USBFS_USB__ARB_RW1_RA_MSB CYREG_USB_ARB_RW1_RA_MSB
#define USBFS_USB__ARB_RW1_WA CYREG_USB_ARB_RW1_WA
#define USBFS_USB__ARB_RW1_WA_MSB CYREG_USB_ARB_RW1_WA_MSB
#define USBFS_USB__ARB_RW2_DR CYREG_USB_ARB_RW2_DR
#define USBFS_USB__ARB_RW2_RA CYREG_USB_ARB_RW2_RA
#define USBFS_USB__ARB_RW2_RA_MSB CYREG_USB_ARB_RW2_RA_MSB
#define USBFS_USB__ARB_RW2_WA CYREG_USB_ARB_RW2_WA
#define USBFS_USB__ARB_RW2_WA_MSB CYREG_USB_ARB_RW2_WA_MSB
#define USBFS_USB__ARB_RW3_DR CYREG_USB_ARB_RW3_DR
#define USBFS_USB__ARB_RW3_RA CYREG_USB_ARB_RW3_RA
#define USBFS_USB__ARB_RW3_RA_MSB CYREG_USB_ARB_RW3_RA_MSB
#define USBFS_USB__ARB_RW3_WA CYREG_USB_ARB_RW3_WA
#define USBFS_USB__ARB_RW3_WA_MSB CYREG_USB_ARB_RW3_WA_MSB
#define USBFS_USB__ARB_RW4_DR CYREG_USB_ARB_RW4_DR
#define USBFS_USB__ARB_RW4_RA CYREG_USB_ARB_RW4_RA
#define USBFS_USB__ARB_RW4_RA_MSB CYREG_USB_ARB_RW4_RA_MSB
#define USBFS_USB__ARB_RW4_WA CYREG_USB_ARB_RW4_WA
#define USBFS_USB__ARB_RW4_WA_MSB CYREG_USB_ARB_RW4_WA_MSB
#define USBFS_USB__ARB_RW5_DR CYREG_USB_ARB_RW5_DR
#define USBFS_USB__ARB_RW5_RA CYREG_USB_ARB_RW5_RA
#define USBFS_USB__ARB_RW5_RA_MSB CYREG_USB_ARB_RW5_RA_MSB
#define USBFS_USB__ARB_RW5_WA CYREG_USB_ARB_RW5_WA
#define USBFS_USB__ARB_RW5_WA_MSB CYREG_USB_ARB_RW5_WA_MSB
#define USBFS_USB__ARB_RW6_DR CYREG_USB_ARB_RW6_DR
#define USBFS_USB__ARB_RW6_RA CYREG_USB_ARB_RW6_RA
#define USBFS_USB__ARB_RW6_RA_MSB CYREG_USB_ARB_RW6_RA_MSB
#define USBFS_USB__ARB_RW6_WA CYREG_USB_ARB_RW6_WA
#define USBFS_USB__ARB_RW6_WA_MSB CYREG_USB_ARB_RW6_WA_MSB
#define USBFS_USB__ARB_RW7_DR CYREG_USB_ARB_RW7_DR
#define USBFS_USB__ARB_RW7_RA CYREG_USB_ARB_RW7_RA
#define USBFS_USB__ARB_RW7_RA_MSB CYREG_USB_ARB_RW7_RA_MSB
#define USBFS_USB__ARB_RW7_WA CYREG_USB_ARB_RW7_WA
#define USBFS_USB__ARB_RW7_WA_MSB CYREG_USB_ARB_RW7_WA_MSB
#define USBFS_USB__ARB_RW8_DR CYREG_USB_ARB_RW8_DR
#define USBFS_USB__ARB_RW8_RA CYREG_USB_ARB_RW8_RA
#define USBFS_USB__ARB_RW8_RA_MSB CYREG_USB_ARB_RW8_RA_MSB
#define USBFS_USB__ARB_RW8_WA CYREG_USB_ARB_RW8_WA
#define USBFS_USB__ARB_RW8_WA_MSB CYREG_USB_ARB_RW8_WA_MSB
#define USBFS_USB__BUF_SIZE CYREG_USB_BUF_SIZE
#define USBFS_USB__BUS_RST_CNT CYREG_USB_BUS_RST_CNT
#define USBFS_USB__CR0 CYREG_USB_CR0
#define USBFS_USB__CR1 CYREG_USB_CR1
#define USBFS_USB__CWA CYREG_USB_CWA
#define USBFS_USB__CWA_MSB CYREG_USB_CWA_MSB
#define USBFS_USB__DMA_THRES CYREG_USB_DMA_THRES
#define USBFS_USB__DMA_THRES_MSB CYREG_USB_DMA_THRES_MSB
#define USBFS_USB__DYN_RECONFIG CYREG_USB_DYN_RECONFIG
#define USBFS_USB__EP0_CNT CYREG_USB_EP0_CNT
#define USBFS_USB__EP0_CR CYREG_USB_EP0_CR
#define USBFS_USB__EP0_DR0 CYREG_USB_EP0_DR0
#define USBFS_USB__EP0_DR1 CYREG_USB_EP0_DR1
#define USBFS_USB__EP0_DR2 CYREG_USB_EP0_DR2
#define USBFS_USB__EP0_DR3 CYREG_USB_EP0_DR3
#define USBFS_USB__EP0_DR4 CYREG_USB_EP0_DR4
#define USBFS_USB__EP0_DR5 CYREG_USB_EP0_DR5
#define USBFS_USB__EP0_DR6 CYREG_USB_EP0_DR6
#define USBFS_USB__EP0_DR7 CYREG_USB_EP0_DR7
#define USBFS_USB__EP_ACTIVE CYREG_USB_EP_ACTIVE
#define USBFS_USB__EP_TYPE CYREG_USB_EP_TYPE
#define USBFS_USB__MEM_DATA CYREG_USB_MEM_DATA_MBASE
#define USBFS_USB__PM_ACT_CFG CYREG_PM_ACT_CFG5
#define USBFS_USB__PM_ACT_MSK 0x01u
#define USBFS_USB__PM_STBY_CFG CYREG_PM_STBY_CFG5
#define USBFS_USB__PM_STBY_MSK 0x01u
#define USBFS_USB__SIE_EP1_CNT0 CYREG_USB_SIE_EP1_CNT0
#define USBFS_USB__SIE_EP1_CNT1 CYREG_USB_SIE_EP1_CNT1
#define USBFS_USB__SIE_EP1_CR0 CYREG_USB_SIE_EP1_CR0
#define USBFS_USB__SIE_EP2_CNT0 CYREG_USB_SIE_EP2_CNT0
#define USBFS_USB__SIE_EP2_CNT1 CYREG_USB_SIE_EP2_CNT1
#define USBFS_USB__SIE_EP2_CR0 CYREG_USB_SIE_EP2_CR0
#define USBFS_USB__SIE_EP3_CNT0 CYREG_USB_SIE_EP3_CNT0
#define USBFS_USB__SIE_EP3_CNT1 CYREG_USB_SIE_EP3_CNT1
#define USBFS_USB__SIE_EP3_CR0 CYREG_USB_SIE_EP3_CR0
#define USBFS_USB__SIE_EP4_CNT0 CYREG_USB_SIE_EP4_CNT0
#define USBFS_USB__SIE_EP4_CNT1 CYREG_USB_SIE_EP4_CNT1
#define USBFS_USB__SIE_EP4_CR0 CYREG_USB_SIE_EP4_CR0
#define USBFS_USB__SIE_EP5_CNT0 CYREG_USB_SIE_EP5_CNT0
#define USBFS_USB__SIE_EP5_CNT1 CYREG_USB_SIE_EP5_CNT1
#define USBFS_USB__SIE_EP5_CR0 CYREG_USB_SIE_EP5_CR0
#define USBFS_USB__SIE_EP6_CNT0 CYREG_USB_SIE_EP6_CNT0
#define USBFS_USB__SIE_EP6_CNT1 CYREG_USB_SIE_EP6_CNT1
#define USBFS_USB__SIE_EP6_CR0 CYREG_USB_SIE_EP6_CR0
#define USBFS_USB__SIE_EP7_CNT0 CYREG_USB_SIE_EP7_CNT0
#define USBFS_USB__SIE_EP7_CNT1 CYREG_USB_SIE_EP7_CNT1
#define USBFS_USB__SIE_EP7_CR0 CYREG_USB_SIE_EP7_CR0
#define USBFS_USB__SIE_EP8_CNT0 CYREG_USB_SIE_EP8_CNT0
#define USBFS_USB__SIE_EP8_CNT1 CYREG_USB_SIE_EP8_CNT1
#define USBFS_USB__SIE_EP8_CR0 CYREG_USB_SIE_EP8_CR0
#define USBFS_USB__SIE_EP_INT_EN CYREG_USB_SIE_EP_INT_EN
#define USBFS_USB__SIE_EP_INT_SR CYREG_USB_SIE_EP_INT_SR
#define USBFS_USB__SOF0 CYREG_USB_SOF0
#define USBFS_USB__SOF1 CYREG_USB_SOF1
#define USBFS_USB__USBIO_CR0 CYREG_USB_USBIO_CR0
#define USBFS_USB__USBIO_CR1 CYREG_USB_USBIO_CR1
#define USBFS_USB__USB_CLK_EN CYREG_USB_USB_CLK_EN

/* USBFS_Dm */
#define USBFS_Dm__0__MASK 0x80u
#define USBFS_Dm__0__PC CYREG_IO_PC_PRT15_7_6_PC1
#define USBFS_Dm__0__PORT 15u
#define USBFS_Dm__0__SHIFT 7
#define USBFS_Dm__AG CYREG_PRT15_AG
#define USBFS_Dm__AMUX CYREG_PRT15_AMUX
#define USBFS_Dm__BIE CYREG_PRT15_BIE
#define USBFS_Dm__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBFS_Dm__BYP CYREG_PRT15_BYP
#define USBFS_Dm__CTL CYREG_PRT15_CTL
#define USBFS_Dm__DM0 CYREG_PRT15_DM0
#define USBFS_Dm__DM1 CYREG_PRT15_DM1
#define USBFS_Dm__DM2 CYREG_PRT15_DM2
#define USBFS_Dm__DR CYREG_PRT15_DR
#define USBFS_Dm__INP_DIS CYREG_PRT15_INP_DIS
#define USBFS_Dm__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBFS_Dm__LCD_EN CYREG_PRT15_LCD_EN
#define USBFS_Dm__MASK 0x80u
#define USBFS_Dm__PORT 15u
#define USBFS_Dm__PRT CYREG_PRT15_PRT
#define USBFS_Dm__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBFS_Dm__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBFS_Dm__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBFS_Dm__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBFS_Dm__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBFS_Dm__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBFS_Dm__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBFS_Dm__PS CYREG_PRT15_PS
#define USBFS_Dm__SHIFT 7
#define USBFS_Dm__SLW CYREG_PRT15_SLW

/* USBFS_Dp */
#define USBFS_Dp__0__MASK 0x40u
#define USBFS_Dp__0__PC CYREG_IO_PC_PRT15_7_6_PC0
#define USBFS_Dp__0__PORT 15u
#define USBFS_Dp__0__SHIFT 6
#define USBFS_Dp__AG CYREG_PRT15_AG
#define USBFS_Dp__AMUX CYREG_PRT15_AMUX
#define USBFS_Dp__BIE CYREG_PRT15_BIE
#define USBFS_Dp__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBFS_Dp__BYP CYREG_PRT15_BYP
#define USBFS_Dp__CTL CYREG_PRT15_CTL
#define USBFS_Dp__DM0 CYREG_PRT15_DM0
#define USBFS_Dp__DM1 CYREG_PRT15_DM1
#define USBFS_Dp__DM2 CYREG_PRT15_DM2
#define USBFS_Dp__DR CYREG_PRT15_DR
#define USBFS_Dp__INP_DIS CYREG_PRT15_INP_DIS
#define USBFS_Dp__INTSTAT CYREG_PICU15_INTSTAT
#define USBFS_Dp__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBFS_Dp__LCD_EN CYREG_PRT15_LCD_EN
#define USBFS_Dp__MASK 0x40u
#define USBFS_Dp__PORT 15u
#define USBFS_Dp__PRT CYREG_PRT15_PRT
#define USBFS_Dp__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBFS_Dp__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBFS_Dp__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBFS_Dp__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBFS_Dp__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBFS_Dp__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBFS_Dp__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBFS_Dp__PS CYREG_PRT15_PS
#define USBFS_Dp__SHIFT 6
#define USBFS_Dp__SLW CYREG_PRT15_SLW
#define USBFS_Dp__SNAP CYREG_PICU_15_SNAP_15

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_BOOTLOADER_IO_COMP_CUSTOM_IO 0
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PSOC5LP
#define CYDEV_BOOTLOADER_IO_COMP_USBFS 1
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_BOOTLOADER_APPLICATIONS 1u
#define CYDEV_BOOTLOADER_CHECKSUM_BASIC 0
#define CYDEV_BOOTLOADER_CHECKSUM_CRC 1
#define CYDEV_BOOTLOADER_IO_COMP CYDEV_BOOTLOADER_IO_COMP_USBFS
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E109069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 0
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowWithInfo
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_Disable
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_REQXRES 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000000u
#define CYDEV_PROJ_TYPE 1
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USB_CLK_OSC_LOCKING_ENABLED_AT_PWR_UP 
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 2.5
#define CYDEV_VDDA_MV 2500
#define CYDEV_VDDD 2.5
#define CYDEV_VDDD_MV 2500
#define CYDEV_VDDIO0 2.5
#define CYDEV_VDDIO0_MV 2500
#define CYDEV_VDDIO1 2.5
#define CYDEV_VDDIO1_MV 2500
#define CYDEV_VDDIO2 2.5
#define CYDEV_VDDIO2_MV 2500
#define CYDEV_VDDIO3 2.5
#define CYDEV_VDDIO3_MV 2500
#define CYDEV_VIO0 2.5
#define CYDEV_VIO0_MV 2500
#define CYDEV_VIO1 2.5
#define CYDEV_VIO1_MV 2500
#define CYDEV_VIO2 2.5
#define CYDEV_VIO2_MV 2500
#define CYDEV_VIO3 2.5
#define CYDEV_VIO3_MV 2500
#define CyBtldr_Custom_Interface CYDEV_BOOTLOADER_IO_COMP_CUSTOM_IO
#define CyBtldr_USBFS CYDEV_BOOTLOADER_IO_COMP_USBFS
#define CyScBoostClk__CFG0 CYREG_CLKDIST_ACFG0_CFG0
#define CyScBoostClk__CFG1 CYREG_CLKDIST_ACFG0_CFG1
#define CyScBoostClk__CFG2 CYREG_CLKDIST_ACFG0_CFG2
#define CyScBoostClk__CFG2_SRC_SEL_MASK 0x07u
#define CyScBoostClk__CFG3 CYREG_CLKDIST_ACFG0_CFG3
#define CyScBoostClk__CFG3_PHASE_DLY_MASK 0x0Fu
#define CyScBoostClk__INDEX 0x00u
#define CyScBoostClk__PM_ACT_CFG CYREG_PM_ACT_CFG1
#define CyScBoostClk__PM_ACT_MSK 0x01u
#define CyScBoostClk__PM_STBY_CFG CYREG_PM_STBY_CFG1
#define CyScBoostClk__PM_STBY_MSK 0x01u
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 1

#endif /* INCLUDED_CYFITTER_H */