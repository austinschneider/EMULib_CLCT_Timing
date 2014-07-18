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

/*********************************************************************
 * I2OMsg.h -- I2O Message definition file
 *
 * This file contains information presented in Chapter 3, 4 and 6 of
 * the I2O(tm) Specification and most of the I2O Global defines and
 * Typedefs.
 **********************************************************************/

#if !defined(I2O_MESSAGE_HDR)
#define I2O_MESSAGE_HDR

#define I2OMSG_REV 2_0_0  /* I2OMsg header file revision string */

/*

   NOTES:

   Gets, reads, receives, etc. are all even numbered functions.
   Sets, writes, sends, etc. are all odd numbered functions.
   Functions that both send and receive data can be either but an attempt is 
   made to use the function number that indicates the greater transfer amount.
   Functions that do not send or receive data use odd function numbers.

   Some functions are synonyms like read, receive and send, write.

   All common functions will have a code of less than 0x80.
   Unique functions to a class will start at 0x80.
   Executive Functions start at 0xA0.

   Utility Message function codes range from 0 - 0x1f
   Base Message function codes range from 0x20 - 0xfe
   Private Message function code is 0xff.
*/



#include "i2otypes.h"
#include "i2osgl.h"

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

/* Set to 1 for 64 bit Context Fields */
#define     I2O_64BIT_CONTEXT          1

/****************************************************************************/

/* Common functions accross all classes. */

#define    I2O_PRIVATE_MESSAGE                         0xFF

/****************************************************************************/

/* Spec version numbers */

#define    I2O_SPEC_VERSION_10                         0x00
#define    I2O_SPEC_VERSION_15                         0x01
#define    I2O_SPEC_VERSION_20                         0x02

/* ClassID version field */

#define    I2O_CLASS_VERSION_10                        I2O_SPEC_VERSION_10
#define    I2O_CLASS_VERSION_15                        I2O_SPEC_VERSION_15
#define    I2O_CLASS_VERSION_20                        I2O_SPEC_VERSION_20

/* Class Code Assignments */

/*    Class Code Names:  Table 6-1 Class Code Assignments. */
#define    I2O_CLASS_EXECUTIVE                         0x000
#define    I2O_CLASS_DDM                               0x001
#define    I2O_CLASS_RANDOM_BLOCK_STORAGE              0x010
#define    I2O_CLASS_SEQUENTIAL_STORAGE                0x011
#define    I2O_CLASS_LAN                               0x020
#define    I2O_CLASS_WAN                               0x030
#define    I2O_CLASS_FIBRE_CHANNEL_PORT                0x040
#define    I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL          0x041
#define    I2O_CLASS_SCSI_PERIPHERAL                   0x051
#define    I2O_CLASS_ATE_PORT                          0x060
#define    I2O_CLASS_ATE_PERIPHERAL                    0x061
#define    I2O_CLASS_FLOPPY_CONTROLLER                 0x070
#define    I2O_CLASS_FLOPPY_DEVICE                     0x071
#define    I2O_CLASS_BUS_ADAPTER_PORT                  0x080
#define    I2O_CLASS_PEER_TRANSPORT_AGENT              0x090
#define    I2O_CLASS_PEER_TRANSPORT                    0x091
/* Class Codes 0x090 - 0x09f are reserved for Peer-to-Peer classes */
#define    I2O_CLASS_REMOTE_UNIT_MANAGEMENT            0x0a0
#define    I2O_CLASS_REMOTE_TRANSPORT                  0x0a1
#define    I2O_CLASS_HOT_PLUG_CONTROLLER               0x0b0

#define    I2O_CLASS_MATCH_ANYCLASS                    0xffffffff
#define    I2O_CLASS_MATCH_ANYVENDOR                   0xffff
#define    I2O_CLASS_MATCH_ANYVERSION                  0xf
#define    I2O_CLASS_MATCH_ANYCLASSCODE                0xfff

#define    I2O_SUBCLASS_i960                           0x001


/*  The following are obsolete in Version 2.0 - use I2O_DDM_TYPE_
 *  definitions in i2oddm.h
 */

#define    I2O_SUBCLASS_HDM                            0x020
#define    I2O_SUBCLASS_ISM                            0x021


/****************************************************************************/
/* Message Frame defines and structures  */

/*   Defines for the Version_Offset field. */

#define    I2O_MESSAGE_HEADER_VERSION_10               0x00
#define    I2O_MESSAGE_HEADER_VERSION_15               0x01

#define    I2O_VERSION_OFFSET_NUMBER_MASK              0x07
#define    I2O_VERSION_OFFSET_SGL_TRL_OFFSET_MASK      0xF0

/*   Defines for the Message Flags Field. */
/*   Please Note that the FAIL bit is only set in the Transport Fail Message. */
#define    I2O_MESSAGE_FLAGS_STATIC                    0x01
#define    I2O_MESSAGE_FLAGS_64BIT_CONTEXT             0x02
#define    I2O_MESSAGE_FLAGS_MULTIPLE                  0x10
#define    I2O_MESSAGE_FLAGS_FAIL                      0x20
#define    I2O_MESSAGE_FLAGS_LAST                      0x40
#define    I2O_MESSAGE_FLAGS_REPLY                     0x80

/* DAQ extension
*/
#define    I2O_MESSAGE_FLAGS_SEGMENT                   0x04


/* Defines for Request Status Codes:  Table 3-1 Reply Status Codes.  */

#define    I2O_REPLY_STATUS_SUCCESS                    0x00
#define    I2O_REPLY_STATUS_ABORT_DIRTY                0x01
#define    I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER     0x02
#define    I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER     0x03
#define    I2O_REPLY_STATUS_ERROR_DIRTY                0x04
#define    I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER     0x05
#define    I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER     0x06
#define    I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY        0x08
#define    I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER   0x09
#define    I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER   0x0A
#define    I2O_REPLY_STATUS_TRANSACTION_ERROR          0x0B
#define    I2O_REPLY_STATUS_PROGRESS_REPORT            0x80

/* DetailedStatusCode defines for ALL messages: Table 3-2 Detailed Status Codes.  */

