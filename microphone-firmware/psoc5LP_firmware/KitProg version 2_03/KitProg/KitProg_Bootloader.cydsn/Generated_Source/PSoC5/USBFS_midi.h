/*******************************************************************************
* File Name: USBFS_midi.h
* Version 2.51
*
* Description:
*  Header File for the USBFS MIDI module.
*  Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(USBFS_midi_H)
#define USBFS_midi_H

#include "cytypes.h"
#include "USBFS.h"


/***************************************
*    Data Struct Definition
***************************************/

/* The following structure is used to hold status information for
   building and parsing incoming MIDI messages. */
typedef struct _USBFS_MIDI_RX_STATUS
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4];    /* message buffer */
} USBFS_MIDI_RX_STATUS;


/***************************************
*           MIDI Constants.
***************************************/

#define USBFS_ONE_EXT_INTRF              (0x01u)
#define USBFS_TWO_EXT_INTRF              (0x02u)

/* Flag definitions for use with MIDI device inquiry */
#define USBFS_INQ_SYSEX_FLAG             (0x01u)
#define USBFS_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define USBFS_CIN_MASK                   (0x0Fu)
#define USBFS_RESERVED0                  (0x00u)
#define USBFS_RESERVED1                  (0x01u)
#define USBFS_2BYTE_COMMON               (0x02u)
#define USBFS_3BYTE_COMMON               (0x03u)
#define USBFS_SYSEX                      (0x04u)
#define USBFS_1BYTE_COMMON               (0x05u)
#define USBFS_SYSEX_ENDS_WITH1           (0x05u)
#define USBFS_SYSEX_ENDS_WITH2           (0x06u)
#define USBFS_SYSEX_ENDS_WITH3           (0x07u)
#define USBFS_NOTE_OFF                   (0x08u)
#define USBFS_NOTE_ON                    (0x09u)
#define USBFS_POLY_KEY_PRESSURE          (0x0Au)
#define USBFS_CONTROL_CHANGE             (0x0Bu)
#define USBFS_PROGRAM_CHANGE             (0x0Cu)
#define USBFS_CHANNEL_PRESSURE           (0x0Du)
#define USBFS_PITCH_BEND_CHANGE          (0x0Eu)
#define USBFS_SINGLE_BYTE                (0x0Fu)

#define USBFS_CABLE_MASK                 (0xF0u)
#define USBFS_MIDI_CABLE_00              (0x00u)
#define USBFS_MIDI_CABLE_01              (0x10u)

#define USBFS_EVENT_BYTE0                (0x00u)
#define USBFS_EVENT_BYTE1                (0x01u)
#define USBFS_EVENT_BYTE2                (0x02u)
#define USBFS_EVENT_BYTE3                (0x03u)
#define USBFS_EVENT_LENGTH               (0x04u)

#define USBFS_MIDI_STATUS_BYTE_MASK      (0x80u)
#define USBFS_MIDI_STATUS_MASK           (0xF0u)
#define USBFS_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define USBFS_MIDI_NOTE_OFF              (0x80u)
#define USBFS_MIDI_NOTE_ON               (0x90u)
#define USBFS_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define USBFS_MIDI_CONTROL_CHANGE        (0xB0u)
#define USBFS_MIDI_PROGRAM_CHANGE        (0xC0u)
#define USBFS_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define USBFS_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define USBFS_MIDI_SYSEX                 (0xF0u)
#define USBFS_MIDI_EOSEX                 (0xF7u)
#define USBFS_MIDI_QFM                   (0xF1u)
#define USBFS_MIDI_SPP                   (0xF2u)
#define USBFS_MIDI_SONGSEL               (0xF3u)
#define USBFS_MIDI_TUNEREQ               (0xF6u)
#define USBFS_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define USBFS_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define USBFS_MIDI_SYSEX_REALTIME        (0x7Fu)
/* ID of target device */
#define USBFS_MIDI_SYSEX_ID_ALL          (0x7Fu)
/* Sub-ID#1*/
#define USBFS_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define USBFS_MIDI_SYSEX_GEN_MESSAGE     (0x09u)
/* Sub-ID#2*/
#define USBFS_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define USBFS_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define USBFS_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define USBFS_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

#define USBFS_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#define USBFS_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)

#endif /* End USBFS_midi_H */


/* [] END OF FILE */
