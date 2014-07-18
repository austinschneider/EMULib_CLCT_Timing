/****************************************************************
Copyright 1999 I2O Special Interest Group (I2O SIG).  All rights reserved.

TERMS AND CONDITIONS OF USE

This header file, and any modifications of this header file, are provided
contingent upon your agreement and adherence to the here-listed terms and
conditions.  By accepting and/or using this header file, you agree to
abide by these terms and conditions and that these terms and conditions will
be construed and governed in accordance with the laws of the State of
California, without reference to conflict-of-law provisions.  If you do not
agree to these terms and conditions, please delete this file, and any
copies, permanently, without making any use thereof.

THIS HEADER FILE IS PROVIDED FREE OF CHARGE ON AN AS-IS BASIS WITHOUT
WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  I2O SIG DOES NOT WARRANT THAT THIS HEADER FILE WILL MEET THE
USER'S REQUIREMENTS OR THAT ITS OPERATION WILL BE UNINTERRUPTED OR
ERROR-FREE.

I2O SIG DISCLAIMS ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF
ANY PROPRIETARY RIGHTS, RELATING TO THE IMPLEMENTATION OF THE I2O
SPECIFICATIONS.  I2O SIG DOES NOT WARRANT OR REPRESENT THAT SUCH
IMPLEMENTATIONS WILL NOT INFRINGE SUCH RIGHTS.

THE USER OF THIS HEADER FILE SHALL HAVE NO RECOURSE TO I2O SIG FOR ANY
ACTUAL OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT LIMITED TO, LOST DATA
OR LOST PROFITS ARISING OUT OF THE USE OR INABILITY TO USE THIS PROGRAM.

I2O SIG grants the user of this header file a license to copy, distribute,
and modify it, for any purpose, under the following terms.  Any copying,
distribution, or modification of this header file must not delete or alter
the copyright notice of I2O SIG or any of these Terms and Conditions.

Any distribution of this header file must not include a charge for the
header file (unless such charges are strictly for the physical acts of
copying or transferring copies).  However, distribution of a product in
which this header file is embedded may include a charge so long as any
such charge does not include any charge for the header file itself.

Any modification of this header file constitutes a derivative work based
on this header file.  Any distribution of such derivative work: (1) must
include prominent notices that the header file has been changed from the
original, together with the dates of any changes; (2) automatically
includes this same license to the original header file from I2O SIG, without
any restriction thereon from the distributing user; and (3) must include a
grant of license of the modified file under the same terms and conditions as
these Terms and Conditions.

****************************************************************

The I2O SIG Web site can be found at: http://www.i2osig.org

The I2O SIG encourages you to deposit derivative works based on this
header file at the I2O SIG Web site.  Furthermore, to become a Registered
Developer of the I2O SIG, sign up at the Web site or call 415.750.8352
(United States).

****************************************************************/


#if !defined(I2O_HPC_HDR)
#define I2O_HPC_HDR


#include   "i2omsg.h"      /* Include the Base Message file */
#include   "i2outil.h"     /* Include the Utility Message file */


#define I2OHPC_REV 2_0_0   /* I2O HPC header file revision string */

/*****************************************************************************
 *
 *     i2ohpc.h -- I2O Hot Plug Controller Class Header
 *
 *     This file contains information presented in Chapter 6, Section 13 of
 *     the I2O Specification.
 *
 *     Revision History: (Revision History tracks the revision number of the I2O
 *         specification)
 *
 *     2.0  - Initial version.
 *
 *****************************************************************************/

/*
    NOTES:

   Gets, reads, receives, etc. are all even numbered functions.
   Sets, writes, sends, etc. are all odd numbered functions.
   Functions that both send and receive data can be either but an attempt
   is made to use the function number that indicates the greater transfer
   amount.
   Functions that do not send or receive data use odd function numbers.

   Some functions are synonyms like read, receive and send, write.

   All common functions will have a code of less than 0x80.
   Unique functions to a class will start at 0x80.
   Executive Functions start at 0xA0.

   Utility Message function codes range from 0 - 0x1f
   Base Message function codes range from 0x20 - 0xfe
   Private Message function code is 0xff.
*/

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

/* HPC Class specific functions */

#define    I2O_HPC_SLOT_POWER_ON                       0x90
#define    I2O_HPC_SLOT_POWER_OFF                      0x91
#define    I2O_HPC_ATTN_INDICATE                       0x92

/* HPC Generic Defines */
#define    I2O_HPC_MAX_SLOT_DESC                       64

/****************************************************************************/

/* HPC Parameter Groups */

/****************************************************************************/

/* HPC Configuration and Operating Structures and Defines */

/* HPC Groups */
#define    I2O_HPC_CONTROLLER_INFO_GROUP_NO            0x0000
#define    I2O_HPC_SLOT_INFO                           0x0001

/* - 0000h - HPC Controller Information Parameter Group */
/* Bus Type */
#define     I2O_HPC_BUS_TYPE_PCI                       0x04

typedef struct _I2O_HPC_CONTROLLER_INFO_SCALAR {
    U8          BusType;
} I2O_HPC_CONTROLLER_INFO_SCALAR, *PI2O_HPC_CONTROLLER_INFO_SCALAR;