#define    I2O_DETAIL_STATUS_SUCCESS                        0x0000
#define    I2O_DETAIL_STATUS_BAD_KEY                        0x0002
#define    I2O_DETAIL_STATUS_TCL_ERROR                      0x0003
#define    I2O_DETAIL_STATUS_REPLY_BUFFER_FULL              0x0004
#define    I2O_DETAIL_STATUS_NO_SUCH_PAGE                   0x0005
#define    I2O_DETAIL_STATUS_INSUFFICIENT_RESOURCE_SOFT     0x0006
#define    I2O_DETAIL_STATUS_INSUFFICIENT_RESOURCE_HARD     0x0007
#define    I2O_DETAIL_STATUS_CHAIN_BUFFER_TOO_LARGE         0x0009
#define    I2O_DETAIL_STATUS_UNSUPPORTED_FUNCTION           0x000A
#define    I2O_DETAIL_STATUS_DEVICE_LOCKED                  0x000B
#define    I2O_DETAIL_STATUS_DEVICE_RESET                   0x000C
#define    I2O_DETAIL_STATUS_INAPPROPRIATE_FUNCTION         0x000D
#define    I2O_DETAIL_STATUS_INVALID_INITIATOR_ADDRESS      0x000E
#define    I2O_DETAIL_STATUS_INVALID_MESSAGE_FLAGS          0x000F
#define    I2O_DETAIL_STATUS_INVALID_OFFSET                 0x0010
#define    I2O_DETAIL_STATUS_INVALID_PARAMETER              0x0011
#define    I2O_DETAIL_STATUS_INVALID_REQUEST                0x0012
#define    I2O_DETAIL_STATUS_INVALID_TARGET_ADDRESS         0x0013
#define    I2O_DETAIL_STATUS_MESSAGE_TOO_LARGE              0x0014
#define    I2O_DETAIL_STATUS_MESSAGE_TOO_SMALL              0x0015
#define    I2O_DETAIL_STATUS_MISSING_PARAMETER              0x0016
#define    I2O_DETAIL_STATUS_TIMEOUT                        0x0017
#define    I2O_DETAIL_STATUS_UNKNOWN_ERROR                  0x0018
#define    I2O_DETAIL_STATUS_UNKNOWN_FUNCTION               0x0019
#define    I2O_DETAIL_STATUS_UNSUPPORTED_VERSION            0x001A
#define    I2O_DETAIL_STATUS_DEVICE_BUSY                    0x001B
#define    I2O_DETAIL_STATUS_DEVICE_NOT_AVAILABLE           0x001C
#define    I2O_DETAIL_STATUS_CRITICAL_DEVICE                0x001D
#define    I2O_DETAIL_STATUS_EVENT_ACK_PENDING              0x001E
#define    I2O_DETAIL_STATUS_PERMANENT_STORE_ERROR          0x001F

/* Common I2O Field sizes  */

#define    I2O_TID_SZ                                  12
#define    I2O_FUNCTION_SZ                             8
#define    I2O_UNIT_ID_SZ                              16
#define    I2O_SEGMENT_NUMBER_SZ                       12

#define    I2O_IOP_ID_SZ                               12
#define    I2O_GROUP_ID_SZ                             16
#define    I2O_IOP_STATE_SZ                            8
#define    I2O_MESSENGER_TYPE_SZ                       8

#define    I2O_CLASS_ID_SZ                             12
#define    I2O_CLASS_ORGANIZATION_ID_SZ                16

#define    I2O_4BIT_VERSION_SZ                         4
#define    I2O_8BIT_FLAGS_SZ                           8
#define    I2O_COMMON_LENGTH_FIELD_SZ                  16

#define    I2O_DEVID_DESCRIPTION_SZ                    16
#define    I2O_DEVID_VENDOR_INFO_SZ                    16
#define    I2O_DEVID_PRODUCT_INFO_SZ                   16
#define    I2O_DEVID_REV_LEVEL_SZ                      8
#define    I2O_MODULE_NAME_SZ                          24

#define    I2O_BIOS_INFO_SZ                            8

#define    I2O_RESERVED_4BITS                          4
#define    I2O_RESERVED_8BITS                          8
#define    I2O_RESERVED_12BITS                         12
#define    I2O_RESERVED_16BITS                         16
#define    I2O_RESERVED_20BITS                         20
#define    I2O_RESERVED_24BITS                         24
#define    I2O_RESERVED_28BITS                         28


typedef    U32        I2O_PARAMETER_TID;

#if I2O_64BIT_CONTEXT
typedef    U64        I2O_INITIATOR_CONTEXT;
typedef    U64        I2O_TRANSACTION_CONTEXT;
#else
typedef    U32        I2O_INITIATOR_CONTEXT;
typedef    U32        I2O_TRANSACTION_CONTEXT;
#endif

/*  Serial Number format defines */

#define    I2O_SERIAL_FORMAT_UNKNOWN                   0
#define    I2O_SERIAL_FORMAT_BINARY                    1
#define    I2O_SERIAL_FORMAT_ASCII                     2
#define    I2O_SERIAL_FORMAT_UNICODE                   3
#define    I2O_SERIAL_FORMAT_LAN_MAC                   4
#define    I2O_SERIAL_FORMAT_WAN                       5
#define    I2O_SERIAL_FORMAT_LAN_64_MAC                6
#define    I2O_SERIAL_FORMAT_I2O_DDM                   7
#define    I2O_SERIAL_FORMAT_IEEE_64                   8
#define    I2O_SERIAL_FORMAT_IEEE_128                  9
#define    I2O_SERIAL_FORMAT_UNKNOWN_FORMAT         0xff


/* Special TID Assignments */

#define    I2O_IOP_TID                                 0
#define    I2O_HOST_TID                                1
#define    I2O_RTA_TID                                 2


/****************************************************************************/

/* I2O Message Frame common for all messages  */

typedef struct _I2O_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   U8                          VersionOffset;
   U8                          MsgFlags;
   U16                         MessageSize;
   BF                          TargetAddress:I2O_TID_SZ;
   BF                          InitiatorAddress:I2O_TID_SZ;
   BF                          Function:I2O_FUNCTION_SZ;
   I2O_INITIATOR_CONTEXT       InitiatorContext;
#elif defined(BIG_ENDIAN__)
   U16                         MessageSize;
   U8                          MsgFlags;
   U8                          VersionOffset;
   BF                          Function:I2O_FUNCTION_SZ;
   BF                          InitiatorAddress:I2O_TID_SZ;
   BF                          TargetAddress:I2O_TID_SZ;
   I2O_INITIATOR_CONTEXT       InitiatorContext;
#endif
} I2O_MESSAGE_FRAME, *PI2O_MESSAGE_FRAME;


/****************************************************************************/

/* Transaction Reply Lists (TRL) Control Word structure */

#define    I2O_TRL_FLAGS_SINGLE_FIXED_LENGTH           0x00
#define    I2O_TRL_FLAGS_SINGLE_VARIABLE_LENGTH        0x40
#define    I2O_TRL_FLAGS_MULTIPLE_FIXED_LENGTH         0x80

typedef struct _I2O_TRL_CONTROL_WORD {
#if defined(LITTLE_ENDIAN__)
   U8                          TrlCount;
   U8                          TrlElementSize;
   U8                          reserved;
   U8                          TrlFlags;
  #if I2O_64BIT_CONTEXT
   U32                         Padding;           /* Padding for 64 bit */
  #endif
#elif defined(BIG_ENDIAN__)
   U8                          TrlFlags;
   U8                          reserved;
   U8                          TrlElementSize;
   U8                          TrlCount;
  #if I2O_64BIT_CONTEXT
   U32                         Padding;           /* Padding for 64 bit */
  #endif
#endif
} I2O_TRL_CONTROL_WORD, *PI2O_TRL_CONTROL_WORD;

/****************************************************************************/

/* I2O Successful Single Transaction Reply Message Frame structure. */

typedef struct _I2O_SINGLE_REPLY_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         DetailedStatusCode;
   U8                          reserved;
   U8                          ReqStatus;
/*                             ReplyPayload        */
#elif defined(BIG_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U8                          ReqStatus;
   U8                          reserved;
   U16                         DetailedStatusCode;
/*                             ReplyPayload        */
#endif
} I2O_SINGLE_REPLY_MESSAGE_FRAME, *PI2O_SINGLE_REPLY_MESSAGE_FRAME;


/****************************************************************************/

/* I2O Successful Multiple Transaction Reply Message Frame structure. */

typedef struct _I2O_MULTIPLE_REPLY_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRL_CONTROL_WORD        TrlControlWord;
   U16                         DetailedStatusCode;
   U8                          reserved;
   U8                          ReqStatus;
/*                             TransactionDetails[]        */
#elif defined(BIG_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRL_CONTROL_WORD        TrlControlWord;
   U8                          ReqStatus;
   U8                          reserved;
   U16                         DetailedStatusCode;
/*                             TransactionDetails[]        */
#endif
} I2O_MULTIPLE_REPLY_MESSAGE_FRAME, *PI2O_MULTIPLE_REPLY_MESSAGE_FRAME;


/****************************************************************************/

/* I2O Private Message Frame structure. */

typedef struct _I2O_PRIVATE_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         XFunctionCode;
   U16                         OrganizationID;
   U32                         Padding;           /* Padding for 64 bit */
/*                             PrivatePayload[]        */
#elif defined(BIG_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         OrganizationID;
   U16                         XFunctionCode;
   U32                         Padding;           /* Padding for 64 bit */
/*                             PrivatePayload[]        */
#endif
} I2O_PRIVATE_MESSAGE_FRAME, *PI2O_PRIVATE_MESSAGE_FRAME;


/****************************************************************************/

/* Message Failure Severity Codes */

#define    I2O_SEVERITY_FORMAT_ERROR                   0x1
#define    I2O_SEVERITY_PATH_ERROR                     0x2
#define    I2O_SEVERITY_PATH_STATE                     0x4
#define    I2O_SEVERITY_CONGESTION                     0x8

/* Transport Failure Codes: Table 3-3 Mesasge Failure Codes */

#define    I2O_FAILURE_CODE_TRANSPORT_SERVICE_SUSPENDED    0x81
#define    I2O_FAILURE_CODE_TRANSPORT_SERVICE_TERMINATED   0x82
#define    I2O_FAILURE_CODE_TRANSPORT_CONGESTION           0x83
#define    I2O_FAILURE_CODE_TRANSPORT_FAIL                 0x84
#define    I2O_FAILURE_CODE_TRANSPORT_STATE_ERROR          0x85
#define    I2O_FAILURE_CODE_TRANSPORT_TIME_OUT             0x86
#define    I2O_FAILURE_CODE_TRANSPORT_ROUTING_FAILURE      0x87
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_VERSION      0x88
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_OFFSET       0x89
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_MSG_FLAGS    0x8A
#define    I2O_FAILURE_CODE_TRANSPORT_FRAME_TOO_SMALL      0x8B
#define    I2O_FAILURE_CODE_TRANSPORT_FRAME_TOO_LARGE      0x8C
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_TARGET_ID    0x8D
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_INITIATOR_ID 0x8E
#define    I2O_FAILURE_CODE_TRANSPORT_INVALID_INITIATOR_CONTEXT    0x8F
#define    I2O_FAILURE_CODE_TRANSPORT_UNKNOWN_FAILURE      0xFF

/* IOP_ID and Severity sizes */

#define    I2O_FAILCODE_SEVERITY_SZ                        8
#define    I2O_FAILCODE_CODE_SZ                            8

/* I2O Transport Message Reply for Message Failure. */

typedef struct _I2O_FAILURE_REPLY_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U8                          LowestVersion;
   U8                          HighestVersion;
   BF                          Severity:I2O_FAILCODE_SEVERITY_SZ;
   BF                          FailureCode:I2O_FAILCODE_CODE_SZ;
   BF                          FailingIOP_ID:I2O_IOP_ID_SZ;
   BF                          reserved:I2O_RESERVED_4BITS;
   BF                          FailingHostUnitID:I2O_UNIT_ID_SZ;
   U32                         AgeLimit;
   U128                        PreservedMFA;
#elif defined(BIG_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   BF                          FailureCode:I2O_FAILCODE_CODE_SZ;
   BF                          Severity:I2O_FAILCODE_SEVERITY_SZ;
   U8                          HighestVersion;
   U8                          LowestVersion;
   BF                          FailingHostUnitID:I2O_UNIT_ID_SZ;
   BF                          reserved:I2O_RESERVED_4BITS;
   BF                          FailingIOP_ID:I2O_IOP_ID_SZ;
   U32                         AgeLimit;
   U128                        PreservedMFA;
#endif   
} I2O_FAILURE_REPLY_MESSAGE_FRAME, *PI2O_FAILURE_REPLY_MESSAGE_FRAME;

/* I2O Transport Message Reply for Transaction Error. */

typedef struct _I2O_TRANSACTION_ERROR_REPLY_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         DetailedStatusCode;
   U8                          reserved;
   U8                          ReqStatus;   /* Should always be Transaction Error */
   U32                         ErrorOffset;
   U8                          BitOffset;
   U8                          reserved1;
   U16                         reserved2;
#elif defined(BIG_ENDIAN__)
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U8                          ReqStatus;   /* Should always be Transaction Error */
   U8                          reserved;
   U16                         DetailedStatusCode;
   U32                         ErrorOffset;
   U16                         reserved2;
   U8                          reserved1;
   U8                          BitOffset;
#endif
} I2O_TRANSACTION_ERROR_REPLY_MESSAGE_FRAME, *PI2O_TRANSACTION_ERROR_REPLY_MESSAGE_FRAME;

/****************************************************************************/

/*  Misc. commonly used structures */

/* Class ID Block */

typedef struct _I2O_CLASS_ID {
 #if defined(LITTLE_ENDIAN__)
   BF                          Class:I2O_CLASS_ID_SZ;
   BF                          Version:I2O_4BIT_VERSION_SZ;
   BF                          OrganizationID:I2O_CLASS_ORGANIZATION_ID_SZ;
#elif defined(BIG_ENDIAN__)
   BF                          OrganizationID:I2O_CLASS_ORGANIZATION_ID_SZ;
   BF                          Version:I2O_4BIT_VERSION_SZ;
   BF                          Class:I2O_CLASS_ID_SZ;
#endif
} I2O_CLASS_ID, *PI2O_CLASS_ID;