/* - 0001h - PCI Slot Info Parameter Group */
typedef struct _I2O_HPC_SLOT_INFO_TABLE {
    U32         SlotID;
    U8          SlotDescription[I2O_HPC_MAX_SLOT_DESC];
    U8          SlotState;
    U8          AttnIndicator;
    U8          AdapterCardPwrReq;
    U8          AdapterCardFreqCap;
    U8          SlotFreq;
    U8          SlotInterlockStatus;
    U8          Reserved[2];
} I2O_HPC_SLOT_INFO_TABLE, *PI2O_HPC_SLOT_INFO_TABLE;


/* Slot States */
#define    I2O_HPC_SLOT_STATE_OFF                      0x00
#define    I2O_HPC_SLOT_STATE_ON                       0x01


/* Attention Indicator */
#define    I2O_HPC_ATTN_INDICATOR_NORMAL               0x00
#define    I2O_HPC_ATTN_INDICATOR_ATTENTION            0x01


/* Adapter Card Power Requirements */
#define    I2O_HPC_ADAPTER_CARD_PWR_REQ_NOT_PRESENT    0x00
#define    I2O_HPC_ADAPTER_CARD_PWR_REQ_LOW            0x01
#define    I2O_HPC_ADAPTER_CARD_PWR_REQ_MEDIUM         0x02
#define    I2O_HPC_ADAPTER_CARD_PWR_REQ_HIGH           0x03


/* Adatper Card Frequency Capabilies */
#define    I2O_HPC_ADAPTER_CARD_FREQ_CAP_UNKNOWN       0x00
#define    I2O_HPC_ADAPTER_CARD_FREQ_CAP_33MHZ         0x01
#define    I2O_HPC_ADAPTER_CARD_FREQ_CAP_66MHZ         0x02
#define    I2O_HPC_ADAPTER_CARD_FREQ_CAP_PCIX          0x03

/* Slot Frequencies */
#define    I2O_HPC_SLOT_FREQ_UNKNOWN                   0x00
#define    I2O_HPC_SLOT_FREQ_33MHZ                     0x01
#define    I2O_HPC_SLOT_FREQ_66MHZ                     0x02
#define    I2O_HPC_SLOT_FREQ_PCIX_MODE                 0x03

/* Slot Interlock Status (optional) */
#define    I2O_HPC_ADAPTER_INTERLOCK_STS_OPEN          0x00
#define    I2O_HPC_ADAPTER_INTERLOCK_STS_CLOSED        0x01


/****************************************************************************/


/* Event Masks */
#define    I2O_HPC_EVENT_CARD_PRESENCE_CHANGE          0x01
#define    I2O_HPC_EVENT_POWER_FAIL                    0x02
#define    I2O_HPC_EVENT_PUSH_BUTTON_REQUEST           0x04
#define    I2O_HPC_EVENT_INTERLOCK_CHANGE              0x08

/****************************************************************************/


/* DetailedStatusCode defines */
#define    I2O_HPC_DSC_SUCCESS                         0x00
#define    I2O_HPC_DSC_POWER_FAIL                      0x01
#define    I2O_HPC_DSC_WRONG_FREQ                      0x02
#define    I2O_HPC_DSC_INSUFFICIENT_PWR                0x03
#define    I2O_HPC_DSC_GENERAL_FAILURE                 0x04

/****************************************************************************/


/* I2O Hot Plug Controller Class Specific Message Definitions */
/****************************************************************************/


/* I2O HPC Class Reply Message Frame */
typedef struct _I2O_HPC_REPLY_MESSAGE_FRAME {
    I2O_SINGLE_REPLY_MESSAGE_FRAME StdReplyFrame;
} I2O_HPC_REPLY_MESSAGE_FRAME, *PI2O_HPC_REPLY_MESSAGE_FRAME;

/****************************************************************************/


/* I2O HPC Slot Power On Message Frame */
typedef struct _I2O_HPC_SLOT_POWER_ON_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U32                         SlotId;
} I2O_HPC_SLOT_POWER_ON_MESSAGE, *PI2O_HPC_SLOT_POWER_ON_MESSAGE;

/****************************************************************************/


/* I2O HPC Slot Power Off Message Frame */
typedef struct _I2O_HPC_SLOT_POWER_OFF_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U32                         SlotId;
} I2O_HPC_SLOT_POWER_OFF_MESSAGE, *PI2O_HPC_SLOT_POWER_OFF_MESSAGE;

/****************************************************************************/


/* I2O HPC Slot Attention Indicate Message Frame */
typedef struct _I2O_HPC_SLOT_ATTN_INDICATE_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U32                         SlotId;
   U32                         AttnIndication;
} I2O_HPC_SLOT_ATTN_INDICATE_MESSAGE, *PI2O_HPC_SLOT_ATTN_INDICATE_MESSAGE;

/****************************************************************************/

PRAGMA_PACK_POP
PRAGMA_ALIGN_POP

#endif     /* I2O_HPC_HDR */  