#define    I2O_MAX_SERIAL_NUMBER_SZ                    256

typedef struct _I2O_SERIAL_INFO {
#if defined(LITTLE_ENDIAN__)
   U8                          SerialNumberLength;
   U8                          SerialNumberFormat;
   U8                          SerialNumber[I2O_MAX_SERIAL_NUMBER_SZ];
#elif defined(BIG_ENDIAN__)
   U8                          SerialNumber[2];
   U8                          SerialNumberFormat;
   U8                          SerialNumberLength;
 #if (I2O_MAX_SERIAL_NUMBER_SZ > 2)
   U8                          SerialNumberRemaining[I2O_MAX_SERIAL_NUMBER_SZ - 2];
 #endif
#endif
} I2O_SERIAL_INFO, *PI2O_SERIAL_INFO;


/****************************************************************************/
/* Hardware Resource Table (HRT) and Logical Configuration Table (LCT) */
/****************************************************************************/

/* Bus Type Code defines */

#define    I2O_LOCAL_BUS                               0
#define    I2O_ISA_BUS                                 1
#define    I2O_EISA_BUS                                2
#define    I2O_MCA_BUS                                 3
#define    I2O_PCI_BUS                                 4
#define    I2O_PCMCIA_BUS                              5
#define    I2O_NUBUS_BUS                               6
#define    I2O_CARDBUS_BUS                             7
#define    I2O_OTHER_BUS                               0x80

#define    I2O_HRT_STATE_SZ                            4
#define    I2O_HRT_BUS_NUMBER_SZ                       8
#define    I2O_HRT_BUS_TYPE_SZ                         8

/* Bus Structures */

/* PCI Bus */
typedef struct _I2O_PCI_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U8                          PciFunctionNumber;
   U8                          PciDeviceNumber;
   U8                          PciBusNumber;
   U8                          reserved;
   U16                         PciVendorID;
   U16                         PciDeviceID;
#elif defined(BIG_ENDIAN__)
   U8                          reserved;
   U8                          PciBusNumber;
   U8                          PciDeviceNumber;
   U8                          PciFunctionNumber;
   U16                         PciDeviceID;
   U16                         PciVendorID;
#endif
} I2O_PCI_BUS_INFO, *PI2O_PCI_BUS_INFO;

/* Local Bus */
typedef struct _I2O_LOCAL_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U16                         LbBaseIOPort;
   U16                         reserved;
   U32                         LbBaseMemoryAddress;
#elif defined(BIG_ENDIAN__)
   U16                         reserved;
   U16                         LbBaseIOPort;
   U32                         LbBaseMemoryAddress;
#endif
} I2O_LOCAL_BUS_INFO, *PI2O_LOCAL_BUS_INFO;

/* ISA Bus */
typedef struct _I2O_ISA_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U16                         IsaBaseIOPort;
   U8                          CSN;
   U8                          reserved;
   U32                         IsaBaseMemoryAddress;
#elif defined(BIG_ENDIAN__)
   U8                          reserved;
   U8                          CSN;
   U16                         IsaBaseIOPort;
   U32                         IsaBaseMemoryAddress;
#endif
} I2O_ISA_BUS_INFO, *PI2O_ISA_BUS_INFO;

/* EISA Bus */
typedef struct _I2O_EISA_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U16                         EisaBaseIOPort;
   U8                          reserved;
   U8                          EisaSlotNumber;
   U32                         EisaBaseMemoryAddress;
#elif defined(BIG_ENDIAN__)
   U8                          EisaSlotNumber;
   U8                          reserved;
   U16                         EisaBaseIOPort;
   U32                         EisaBaseMemoryAddress;
#endif
} I2O_EISA_BUS_INFO, *PI2O_EISA_BUS_INFO;

/* MCA Bus */
typedef struct _I2O_MCA_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U16                         McaBaseIOPort;
   U8                          reserved;
   U8                          McaSlotNumber;
   U32                         McaBaseMemoryAddress;
#elif defined(BIG_ENDIAN__)
   U8                          McaSlotNumber;
   U8                          reserved;
   U16                         McaBaseIOPort;
   U32                         McaBaseMemoryAddress;
#endif
} I2O_MCA_BUS_INFO, *PI2O_MCA_BUS_INFO;

/* Other Bus */
typedef struct _I2O_OTHER_BUS_INFO {
#if defined(LITTLE_ENDIAN__)
   U16                         BaseIOPort;
   U16                         reserved;
   U32                         BaseMemoryAddress;
#elif defined(BIG_ENDIAN__)
   U16                         reserved;
   U16                         BaseIOPort;
   U32                         BaseMemoryAddress;
#endif
} I2O_OTHER_BUS_INFO, *PI2O_OTHER_BUS_INFO;


/* HRT Entry Block */

typedef struct _I2O_HRT_ENTRY {
#if defined(LITTLE_ENDIAN__)
   U32                         AdapterID;
   BF                          ControllingTID:I2O_TID_SZ;
   BF                          AdapterState:I2O_HRT_STATE_SZ;
   BF                          BusNumber:I2O_HRT_BUS_NUMBER_SZ;
   BF                          BusType:I2O_HRT_BUS_TYPE_SZ;
   union {
       /* PCI Bus */
       I2O_PCI_BUS_INFO        PCIBus;

       /* Local Bus */
       I2O_LOCAL_BUS_INFO      LocalBus;

       /* ISA Bus */
       I2O_ISA_BUS_INFO        ISABus;

       /* EISA Bus */
       I2O_EISA_BUS_INFO       EISABus;

       /* MCA Bus */
       I2O_MCA_BUS_INFO        MCABus;

       /* Other. */
       I2O_OTHER_BUS_INFO      OtherBus;
   }uBus;
   BF                          HpcTID:I2O_TID_SZ;
   BF                          Reserved1:4;
   BF                          Reserved2:16;
   U32                         SlotID;
#elif defined(BIG_ENDIAN__)
   U32                         AdapterID;
   BF                          BusType:I2O_HRT_BUS_TYPE_SZ;
   BF                          BusNumber:I2O_HRT_BUS_NUMBER_SZ;
   BF                          AdapterState:I2O_HRT_STATE_SZ;
   BF                          ControllingTID:I2O_TID_SZ;
   union {
       /* PCI Bus */
       I2O_PCI_BUS_INFO        PCIBus;

       /* Local Bus */
       I2O_LOCAL_BUS_INFO      LocalBus;

       /* ISA Bus */
       I2O_ISA_BUS_INFO        ISABus;

       /* EISA Bus */
       I2O_EISA_BUS_INFO       EISABus;

       /* MCA Bus */
       I2O_MCA_BUS_INFO        MCABus;

       /* Other. */
       I2O_OTHER_BUS_INFO      OtherBus;
   }uBus;
   BF                          Reserved2:16;
   BF                          Reserved1:4;
   BF                          HpcTID:I2O_TID_SZ;
   U32                         SlotID;
#endif   
} I2O_HRT_ENTRY, *PI2O_HRT_ENTRY;


/* I2O Hardware Resource Table structure. */

typedef struct _I2O_HRT {
#if defined(LITTLE_ENDIAN__)
   U16                         NumberEntries;
   U8                          EntryLength;
   U8                          HRTVersion;
   U32                         CurrentChangeIndicator;
   I2O_HRT_ENTRY               HRTEntry[1];
#elif defined(BIG_ENDIAN__)
   U8                          HRTVersion;
   U8                          EntryLength;
   U16                         NumberEntries;
   U32                         CurrentChangeIndicator;
   I2O_HRT_ENTRY               HRTEntry[1];
#endif
} I2O_HRT, *PI2O_HRT;


/****************************************************************************/
/* Logical Configuration Table  */
/****************************************************************************/

/* I2O Logical Configuration Table structures. */

#define    I2O_IDENTITY_TAG_SZ                         8

/* I2O Logical Configuration Table Device Flags */

#define    I2O_LCT_DEVICE_FLAGS_CONF_DIALOG_REQUEST             0x01
#define    I2O_LCT_DEVICE_FLAGS_MORE_THAN_1_USER                0x02

#define    I2O_LCT_DEVICE_FLAGS_CONTEXT_SUPPORT_MASK            0x0C
#define    I2O_LCT_DEVICE_FLAGS_32_BIT_CONTEXT_SUPPORT          0x00
#define    I2O_LCT_DEVICE_FLAGS_64_BIT_CONTEXT_SUPPORT          0x04
#define    I2O_LCT_DEVICE_FLAGS_32_OR_64_BIT_CONTEXT_SUPPORT    0x08
#define    I2O_LCT_DEVICE_FLAGS_32_AND_64_BIT_CONTEXT_SUPPORT   0x0C

#define    I2O_LCT_DEVICE_FLAGS_PEER_SERVICE_DISABLED           0x10
#define    I2O_LCT_DEVICE_FLAGS_MANAGEMENT_SERVICE_DISABLED     0x20
#define    I2O_LCT_DEVICE_FLAGS_HOT_PLUG_SUPPORTED              0x40
#define    I2O_LCT_DEVICE_FLAGS_ADDRESSES_ABOVE_32BIT_SUPPORTED 0x80

/* LCT Entry Block */

typedef struct _I2O_LCT_ENTRY {
#if defined(LITTLE_ENDIAN__)
   BF                          TableEntrySize:I2O_COMMON_LENGTH_FIELD_SZ;
   BF                          LocalTID:I2O_TID_SZ;
   BF                          reserved:I2O_4BIT_VERSION_SZ;
   U32                         ChangeIndicator;
   U32                         DeviceFlags;
   I2O_CLASS_ID                ClassID;
   U32                         SubClassInfo;
   BF                          UserTID:I2O_TID_SZ;
   BF                          ParentTID:I2O_TID_SZ;
   BF                          BiosInfo:I2O_BIOS_INFO_SZ;
   U8                          IdentityTag[I2O_IDENTITY_TAG_SZ];
   U32                         EventCapabilities;
#elif defined(BIG_ENDIAN__)
   BF                          reserved:I2O_4BIT_VERSION_SZ;
   BF                          LocalTID:I2O_TID_SZ;
   BF                          TableEntrySize:I2O_COMMON_LENGTH_FIELD_SZ;
   U32                         ChangeIndicator;
   U32                         DeviceFlags;
   I2O_CLASS_ID                ClassID;
   U32                         SubClassInfo;
   BF                          BiosInfo:I2O_BIOS_INFO_SZ;
   BF                          ParentTID:I2O_TID_SZ;
   BF                          UserTID:I2O_TID_SZ;
   U8                          IdentityTag[I2O_IDENTITY_TAG_SZ];
   U32                         EventCapabilities;
#endif
} I2O_LCT_ENTRY, *PI2O_LCT_ENTRY;


/* I2O Logical Configuration Table structure. */

typedef struct _I2O_LCT {
#if defined(LITTLE_ENDIAN__)
   BF                          TableSize:I2O_COMMON_LENGTH_FIELD_SZ;
   BF                          BootDeviceTID:I2O_TID_SZ;
   BF                          LctVer:I2O_4BIT_VERSION_SZ;
   U32                         IopFlags;
   U32                         CurrentChangeIndicator;
   I2O_LCT_ENTRY               LCTEntry[1];
#elif defined(BIG_ENDIAN__)
   BF                          LctVer:I2O_4BIT_VERSION_SZ;
   BF                          BootDeviceTID:I2O_TID_SZ;
   BF                          TableSize:I2O_COMMON_LENGTH_FIELD_SZ;
   U32                         IopFlags;
   U32                         CurrentChangeIndicator;
   I2O_LCT_ENTRY               LCTEntry[1];
#endif
} I2O_LCT, *PI2O_LCT;

/****************************************************************************/
/*  Basic Parameter Group Access */
/****************************************************************************/

/* Operation Function Numbers */

#define   I2O_PARAMS_OPERATION_FIELD_GET               0x0001
#define   I2O_PARAMS_OPERATION_LIST_GET                0x0002
#define   I2O_PARAMS_OPERATION_MORE_GET                0x0003
#define   I2O_PARAMS_OPERATION_SIZE_GET                0x0004
#define   I2O_PARAMS_OPERATION_TABLE_GET               0x0005
#define   I2O_PARAMS_OPERATION_FIELD_SET               0x0006
#define   I2O_PARAMS_OPERATION_LIST_SET                0x0007
#define   I2O_PARAMS_OPERATION_ROW_ADD                 0x0008
#define   I2O_PARAMS_OPERATION_ROW_DELETE              0x0009
#define   I2O_PARAMS_OPERATION_TABLE_CLEAR             0x000A

/* Operations List Header */

typedef struct _I2O_PARAM_OPERATIONS_LIST_HEADER {
#if defined(LITTLE_ENDIAN__)
   U16                         OperationCount;
   U16                         Reserved;
#elif defined(BIG_ENDIAN__)
   U16                         Reserved;
   U16                         OperationCount;
#endif
} I2O_PARAM_OPERATIONS_LIST_HEADER, *PI2O_PARAM_OPERATIONS_LIST_HEADER;

/* Results List Header */

typedef struct _I2O_PARAM_RESULTS_LIST_HEADER {
#if defined(LITTLE_ENDIAN__)
   U16                         ResultCount;
   U16                         Reserved;
#elif defined(BIG_ENDIAN__)
   U16                         Reserved;
   U16                         ResultCount;
#endif
} I2O_PARAM_RESULTS_LIST_HEADER, *PI2O_PARAM_RESULTS_LIST_HEADER;

/* Read Operation Result Block Template Structure */

typedef struct _I2O_PARAM_READ_OPERATION_RESULT {
#if defined(LITTLE_ENDIAN__)
   U16                         BlockSize;
   U8                          BlockStatus;
   U8                          ErrorInfoSize;
   /*                          Operations Results          */
   /*                          Pad (if any)                */
   /*                          ErrorInformation (if any)   */
#elif defined(BIG_ENDIAN__)
   U8                          ErrorInfoSize;
   U8                          BlockStatus;
   U16                         BlockSize;
   /*                          Operations Results          */
   /*                          Pad (if any)                */
   /*                          ErrorInformation (if any)   */
#endif
} I2O_PARAM_READ_OPERATION_RESULT, *PI2O_PARAM_READ_OPERATION_RESULT;

typedef struct _I2O_TABLE_READ_OPERATION_RESULT {
#if defined(LITTLE_ENDIAN__)
   U16                         BlockSize;
   U8                          BlockStatus;
   U8                          ErrorInfoSize;
   U16                         RowCount;
   U16                         MoreFlag;
   /*                          Operations Results          */
   /*                          Pad (if any)                */
   /*                          ErrorInformation (if any)   */
#elif defined(BIG_ENDIAN__)
   U8                          ErrorInfoSize;
   U8                          BlockStatus;
   U16                         BlockSize;
   U16                         MoreFlag;
   U16                         RowCount;
   /*                          Operations Results          */
   /*                          Pad (if any)                */
   /*                          ErrorInformation (if any)   */
#endif
} I2O_TABLE_READ_OPERATION_RESULT, *PI2O_TABLE_READ_OPERATION_RESULT;

/* Error Information Template Structure */

typedef struct _I2O_PARAM_ERROR_INFO_TEMPLATE {
#if defined(LITTLE_ENDIAN__)
   U16                         OperationCode;
   U16                         GroupNumber;
   U16                         FieldIdx;
   U8                          AdditionalStatus;
   U8                          NumberKeys;
   /*                          List of Key Values (variable)   */
   /*                          Pad (if any)                    */
#elif defined(BIG_ENDIAN__)
   U16                         GroupNumber;
   U16                         OperationCode;
   U8                          NumberKeys;
   U8                          AdditionalStatus;
   U16                         FieldIdx;
   /*                          List of Key Values (variable)   */
   /*                          Pad (if any)                    */
#endif 
} I2O_PARAM_ERROR_INFO_TEMPLATE, *PI2O_PARAM_ERROR_INFO_TEMPLATE;

/* Operation Template for Specific Fields */

typedef struct _I2O_PARAM_OPERATION_SPECIFIC_TEMPLATE {
/*#if defined(LITTLE_ENDIAN__)*/
   U16                         Operation;
   U16                         GroupNumber;
   U16                         FieldCount;
   U16                         FieldIdx[1];
   /*                          Pad (if any)                    */
/*#elif defined(BIG_ENDIAN__)
  U16                         GroupNumber;
 U16                         Operation;
   U16                         FieldIdx[1];
   U16                         FieldCount;
 we don't swap this ( SGL data is never swapped)   */
   /*                          Pad (if any)                    */
/*#endif*/
} I2O_PARAM_OPERATION_SPECIFIC_TEMPLATE, *PI2O_PARAM_OPERATION_SPECIFIC_TEMPLATE;

/* Operation Template for All Fields */

typedef struct _I2O_PARAM_OPERATION_ALL_TEMPLATE {
/*#if defined(LITTLE_ENDIAN__)*/
   U16                         Operation;
   U16                         GroupNumber;
   U16                         FieldCount;
   /*                          Pad (if any)                    */
/*#elif defined(BIG_ENDIAN__)
   U16                         GroupNumber;
   U16                         Operation;
   U16                         Pad[1];
   U16                         FieldCount;
                             Pad (if any other)               
 we don't swap this ( SGL data is never swapped)   
#endif*/
} I2O_PARAM_OPERATION_ALL_TEMPLATE, *PI2O_PARAM_OPERATION_ALL_TEMPLATE;

/* Operation Template for All List Fields */

typedef struct _I2O_PARAM_OPERATION_ALL_LIST_TEMPLATE {
#if defined(LITTLE_ENDIAN__)
   U16                         Operation;
   U16                         GroupNumber;
   U16                         FieldCount;
   U16                         KeyCount;
   U8                          KeyValue;
   /*                          Pad (if any)                    */
#elif defined(BIG_ENDIAN__)
   U16                         GroupNumber;
   U16                         Operation;
   U16                         KeyCount;
   U16                         FieldCount;
   U8                          Pad[3];
   U8                          KeyValue;
   /*                          Pad (if any other)              */
#endif
} I2O_PARAM_OPERATION_ALL_LIST_TEMPLATE, *PI2O_PARAM_OPERATION_ALL_LIST_TEMPLATE;

/* Modify Operation Result Block Template Structure */

typedef struct _I2O_PARAM_MODIFY_OPERATION_RESULT {
#if defined(LITTLE_ENDIAN__)
   U16                         BlockSize;
   U8                          BlockStatus;
   U8                          ErrorInfoSize;
   /*                          ErrorInformation (if any)   */
#elif defined(BIG_ENDIAN__)
   U8                          ErrorInfoSize;
   U8                          BlockStatus;
   U16                         BlockSize;
   /*                          ErrorInformation (if any)   */
#endif
} I2O_PARAM_MODIFY_OPERATION_RESULT, *PI2O_PARAM_MODIFY_OPERATION_RESULT;

/* Operation Template for Row Delete  */

typedef struct _I2O_PARAM_OPERATION_ROW_DELETE_TEMPLATE {
#if defined(LITTLE_ENDIAN__)
   U16                         Operation;
   U16                         GroupNumber;
   U16                         RowCount;
   U8                          KeyValue;
#elif defined(BIG_ENDIAN__)
   U16                         GroupNumber;
   U16                         Operation;
   U8                          Pad[1];  /* PLX: Padding necessary for endian conversion */
   U8                          KeyValue;
   U16                         RowCount;
#endif
} I2O_PARAM_OPERATION_ROW_DELETE_TEMPLATE, *PI2O_PARAM_OPERATION_ROW_DELETE_TEMPLATE;

/* Operation Template for Table Clear  */

typedef struct _I2O_PARAM_OPERATION_TABLE_CLEAR_TEMPLATE {
#if defined(LITTLE_ENDIAN__)
   U16                         Operation;
   U16                         GroupNumber;
#elif defined(BIG_ENDIAN__)
   U16                         GroupNumber;
   U16                         Operation;
#endif
} I2O_PARAM_OPERATION_TABLE_CLEAR_TEMPLATE, *PI2O_PARAM_OPERATION_TABLE_CLEAR_TEMPLATE;

/* Status codes and Error Information for Parameter functions */

#define   I2O_PARAMS_STATUS_SUCCESS                0x00
#define   I2O_PARAMS_STATUS_BAD_KEY_ABORT          0x01
#define   I2O_PARAMS_STATUS_BAD_KEY_CONTINUE       0x02
#define   I2O_PARAMS_STATUS_BUFFER_FULL            0x03
#define   I2O_PARAMS_STATUS_BUFFER_TOO_SMALL       0x04
#define   I2O_PARAMS_STATUS_FIELD_UNREADABLE       0x05
#define   I2O_PARAMS_STATUS_FIELD_UNWRITEABLE      0x06
#define   I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS    0x07
#define   I2O_PARAMS_STATUS_INVALID_GROUP_ID       0x08
#define   I2O_PARAMS_STATUS_INVALID_OPERATION      0x09
#define   I2O_PARAMS_STATUS_NO_KEY_FIELD           0x0A
#define   I2O_PARAMS_STATUS_NO_SUCH_FIELD          0x0B
#define   I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP      0x0C
#define   I2O_PARAMS_STATUS_OPERATION_ERROR        0x0D
#define   I2O_PARAMS_STATUS_SCALAR_ERROR           0x0E
#define   I2O_PARAMS_STATUS_TABLE_ERROR            0x0F
#define   I2O_PARAMS_STATUS_WRONG_GROUP_TYPE       0x10


/****************************************************************************/
/* GROUP Parameter Groups */
/****************************************************************************/

/* GROUP Configuration and Operating Structures and Defines */

/* Groups Numbers */

#define    I2O_UTIL_PARAMS_DESCRIPTOR_GROUP_NO          0xF000
#define    I2O_UTIL_PHYSICAL_DEVICE_TABLE_GROUP_NO      0xF001
#define    I2O_UTIL_CLAIMED_TABLE_GROUP_NO              0xF002
#define    I2O_UTIL_USER_TABLE_GROUP_NO                 0xF003
#define    I2O_UTIL_PRIVATE_MESSAGE_EXTENSIONS_GROUP_NO 0xF005
#define    I2O_UTIL_AUTHORIZED_USER_TABLE_GROUP_NO      0xF006
#define    I2O_UTIL_DEVICE_CONFIG_CONTROL_GROUP_NO      0xF007
#define    I2O_UTIL_DEVICE_IDENTITY_GROUP_NO            0xF100
#define    I2O_UTIL_DDM_IDENTITY_GROUP_NO               0xF101
#define    I2O_UTIL_USER_INFORMATION_GROUP_NO           0xF102
#define    I2O_UTIL_SGL_OPERATING_LIMITS_GROUP_NO       0xF103
#define    I2O_UTIL_SENSORS_GROUP_NO                    0xF200

/* UTIL Group F000h - GROUP DESCRIPTORS Parameter Group */

#define    I2O_UTIL_GROUP_PROPERTIES_GROUP_TABLE       0x01
#define    I2O_UTIL_GROUP_PROPERTIES_ROW_ADDITION      0x02
#define    I2O_UTIL_GROUP_PROPERTIES_ROW_DELETION      0x04
#define    I2O_UTIL_GROUP_PROPERTIES_CLEAR_OPERATION   0x08

typedef struct _I2O_UTIL_GROUP_DESCRIPTOR_TABLE {
   U16                         GroupNumber;
   U16                         FieldCount;
   U16                         RowCount;
   U8                          Properties;
   U8                          reserved;
} I2O_UTIL_GROUP_DESCRIPTOR_TABLE, *PI2O_UTIL_GROUP_DESCRIPTOR_TABLE;

/* UTIL Group F001h - Physical Device Table Parameter Group */

typedef struct _I2O_UTIL_PHYSICAL_DEVICE_TABLE {
   U32                         AdapterID;
} I2O_UTIL_PHYSICAL_DEVICE_TABLE, *PI2O_UTIL_PHYSICAL_DEVICE_TABLE;

/* UTIL Group F002h - Claimed Table Parameter Group */

typedef struct _I2O_UTIL_CLAIMED_TABLE {
   U16                         ClaimedTID;
} I2O_UTIL_CLAIMED_TABLE, *PI2O_UTIL_CLAIMED_TABLE;

/* UTIL Group F003h - User Table Parameter Group */

typedef struct _I2O_UTIL_USER_TABLE {
   U16                         Instance;
   U16                         UserTID;
   U8                          ClaimType;
   U8                          ClaimFlags;
   U16                         reserved2;
} I2O_UTIL_USER_TABLE, *PI2O_UTIL_USER_TABLE;

/* UTIL Group F005h - Private Message Extensions Parameter Group */

typedef struct _I2O_UTIL_PRIVATE_MESSAGE_EXTENSIONS_TABLE {
   U16                         ExtInstance;
   U16                         OrganizationID;
   U16                         XFunctionCode;
} I2O_UTIL_PRIVATE_MESSAGE_EXTENSIONS_TABLE, *PI2O_UTIL_PRIVATE_MESSAGE_EXTENSIONS_TABLE;

/* UTIL Group F006h - Authorized User Table Parameter Group */

typedef struct _I2O_UTIL_AUTHORIZED_USER_TABLE {
   U16                         AlternateTID;
} I2O_UTIL_AUTHORIZED_USER_TABLE, *PI2O_UTIL_AUTHORIZED_USER_TABLE;

/* UTIL Group F007h - Device Configuration Control Parameter Group */

typedef struct _I2O_UTIL_DEVICE_CONFIG_CONTROL_SCALAR {
   U8                          NvUpdateRequired;
   U8                          NvUpdateMode;
   U8                          NvUpdateAction;
} I2O_UTIL_DEVICE_CONFIG_CONTROL_SCALAR, *PI2O_UTIL_DEVICE_CONFIG_CONTROL_SCALAR;

/* UTIL Group F100h - Device Identity Parameter Group */

typedef struct _I2O_UTIL_DEVICE_IDENTITY_SCALAR {
   U32                         ClassID;
   U16                         OwnerTID;
   U16                         ParentTID;
   U8                          VendorInfo[I2O_DEVID_VENDOR_INFO_SZ];
   U8                          ProductInfo[I2O_DEVID_PRODUCT_INFO_SZ];
   U8                          Description[I2O_DEVID_DESCRIPTION_SZ];
   U8                          ProductRevLevel[I2O_DEVID_REV_LEVEL_SZ];
   U8                          SNFormat;
   U8                          SerialNumber[I2O_MAX_SERIAL_NUMBER_SZ];
} I2O_UTIL_DEVICE_IDENTITY_SCALAR, *PI2O_UTIL_DEVICE_IDENTITY_SCALAR;

/* UTIL Group F101h - DDM Identity Parameter Group */

typedef struct _I2O_UTIL_DDM_IDENTITY_SCALAR {
   U16                         DdmTID;
   U8                          ModuleName[I2O_MODULE_NAME_SZ];
   U8                          ModuleRevLevel[I2O_DEVID_REV_LEVEL_SZ];
   U8                          SNFormat;
   U8                          SerialNumber[I2O_MAX_SERIAL_NUMBER_SZ];
} I2O_UTIL_DDM_IDENTITY_SCALAR, *PI2O_UTIL_DDM_IDENTITY_SCALAR;

/* UTIL Group F102h - User Information Parameter Group */

#define    I2O_USER_DEVICE_NAME_SZ                     64
#define    I2O_USER_SERVICE_NAME_SZ                    64
#define    I2O_USER_PHYSICAL_LOCATION_SZ               64
#define    I2O_USER_INSTANCE_NUMBER_SZ                 4

typedef struct _I2O_UTIL_USER_INFORMATION_SCALAR {
   U8                          DeviceName[I2O_USER_DEVICE_NAME_SZ];
   U8                          ServiceName[I2O_USER_SERVICE_NAME_SZ];
   U8                          PhysicalLocation[I2O_USER_PHYSICAL_LOCATION_SZ];
   U8                          InstanceNumber[I2O_USER_INSTANCE_NUMBER_SZ];
} I2O_UTIL_USER_INFORMATION_SCALAR, *PI2O_UTIL_USER_INFORMATION_SCALAR;

/* UTIL Group F103h - SGL Operating Limits Parameter Group */

#define    I2O_SGL_UNIT_PHYSICAL_ADDR_SIZE_32BIT       0x1
#define    I2O_SGL_UNIT_PHYSICAL_ADDR_SIZE_64BIT       0x2
#define    I2O_SGL_UNIT_PHYSICAL_ADDR_SIZE_96BIT       0x4
#define    I2O_SGL_UNIT_PHYSICAL_ADDR_SIZE_128BIT      0x8

typedef struct _I2O_UTIL_SGL_OPERATING_LIMITS_SCALAR {
   U32                         SglChainSize;
   U32                         SglChainSizeMax;
   U32                         SglChainSizeTarget;
   U16                         SglFragCount;
   U16                         SglFragCountMax;
   U16                         SglFragCountTarget;
   U16                         SglDataAlignment;
   U8                          SglAddrLimit;
   U8                          SglUnitAddrField;
} I2O_UTIL_SGL_OPERATING_LIMITS_SCALAR, *PI2O_UTIL_SGL_OPERATING_LIMITS_SCALAR;

/* UTIL Group F200h - Sensors Parameter Group */

#define    I2O_SENSOR_COMPONENT_OTHER                  0x00
#define    I2O_SENSOR_COMPONENT_PLANAR_LOGIC_BOARD     0x01
#define    I2O_SENSOR_COMPONENT_CPU                    0x02
#define    I2O_SENSOR_COMPONENT_CHASSIS                0x03
#define    I2O_SENSOR_COMPONENT_POWER_SUPPLY           0x04
#define    I2O_SENSOR_COMPONENT_STORAGE                0x05
#define    I2O_SENSOR_COMPONENT_EXTERNAL               0x06

#define    I2O_SENSOR_SENSOR_CLASS_ANALOG              0x00
#define    I2O_SENSOR_SENSOR_CLASS_DIGITAL             0x01

#define    I2O_SENSOR_SENSOR_TYPE_OTHER                0x00
#define    I2O_SENSOR_SENSOR_TYPE_THERMAL              0x01
#define    I2O_SENSOR_SENSOR_TYPE_DC_VOLTAGE           0x02
#define    I2O_SENSOR_SENSOR_TYPE_AC_VOLTAGE           0x03
#define    I2O_SENSOR_SENSOR_TYPE_DC_CURRENT           0x04
#define    I2O_SENSOR_SENSOR_TYPE_AC_CURRENT           0x05
#define    I2O_SENSOR_SENSOR_TYPE_DOOR_OPEN            0x06
#define    I2O_SENSOR_SENSOR_TYPE_FAN_OPERATIONAL      0x07

#define    I2O_SENSOR_SENSOR_STATE_NORMAL              0x00
#define    I2O_SENSOR_SENSOR_STATE_ABNORMAL            0x01
#define    I2O_SENSOR_SENSOR_STATE_UNKNOWN             0x02
#define    I2O_SENSOR_SENSOR_STATE_LOW_CAT             0x03
#define    I2O_SENSOR_SENSOR_STATE_LOW                 0x04
#define    I2O_SENSOR_SENSOR_STATE_LOW_WARNING         0x05
#define    I2O_SENSOR_SENSOR_STATE_HIGH_WARNING        0x06
#define    I2O_SENSOR_SENSOR_STATE_HIGH                0x07
#define    I2O_SENSOR_SENSOR_STATE_HIGH_CAT            0x08

#define    I2O_SENSOR_EVENT_ENABLE_STATE_CHANGE        0x0001
#define    I2O_SENSOR_EVENT_ENABLE_LOW_CATASTROPHIC    0x0002
#define    I2O_SENSOR_EVENT_ENABLE_LOW_READING         0x0004
#define    I2O_SENSOR_EVENT_ENABLE_LOW_WARNING         0x0008
#define    I2O_SENSOR_EVENT_ENABLE_CHANGE_TO_NORMAL    0x0010
#define    I2O_SENSOR_EVENT_ENABLE_HIGH_WARNING        0x0020
#define    I2O_SENSOR_EVENT_ENABLE_HIGH_READING        0x0040
#define    I2O_SENSOR_EVENT_ENABLE_HIGH_CATASTROPHIC   0x0080


typedef struct _I2O_UTIL_SENSORS_TABLE {
   U16                         SensorInstance;
   U16                         ComponentInstance;
   U8                          Component;
   U8                          SensorClass;
   U8                          SensorType;
   S8                          ScalingExponent;
   S32                         ActualReading;
   S32                         MinimumReading;
   S32                         Low2LowCatThreshold;
   S32                         LowCat2LowThreshold;
   S32                         LowWarn2LowThreshold;
   S32                         Low2LowWarnThreshold;
   S32                         Norm2LowWarnThreshold;
   S32                         LowWarn2NormThreshold;
   S32                         NominalReading;
   S32                         HiWarn2NormThreshold;
   S32                         Norm2HiWarnThreshold;
   S32                         High2HiWarnThreshold;
   S32                         HiWarn2HighThreshold;
   S32                         HiCat2HighThreshold;
   S32                         Hi2HiCatThreshold;
   S32                         MaximumReading;
   U8                          SensorState;
   U16                         EventEnable;
} I2O_UTIL_SENSORS_TABLE, *PI2O_UTIL_SENSORS_TABLE;


PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif    /* I2O_MESSAGE_HDR */
