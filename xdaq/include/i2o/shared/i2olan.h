/*******************************************************************************
 *
 * All software on this website is made available under the following terms and 
 * conditions.  By downloading this software, you agree to abide by these terms
 * and conditions with respect to this software.
 * 
 * I2O SIG All rights reserved.
 * 
 * These header files are provided, pursuant to your I2O SIG membership
 * agreement, free of charge on an as-is basis without warranty of any kind, 
 * either express or implied, including but not limited to, implied warranties 
 * or merchantability and fitness for a particular purpose.  I2O SIG does not 
 * warrant that this program will meet the user's requirements or that the 
 * operation of these programs will be uninterrupted or error-free.  
 * Acceptance and use of this program constitutes the user's understanding 
 * that he will have no recourse to I2O SIG for any actual or consequential 
 * damages including, but not limited to, loss profits arising out of use 
 * or inability to use this program.
 * 
 * Member is permitted to create derivative works to this header-file program.  
 * However, all copies of the program and its derivative works must contain the
 * I2O SIG copyright notice.
 *
 ******************************************************************************/

#if !defined(I2O_LAN_HDR)
#define I2O_LAN_HDR

#include   "i2omsg.h"      /* Include the Base Message file */
#include   "i2outil.h"     /* Include the Utility Message file */

#define I2OLAN_REV 1_5_3   /* I2O LAN header file revision string */

/*****************************************************************************
 *
 *     I2OLAN.h -- I2O Local Area Network Device Class Message defintion file
 *
 *     This file contains information presented in Chapter 6, Section 10 of
 *     the I2O Specification.
 *
 *     Revision History: (Revision History tracks the revision number of the 
 *         I2O specification)
 *
 *     .92     - First marked revsion used for Proof of Concept. 
 *     .93     - Change to match the rev .93 of the spec.
 *     .95     - Updated to Rev .95 of 2/5/96.
 *    1.10     - Updated to the 1.x version of the I2O Specification (10/29/96)
 *    1.51     - Updated to the 1.5 version of the I2O Specification (05/01/97)
 *    1.51a    - Corrected minor errors, added field indices.        (06/30/97)
 *    1.51b    - Modifications as voted on in LAN WG meeting.        (09/15/97)
 *    1.51c    - Updated to match rev 4 of post 1.5 LAN draft.       (10/10/97)
 *    1.51d    - Updated to match rev 5 of post 1.5 LAN draft.       (10/14/97)
 *    1.51e    - Corrections/updates to match spec submitted to CAWG.(10/14/97)
 *    1.52     - Updated to match the 1.5 errata of 6/2/98.          (06/04/98)
 *    1.53     - Corrected typo.                                     (07/20/98)
 *
 *****************************************************************************/

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

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

/* LAN Class specific functions */

#define I2O_LAN_PACKET_SEND                            0x3B
#define I2O_LAN_SDU_SEND                               0x3D
#define I2O_LAN_RECEIVE_POST                           0x3E
#define I2O_LAN_RESET                                  0x35
#define I2O_LAN_SUSPEND                                0x37

/* LAN Generic Defines */

#define    I2O_LAN_ADDRESS_SZ                          0x08

/****************************************************************************/

/* LAN Parameter Groups */

/****************************************************************************/

/* LAN Configuration and Operating Structures and Defines */

/* LAN Groups */

#define I2O_LAN_GROUP_NO_DEVICE_INFO                   0x0000
#define I2O_LAN_GROUP_NO_MAC_ADDRESS                   0x0001
#define I2O_LAN_GROUP_NO_MULTICAST_MAC_ADDRESS         0x0002
#define I2O_LAN_GROUP_NO_BATCH_CONTROL                 0x0003
#define I2O_LAN_GROUP_NO_OPERATION                     0x0004
#define I2O_LAN_GROUP_NO_MEDIA_OPERATION               0x0005
#define I2O_LAN_GROUP_NO_ALTERNATE_ADDRESS             0x0006
#define I2O_LAN_GROUP_NO_TRANSMIT_INFO                 0x0007
#define I2O_LAN_GROUP_NO_RECEIVE_INFO                  0x0008


/* - 0000h - Device Information Parameters defines */

#define I2O_LAN_LANTYPE_ETHERNET                       0x0030
#define I2O_LAN_LANTYPE_100BASEVG                      0x0040
#define I2O_LAN_LANTYPE_TOKEN_RING                     0x0050
#define I2O_LAN_LANTYPE_FDDI                           0x0060
#define I2O_LAN_LANTYPE_FIBRE_CHANNEL                  0x0070

#define I2O_LAN_FLAGS_PHYSICAL_PORT                    0x0000
#define I2O_LAN_FLAGS_EMULATED_LAN                     0x0001
#define I2O_LAN_FLAGS_SIMPLEX                          0x0000
#define I2O_LAN_FLAGS_DUPLEX                           0x0002

/* LAN Address Format defines */

#define I2O_LAN_ADDRESS_FORMAT_IEEE_48BIT              0x00
#define I2O_LAN_ADDRESS_FORMAT_FC_IEEE                 0x01

/* LAN Current Device State defines */

#define I2O_LAN_DEVICE_STATE_UNKNOWN                   0x00
#define I2O_LAN_DEVICE_STATE_UNCLAIMED                 0x01
#define I2O_LAN_DEVICE_STATE_OPERATIONAL               0x02
#define I2O_LAN_DEVICE_STATE_SUSPENDED                 0x03
#define I2O_LAN_DEVICE_STATE_RESETTING                 0x04
#define I2O_LAN_DEVICE_STATE_ERROR                     0x05
#define I2O_LAN_DEVICE_STATE_OPERATIONAL_NO_RX         0x06
#define I2O_LAN_DEVICE_STATE_SUSPENDED_NO_RX           0x07

/* LAN Device Error Status defines */

#define I2O_LAN_DEVICE_ERROR_TRANSMIT_CU               0x0001
#define I2O_LAN_DEVICE_ERROR_RECEIVE_CU                0x0002
#define I2O_LAN_DEVICE_ERROR_LOCAL_MEM_ALLOC           0x0004

/* - 0001h - MAC Addresses Parameter Group */

/* Filter Mask defines */

#define I2O_LAN_UNICAST_DIRECTED_DISABLE               0x00000001
#define I2O_LAN_PROMISCUOUS_ENABLE                     0x00000002
#define I2O_LAN_PROMISCUOUS_MC_ENABLE                  0x00000004
#define I2O_LAN_BROADCAST_DISABLE                      0x00000100
#define I2O_LAN_MULTICAST_DISABLE                      0x00000200
#define I2O_LAN_FUNCTIONAL_ADDRESS_DISABLE             0x00000400

/* Filter Mask ---- Reporting Modes */
#define I2O_LAN_MAC_NONE                               0x00000000
#define I2O_LAN_MAC_PRIORITY                           0x00000800
#define I2O_LAN_MAC_ALL                                0x00001000
#define I2O_LAN_MAC_PROMISCUOUS                        0x00001800

/* Hardware Capability defines */

#define I2O_LAN_HC_UNICAST_DIRECTED_DISABLE            0x00000001
#define I2O_LAN_HC_PROMISCUOUS_ENABLE                  0x00000002
#define I2O_LAN_HC_PROMISCUOUS_MC_ENABLE               0x00000004
#define I2O_LAN_HC_BROADCAST_DISABLE                   0x00000100
#define I2O_LAN_HC_MULTICAST_DISABLE                   0x00000200
#define I2O_LAN_HC_FUNCTIONAL_ADDRESS_DISABLE          0x00000400
#define I2O_LAN_HC_MAC_REPORTING                       0x00000800


/* - 0003h -  Batch Control Parameters defines */

#define I2O_LAN_BATCH_FLAGS_BATCH_DISABLED             0x00000001
#define I2O_LAN_BATCH_FLAGS_CURRENT_MODE_BATCHED       0x00000002
#define I2O_LAN_BATCH_FLAGS_BATCH_FORCED               0x00000004

/* - 0004h -  Operation Parameters defines */

/* User Flags */

#define I2O_LAN_OP_FLAGS_REPORT_TX_ERRORS              0x00000001
#define I2O_LAN_OP_FLAGS_REPORT_RX_BAD_PACKETS         0x00000002

/* Transmit Modes Enable Flags */

#define I2O_LAN_TX_MODES_ENABLE_CRC_SUPPRESSION        0x00000004
#define I2O_LAN_TX_MODES_ENABLE_IPV4_CHKSUM            0x00000100
#define I2O_LAN_TX_MODES_ENABLE_TCP_CHKSUM             0x00000200
#define I2O_LAN_TX_MODES_ENABLE_UDP_CHKSUM             0x00000400
#define I2O_LAN_TX_MODES_ENABLE_RSVP_CHKSUM            0x00000800
#define I2O_LAN_TX_MODES_ENABLE_ICMP_CHKSUM            0x00001000
#define I2O_LAN_TX_MODES_ENABLE_LOOPBACK_SUPPRESSION   0x00020000

/* Receive Modes Enable Flags */

#define I2O_LAN_RX_MODES_ENABLE_FCS_RECEPTION          0x00000004
#define I2O_LAN_RX_MODES_ENABLE_IPV4_CHKSUM            0x00000100
#define I2O_LAN_RX_MODES_ENABLE_TCP_CHKSUM             0x00000200
#define I2O_LAN_RX_MODES_ENABLE_UDP_CHKSUM             0x00000400
#define I2O_LAN_RX_MODES_ENABLE_RSVP_CHKSUM            0x00000800
#define I2O_LAN_RX_MODES_ENABLE_ICMP_CHKSUM            0x00001000

/* - 0005h -  Media Operation Parameters defines */

/* Connector Type defines */

#define I2O_LAN_CONNECTOR_OTHER                        0x00000000
#define I2O_LAN_CONNECTOR_UNKNOWN                      0x00000001
#define I2O_LAN_CONNECTOR_AUI                          0x00000002
#define I2O_LAN_CONNECTOR_UTP                          0x00000003
#define I2O_LAN_CONNECTOR_BNC                          0x00000004
#define I2O_LAN_CONNECTOR_RJ45                         0x00000005
#define I2O_LAN_CONNECTOR_STP_DB9                      0x00000006
#define I2O_LAN_CONNECTOR_FIBER_MIC                    0x00000007
#define I2O_LAN_CONNECTOR_APPLE_AUI                    0x00000008
#define I2O_LAN_CONNECTOR_MII                          0x00000009
#define I2O_LAN_CONNECTOR_DB9                          0x0000000A
#define I2O_LAN_CONNECTOR_HSSDC                        0x0000000B
#define I2O_LAN_CONNECTOR_DUPLEX_SC_FIBER              0x0000000C
#define I2O_LAN_CONNECTOR_DUPLEX_ST_FIBER              0x0000000D
#define I2O_LAN_CONNECTOR_TNC_BNC                      0x0000000E
#define I2O_LAN_CONNECTOR_DEFAULT                      0xFFFFFFFF

/* Connection Type defines */

    /* Ethernet types */
#define I2O_LAN_CONNECTION_UNKNOWN                     0x00000000
#define I2O_LAN_CONNECTION_AUI                         (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000001
#define I2O_LAN_CONNECTION_10BASE5                     (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000002
#define I2O_LAN_CONNECTION_FIORL                       (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000003
#define I2O_LAN_CONNECTION_10BASE2                     (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000004
#define I2O_LAN_CONNECTION_10BROAD36                   (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000005
#define I2O_LAN_CONNECTION_10BASE_T                    (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000006
#define I2O_LAN_CONNECTION_10BASE_FP                   (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000007
#define I2O_LAN_CONNECTION_10BASE_FB                   (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000008
#define I2O_LAN_CONNECTION_10BASE_FL                   (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000009
#define I2O_LAN_CONNECTION_100BASE_TX                  (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000A
#define I2O_LAN_CONNECTION_100BASE_FX                  (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000B
#define I2O_LAN_CONNECTION_100BASE_T4                  (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000C
#define I2O_LAN_CONNECTION_1000BASE_SX                 (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000D
#define I2O_LAN_CONNECTION_1000BASE_LX                 (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000E
#define I2O_LAN_CONNECTION_1000BASE_CX                 (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x0000000F
#define I2O_LAN_CONNECTION_1000BASE_T                  (I2O_LAN_LANTYPE_ETHERNET << 4) + 0x00000010

    /* AnyLAN types */
#define I2O_LAN_CONNECTION_100VG_ETHERNET              (I2O_LAN_LANTYPE_100VG_ANYLAN << 4) + 0x00000001
#define I2O_LAN_CONNECTION_100VG_TR                    (I2O_LAN_LANTYPE_100VG_ANYLAN << 4) + 0x00000002

    /* Token Ring types */
#define I2O_LAN_CONNECTION_4MBIT                       (I2O_LAN_LANTYPE_TOKEN_RING << 4) + 0x00000001
#define I2O_LAN_CONNECTION_16MBIT                      (I2O_LAN_LANTYPE_TOKEN_RING << 4) + 0x00000002

    /* FDDI types */
#define I2O_LAN_CONNECTION_125MBAUD                    (I2O_LAN_LANTYPE_FDDI << 4) + 0x00000001

    /* Fibre Channel types */
#define I2O_LAN_CONNECTION_POINT_POINT                 (I2O_LAN_LANTYPE_FIBRE_CHANNEL << 4) + 0x00000001
#define I2O_LAN_CONNECTION_ARB_LOOP                    (I2O_LAN_LANTYPE_FIBRE_CHANNEL << 4) + 0x00000002
#define I2O_LAN_CONNECTION_PUBLIC_LOOP                 (I2O_LAN_LANTYPE_FIBRE_CHANNEL << 4) + 0x00000003
#define I2O_LAN_CONNECTION_FABRIC                      (I2O_LAN_LANTYPE_FIBRE_CHANNEL << 4) + 0x00000004
#define I2O_LAN_CONNECTION_EMULATION                   0x00000F00
#define I2O_LAN_CONNECTION_OTHER                       0x00000F01
#define I2O_LAN_CONNECTION_DEFAULT                     0xFFFFFFFF

/* Duplex Mode & Duplex Mode Target defines */

#define I2O_LAN_DUPLEX_MODE_HALF_DUPLEX                0x00
#define I2O_LAN_DUPLEX_MODE_FULL_DUPLEX                0x01
#define I2O_LAN_DUPLEX_MODE_RESET_TO_DEFAULT           0xFF

/* Link Status defines */

#define I2O_LAN_LSTAT_UNKNOWN                          0x00
#define I2O_LAN_LSTAT_NORMAL                           0x01
#define I2O_LAN_LSTAT_FAILURE                          0x02
#define I2O_LAN_LSTAT_RESET                            0x03
#define I2O_LAN_LSTAT_OTHER                            0xFF

/* - 0007h -  Transmit Control Parameters defines */

/* Tx Modes bit map defines */

#define I2O_LAN_TXMODE_NO_DA_IN_SGL                    0x00000002
#define I2O_LAN_TXMODE_CRC_SUPPRESSION                 0x00000004
#define I2O_LAN_TXMODE_MAC_INSERTION                   0x00000010
#define I2O_LAN_TXMODE_RIF_INSERTION                   0x00000020
#define I2O_LAN_TXMODE_IPV4_CHKSUM                     0x00000100
#define I2O_LAN_TXMODE_TCP_CHKSUM                      0x00000200
#define I2O_LAN_TXMODE_UDP_CHKSUM                      0x00000400
#define I2O_LAN_TXMODE_RSVP_CHKSUM                     0x00000800
#define I2O_LAN_TXMODE_ICMP_CHKSUM                     0x00001000
#define I2O_LAN_TXMODE_LOOPBACK_ENABLE                 0x00008000
#define I2O_LAN_TXMODE_LOOPBACK_SUPPRESSION_ENABLE     0x00010000


/* - 0008h -  Receiver Control Parameters defines */

/* Rx Modes bit map defines */

#define I2O_LAN_RXMODE_FCS_RECEPTION                   0x00000004
#define I2O_LAN_RXMODE_IPV4_CHKSUM                     0x00000100
#define I2O_LAN_RXMODE_TCP_CHKSUM                      0x00000200
#define I2O_LAN_RXMODE_UDP_CHKSUM                      0x00000400
#define I2O_LAN_RXMODE_RSVP_CHKSUM                     0x00000800
#define I2O_LAN_RXMODE_ICMP_CHKSUM                     0x00001000


/* LAN Group 0000h - Device Information Parameter Group */

typedef enum {
    FieldIdx_DI_LANType                   =  0,
    FieldIdx_DI_Flags                     =  1,
    FieldIdx_DI_AddressFormat             =  2,
    FieldIdx_DI_CurrentDeviceState        =  3,
    FieldIdx_DI_DeviceErrorStatus         =  4,
    FieldIdx_DI_MinPacketSize             =  5,
    FieldIdx_DI_MaxPacketSize             =  6,
    FieldIdx_DI_HardwareAddress           =  7,
    FieldIdx_DI_MaxTxWireSpeed            =  8,
    FieldIdx_DI_MaxRxWireSpeed            =  9,
    FieldIdx_DI_MinSduSize                = 10,
    FieldIdx_DI_MaxSduSize                = 11,
    FieldIdx_DI_Reserved                  = 12
} I2O_LAN_DEVICE_INFO_FIELDIDX;

typedef struct _I2O_LAN_DEVICE_INFO_SCALAR {
    U16                    LANType;
    U16                    Flags;
    U8                     AddressFormat;
    U8                     CurrentDeviceState;
    U16                    DeviceErrorStatus;
    U32                    MinPacketSize;
    U32                    MaxPacketSize;
    U8                     HardwareAddress[I2O_LAN_ADDRESS_SZ];
    U64                    MaxTxWireSpeed;
    U64                    MaxRxWireSpeed;
    U32                    MinSduSize;
    U32                    MaxSduSize;
    U32                    Reserved;
} I2O_LAN_DEVICE_INFO_SCALAR, *PI2O_LAN_DEVICE_INFO_SCALAR;


/* LAN Group 0001h - MAC Addresses Parameter Group */

typedef enum {
    FieldIdx_MA_ActiveAddress             =  0,
    FieldIdx_MA_CurrNetworkAddress        =  1,
    FieldIdx_MA_FunctionalAddressMask     =  2,
    FieldIdx_MA_FilterMask                =  3,
    FieldIdx_MA_HardwareCapability        =  4,
    FieldIdx_MA_MaxSizeMulticastTable     =  5,
    FieldIdx_MA_MaxFilterPerfect          =  6,
    FieldIdx_MA_MaxFilterImperfect        =  7
} I2O_LAN_MAC_ADDRESS_FIELDIDX;

typedef struct _I2O_LAN_MAC_ADDRESS_SCALAR {
    U8                     ActiveAddress[I2O_LAN_ADDRESS_SZ];
    U8                     CurrNetworkAddress[I2O_LAN_ADDRESS_SZ];
    U64                    FunctionalAddressMask;
    U32                    FilterMask;
    U32                    HardwareCapability;
    U32                    MaxSizeMulticastTable;
    U32                    MaxFilterPerfect;
    U32                    MaxFilterImperfect;
} I2O_LAN_MAC_ADDRESS_SCALAR, *PI2O_LAN_MAC_ADDRESS_SCALAR;


/* LAN Group 0002h - Multicast MAC Addresses Parameter Group */

typedef enum {
    FieldIdx_MMA_MulticastMACAddress       =  0
} I2O_LAN_MULTICAST_MAC_ADDRESS_FIELDIDX;

typedef struct _I2O_LAN_MULTICAST_MAC_ADDRESS_TABLE {
    U8                     MulticastMACAddress[I2O_LAN_ADDRESS_SZ];
} I2O_LAN_MULTICAST_MAC_ADDRESS_TABLE, *PI2O_LAN_MULTICAST_MAC_ADDRESS_TABLE;


/* LAN Group 0003h - Batch Mode Control Parameter Group */

typedef enum {
    FieldIdx_BC_BatchFlags                =  0,
    FieldIdx_BC_Reserved1                 =  1,
    FieldIdx_BC_Reserved2                 =  2,
    FieldIdx_BC_Reserved3                 =  3,
    FieldIdx_BC_Reserved4                 =  4,
    FieldIdx_BC_MaxRxBatchCount           =  5,
    FieldIdx_BC_MaxRxBatchDelay           =  6,
    FieldIdx_BC_MaxTxBatchDelay           =  7,
    FieldIdx_BC_MaxTxBatchCount           =  8
} I2O_LAN_BATCH_CONTROL_FIELDIDX;

typedef struct _I2O_LAN_BATCH_CONTROL_SCALAR {
    U32                    BatchFlags;
    U32                    Reserved1;
    U32                    Reserved2;
    U32                    Reserved3;
    U32                    Reserved4;
    U32                    MaxRxBatchCount;
    U32                    MaxRxBatchDelay;
    U32                    MaxTxBatchDelay;
    U32                    MaxTxBatchCount;
} I2O_LAN_BATCH_CONTROL_SCALAR, *PI2O_LAN_BATCH_CONTROL_SCALAR;


/* LAN Group 0004h - Operations Parameter Group */

typedef enum {
    FieldIdx_O_PacketPrePad              =  0,
    FieldIdx_O_UserFlags                 =  1,
    FieldIdx_O_PacketOrphanLimit         =  2,
    FieldIdx_O_TxModesEnable             =  3,
    FieldIdx_O_RxModesEnable             =  4
} I2O_LAN_OPERATION_FIELDIDX;

typedef struct _I2O_LAN_OPERATION_SCALAR {
    U32                    PacketPrePad;
    U32                    UserFlags;
    U32                    PacketOrphanLimit;
    U32                    TxModesEnable;
    U32                    RxModesEnable;
} I2O_LAN_OPERATION_SCALAR, *PI2O_LAN_OPERATION_SCALAR;


/* LAN Group 0005h - Media Operations Parameter Group */

typedef enum {
    FieldIdx_MO_ConnectorType             =  0,
    FieldIdx_MO_ConnectionType            =  1,
    FieldIdx_MO_CurrentTxWireSpeed        =  2,
    FieldIdx_MO_CurrentRxWireSpeed        =  3,
    FieldIdx_MO_DuplexMode                =  4,
    FieldIdx_MO_LinkStatus                =  5,
    FieldIdx_MO_Reserved1                 =  6,
    FieldIdx_MO_DuplexModeTarget          =  7,
    FieldIdx_MO_ConnectorTypeTarget       =  8,
    FieldIdx_MO_ConnectionTypeTarget      =  9
} I2O_LAN_MEDIA_OPERATION_FIELDIDX;

typedef struct _I2O_LAN_MEDIA_OPERATION_SCALAR {
    U32                    ConnectorType;
    U32                    ConnectionType;
    U64                    CurrentTxWireSpeed;
    U64                    CurrentRxWireSpeed;
    U8                     DuplexMode;
    U8                     LinkStatus;
    U8                     Reserved;
    U8                     DuplexModeTarget;
    U32                    ConnectorTypeTarget;
    U32                    ConnectionTypeTarget;
} I2O_LAN_MEDIA_OPERATION_SCALAR, *PI2O_LAN_MEDIA_OPERATION_SCALAR;


/* LAN Group 0006h - Alternate MAC Addresses Parameter Group */

typedef enum {
    FieldIdx_AA_AlternateAddress          =  0
} I2O_LAN_ALTERNATE_ADDRESS_FIELDIDX;

typedef struct _I2O_LAN_ALTERNATE_ADDRESS_TABLE {
    U8                     AlternateAddress[I2O_LAN_ADDRESS_SZ];
} I2O_LAN_ALTERNATE_ADDRESS_TABLE, *PI2O_LAN_ALTERNATE_ADDRESS_TABLE;


/* LAN Group 0007h - Transmit Information Parameter Group */

typedef enum {
    FieldIdx_TI_TxMaxPacketSG             =  0,
    FieldIdx_TI_TxMaxChainSG              =  1,
    FieldIdx_TI_TxMaxPktsOut              =  2,
    FieldIdx_TI_TxMaxReqPkts              =  3,
    FieldIdx_TI_TxModes                   =  4
} I2O_LAN_TRANSMIT_INFO_FIELDIDX;

typedef struct _I2O_LAN_TRANSMIT_INFO_SCALAR {
    U32                    TxMaxPacketSG;
    U32                    TxMaxChainSG;
    U32                    TxMaxPktsOut;
    U32                    TxMaxReqPkts;
    U32                    TxModes;
} I2O_LAN_TRANSMIT_INFO_SCALAR, *PI2O_LAN_TRANSMIT_INFO_SCALAR;


/* LAN Group 0008h - Receive Information Parameter Group */

typedef enum {
    FieldIdx_RI_RxMaxChain                =  0,
    FieldIdx_RI_RxMaxBuckets              =  1,
    FieldIdx_RI_RxModes                   =  2,
    FieldIdx_RI_RxMaxBucketsReply         =  3,
    FieldIdx_RI_RxMaxPacketsBucket        =  4,
    FieldIdx_RI_RxMaxPostBuckets          =  5

} I2O_LAN_RECEIVE_INFO_FIELDIDX;

typedef struct _I2O_LAN_RECEIVE_INFO_SCALAR {
    U32                    RxMaxChain;
    U32                    RxMaxBuckets;
    U32                    RxModes;
    U32                    RxMaxBucketsReply;
    U32                    RxMaxPacketsBucket;
    U32                    RxMaxPostBuckets;
} I2O_LAN_RECEIVE_INFO_SCALAR, *PI2O_LAN_RECEIVE_INFO_SCALAR;



/****************************************************************************/

/* Packet Offset flags in the Bucket Descriptor (BD) defines */

#define I2O_LAN_BD_VALID_PACKET                        0x00
#define I2O_LAN_BD_PACKET_ERROR                        0x01
#define I2O_LAN_BD_SKIP_SPACE                          0x02
#define I2O_LAN_BD_PACKET_BUCKET_MASK                  0x0E
#define I2O_LAN_BD_PACKET_CONTINUED                    0x04
#define I2O_LAN_BD_PACKET_NEXT_BUCKET                  0x08
#define I2O_LAN_BD_NETWORK_CHKSUM_VALIDATED            0x10
#define I2O_LAN_BD_TRANSPORT_CHKSUM_VALIDATED          0x20
#define I2O_LAN_BD_LAST_PACKET                         0x40
#define I2O_LAN_BD_LAST_BUCKET                         0xC0

/* Packet Status defines */

#define I2O_LAN_SUCCESS                                0x00
#define I2O_LAN_CRC_ERROR                              0x01
#define I2O_LAN_ALIGNMENT_ERROR                        0x02
#define I2O_LAN_PACKET_TOO_LONG                        0x03
#define I2O_LAN_PACKET_TOO_SHORT                       0x04
#define I2O_LAN_RECEIVE_OVERRUN                        0x05
#define I2O_LAN_NETWORK_CHKSUM_FAILED                  0x40
#define I2O_LAN_TRANSPORT_CHKSUM_FAILED                0X80
#define I2O_LAN_NETWORK_AND_TRANSPORT_CHKSUM_FAILED    0XC0
#define I2O_LAN_OTHER_ERROR                            0xFF

/* Packet/Bucket Descriptor field size defines */

#define I2O_LAN_PACKET_OFFSET_LENGTH_SZ                0x18
#define I2O_LAN_PACKET_FLAGS_SZ                        0x08
#define I2O_LAN_PACKET_LENGTH_SZ                       0x18
#define I2O_LAN_PACKET_STATUS_SZ                       0x08


/* LAN Single Packet Descriptor  */

typedef struct _I2O_LAN_PACKET_INFO {
        BF                PacketOffset:I2O_LAN_PACKET_OFFSET_LENGTH_SZ;
        BF                PacketFlags:I2O_LAN_PACKET_FLAGS_SZ;
        BF                PacketLength:I2O_LAN_PACKET_LENGTH_SZ;
        BF                PacketStatus:I2O_LAN_PACKET_STATUS_SZ;
} I2O_LAN_PACKET_INFO, *PI2O_LAN_PACKET_INFO;


/* LAN Receive Bucket Descriptor (BD) */

typedef struct _I2O_LAN_BUCKET_DESCRIPTOR {
    I2O_TRANSACTION_CONTEXT    BucketContext;        /* aka TransactionContext */
    I2O_LAN_PACKET_INFO        PacketInfo[1];
} I2O_LAN_BUCKET_DESCRIPTOR, *PI2O_LAN_BUCKET_DESCRIPTOR;


/* LAN Receive Packet Descriptor Block (PDB) */

typedef struct _I2O_LAN_PACKET_DESCRIPTOR {
    I2O_LAN_BUCKET_DESCRIPTOR      BDEntry[1];
} I2O_LAN_PACKET_DESCRIPTOR, *PI2O_LAN_PACKET_DESCRIPTOR;


/****************************************************************************/

/* Event Masks */

#define I2O_LAN_EVENT_LINK_DOWN                        0x01
#define I2O_LAN_EVENT_LINK_UP                          0x02
#define I2O_LAN_EVENT_MEDIA_CHANGE                     0x04

/****************************************************************************/

/* Transmit Control Word defines */

#define I2O_LAN_TCW_ACCESS_PRIORITY_MASK               0x00000007
#define I2O_LAN_TCW_SUPPRESS_CRC                       0x00000008
#define I2O_LAN_TCW_GENERATE_NETWORK_LAYER_CHKSUM      0x00000020
#define I2O_LAN_TCW_GENERATE_TRANSPORT_LAYER_CHKSUM    0x00000040

/* Transmit Control Word Reply Modes */
#define I2O_LAN_TCW_USE_BATCH_RULES                    0x00000000
#define I2O_LAN_TCW_REPLY_IMMEDIATELY                  0x40000000
#define I2O_LAN_TCW_REPLY_UNSUCCESSFUL                 0x80000000
#define I2O_LAN_TCW_NO_REPLY_REQUIRED                  0xC0000000

/****************************************************************************/

/* DetailedStatusCode defines */

#define I2O_LAN_DSC_SUCCESS                            0x00
#define I2O_LAN_DSC_DEVICE_FAILURE                     0x01
#define I2O_LAN_DSC_DESTINATION_NOT_FOUND              0x02
#define I2O_LAN_DSC_TRANSMIT_ERROR                     0x03
#define I2O_LAN_DSC_TRANSMIT_ABORTED                   0x04
#define I2O_LAN_DSC_RECEIVE_ERROR                      0x05
#define I2O_LAN_DSC_RECEIVE_ABORTED                    0x06
#define I2O_LAN_DSC_DMA_ERROR                          0x07
#define I2O_LAN_DSC_BAD_PACKET_DETECTED                0x08
#define I2O_LAN_DSC_OUT_OF_MEMORY                      0x09
#define I2O_LAN_DSC_BUCKET_OVERRUN                     0x0A
#define I2O_LAN_DSC_IOP_INTERNAL_ERROR                 0x0B
#define I2O_LAN_DSC_CANCELED                           0x0C
#define I2O_LAN_DSC_INVALID_TRANSACTION_CONTEXT        0x0D
#define I2O_LAN_DSC_DEST_ADDRESS_DETECTED              0x0E
#define I2O_LAN_DSC_DEST_ADDRESS_OMITTED               0x0F
#define I2O_LAN_DSC_PARTIAL_PACKET_RETURNED            0x10
#define I2O_LAN_DSC_TEMP_SUSPENDED_STATE               0x11


/****************************************************************************/

/* I2O LAN Reset and Suspend Resource Flags Defines */

#define I2O_LAN_RESOURCE_FLAG_RETURN_POSTED_BUCKETS    0x01
#define I2O_LAN_RESOURCE_FLAG_RETURN_PEND_TRANSMITS    0x02

/****************************************************************************/

/* I2O LAN Packet or SDU Send Function Message Frame structure. */

typedef struct _I2O_LAN_SEND_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   U32                         TransmitControlWord;
   I2O_SG_ELEMENT              SGL;
} I2O_LAN_SEND_MESSAGE, *PI2O_LAN_SEND_MESSAGE;


    /* I2O LAN Send Reply function structure */

typedef struct _I2O_LAN_SEND_REPLY {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRL_CONTROL_WORD        TrlControlWord;
   U16                         DetailedStatusCode;
   U8                          reserved;
   U8                          RequestStatus;
   I2O_TRANSACTION_CONTEXT     TransactionContext[1];
} I2O_LAN_SEND_REPLY, *PI2O_LAN_SEND_REPLY;

/****************************************************************************/


/* I2O LAN Receive Post Buckets Function Message Frame structure. */

typedef struct _I2O_LAN_RECEIVE_POST_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   U32                         BucketCount;
   I2O_SG_ELEMENT              SGL;
} I2O_LAN_RECEIVE_POST_MESSAGE, *PI2O_LAN_RECEIVE_POST_MESSAGE;


    /* I2O LAN Indirect Receive Reply function structure */

typedef struct _I2O_LAN_RECEIVE_REPLY {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRL_CONTROL_WORD        TrlControlWord;
   U16                         DetailedStatusCode;
   U8                          reserved;
   U8                          RequestStatus;
   U32                         BucketsRemaining;
/* I2O_LAN_PACKET_DESCRIPTOR   PdbArray;           if normal reply */
/* I2O_TRANSACTION_CONTEXT     BucketContext[1];   if ret canceled buckets*/
} I2O_LAN_RECEIVE_REPLY, *PI2O_LAN_RECEIVE_REPLY;


/****************************************************************************/


/* I2O LAN Reset Function Message Frame structure. */

typedef struct _I2O_LAN_RESET_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         Reserved;
   U16                         ResourceFlags;
} I2O_LAN_RESET_MESSAGE, *PI2O_LAN_RESET_MESSAGE;


/****************************************************************************/


/* I2O LAN Suspend Function Message Frame structure. */

typedef struct _I2O_LAN_SUSPEND_MESSAGE {
   I2O_MESSAGE_FRAME           StdMessageFrame;
   I2O_TRANSACTION_CONTEXT     TransactionContext;
   U16                         Reserved;
   U16                         ResourceFlags;
} I2O_LAN_SUSPEND_MESSAGE, *PI2O_LAN_SUSPEND_MESSAGE;


/****************************************************************************/


/* LAN Statistics Structures and Defines */

#define I2O_LAN_GROUP_NO_HIST_STATS                            0x0100
#define I2O_LAN_GROUP_NO_SUPPORTED_OPTIONAL_HIST_STATS         0x0180
#define I2O_LAN_GROUP_NO_0x0181_RESERVED                       0x0181
#define I2O_LAN_GROUP_NO_OPTIONAL_TX_HIST_STATS                0x0182
#define I2O_LAN_GROUP_NO_OPTIONAL_RX_HIST_STATS                0x0183
#define I2O_LAN_GROUP_NO_OPTIONAL_CHKSUM_HIST_STATS            0x0184
#define I2O_LAN_GROUP_NO_802_3_HIST_STATS                      0x0200
#define I2O_LAN_GROUP_NO_SUPPORTED_802_3_HIST_STATS            0x0280
#define I2O_LAN_GROUP_NO_OPTIONAL_802_3_HIST_STATS             0x0281
#define I2O_LAN_GROUP_NO_802_5_HIST_STATS                      0x0300
#define I2O_LAN_GROUP_NO_SUPPORTED_802_5_HIST_STATS            0x0380
#define I2O_LAN_GROUP_NO_OPTIONAL_802_5_HIST_STATS             0x0381
#define I2O_LAN_GROUP_NO_FDDI_HIST_STATS                       0x0400
#define I2O_LAN_GROUP_NO_SUPPORTED_FDDI_HIST_STATS             0x0480
#define I2O_LAN_GROUP_NO_OPTIONAL_FDDI_HIST_STATS              0x0481
#define I2O_LAN_GROUP_NO_FC_HIST_STATS                         0x0500
#define I2O_LAN_GROUP_NO_SUPPORTED_FC_HIST_STATS               0x0580
#define I2O_LAN_GROUP_NO_OPTIONAL_FC_HIST_STATS                0x0581


/* LAN Group 0100h - Required Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_HS_TotalPacketsTransmitted   =  0,
    FieldIdx_HS_TotalBytesTransmitted     =  1,
    FieldIdx_HS_TotalPacketsReceived      =  2,
    FieldIdx_HS_TotalBytesReceived        =  3,
    FieldIdx_HS_TotalTransmitErrors       =  4,
    FieldIdx_HS_TotalReceiveErrors        =  5,
    FieldIdx_HS_ReceiveNoBuffer           =  6,
    FieldIdx_HS_AdapterResetCount         =  7,
    FieldIdx_HS_AdapterSuspendCount       =  8
} I2O_LAN_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_HIST_STATS_SCALAR {
    U64                    TotalPacketsTransmitted;
    U64                    TotalBytesTransmitted;
    U64                    TotalPacketsReceived;
    U64                    TotalBytesReceived;
    U64                    TotalTransmitErrors;
    U64                    TotalReceiveErrors;
    U64                    ReceiveNoBuffer;
    U64                    AdapterResetCount;
    U64                    AdapterSuspendCount;
} I2O_LAN_HIST_STATS_SCALAR, *PI2O_LAN_HIST_STATS_SCALAR;


/* LAN Group 0180h - Optional Supported Generic Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_OHSS_Generic_Reserved =  0,
    FieldIdx_OHSS_Generic_Stat182Supported =  1,
    FieldIdx_OHSS_Generic_Stat183Supported =  2,
    FieldIdx_OHSS_Generic_Stat184Supported =  3
} I2O_LAN_OPT_HIST_STATS_SUPP_FIELDIDX;

typedef struct _I2O_LAN_OPT_HIST_STATS_SUPP_SCALAR {
    U64                    Reserved;
    U64                    Stat182Supported;
    U64                    Stat183Supported;
    U64                    Stat184Supported;
} I2O_LAN_OPT_HIST_STATS_SUPP_SCALAR, *PI2O_LAN_OPT_HIST_STATS_SUPP_SCALAR;


/* LAN Group 0181h - Optional Generic Historical Statistics Parameter Group */
/* Retired/Reserved */

/* LAN Group 0182h - Optional Non Media Specific Transmit Historical Statistics Parameter Group */
typedef enum {
    FieldIdx_OTXHS_TxRetryCount              =  0,
    FieldIdx_OTXHS_DirectedBytesTx           =  1,
    FieldIdx_OTXHS_DirectedPacketsTx         =  2,
    FieldIdx_OTXHS_MulticastBytesTx          =  3,
    FieldIdx_OTXHS_MulticastPacketsTx        =  4,
    FieldIdx_OTXHS_BroadcastBytesTx          =  5,
    FieldIdx_OTXHS_BroadcastPacketsTx        =  6,
    FieldIdx_OTXHS_TotalGroupAddrTxCount     =  7,
    FieldIdx_OTXHS_TotalTxPacketsTooShort    =  8
} I2O_LAN_OPT_TX_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_OPT_TX_HIST_STATS_SCALAR {
    U64                    TxRetryCount;
    U64                    DirectedBytesTx;
    U64                    DirectedPacketsTx;
    U64                    MulticastBytesTx;
    U64                    MulticastPacketsTx;
    U64                    BroadcastBytesTx;
    U64                    BroadcastPacketsTx;
    U64                    TotalGroupAddrTxCount;
    U64                    TotalTxPacketsTooShort;
} I2O_LAN_OPT_TX_HIST_STATS_SCALAR, *PI2O_LAN_OPT_TX_HIST_STATS_SCALAR;

/* LAN Group 0183h - Optional Non Media Specific Receive Historical Statistics Parameter Group */
typedef enum {
    FieldIdx_ORXHS_ReceiveCRCErrorCount      =  0,
    FieldIdx_ORXHS_DirectedBytesRx           =  1,
    FieldIdx_ORXHS_DirectedPacketsRx         =  2,
    FieldIdx_ORXHS_MulticastBytesRx          =  3,
    FieldIdx_ORXHS_MulticastPacketsRx        =  4,
    FieldIdx_ORXHS_BroadcastBytesRx          =  5,
    FieldIdx_ORXHS_BroadcastPacketsRx        =  6,
    FieldIdx_ORXHS_TotalGroupAddrRxCount     =  7,
    FieldIdx_ORXHS_TotalRxPacketsTooShort    =  8,
    FieldIdx_ORXHS_TotalRxPacketsTooLong     =  9,
    FieldIdx_ORXHS_TotalRuntPacketsReceived  = 10
} I2O_LAN_OPT_RX_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_OPT_RX_HIST_STATS_SCALAR {
    U64                    ReceiveCRCErrorCount;
    U64                    DirectedBytesRx;
    U64                    DirectedPacketsRx;
    U64                    MulticastBytesRx;
    U64                    MulticastPacketsRx;
    U64                    BroadcastBytesRx;
    U64                    BroadcastPacketsRx;
    U64                    TotalGroupAddrRxCount;
    U64                    TotalRxPacketsTooShort;
    U64                    TotalRxPacketsTooLong;
    U64                    TotalRuntPacketsReceived;
} I2O_LAN_OPT_RX_HIST_STATS_SCALAR, *PI2O_LAN_OPT_RX_HIST_STATS_SCALAR;

/* LAN Group 0184h - Optional Non Media Specific Checksum Historical Statistics Parameter Group */
typedef enum {
    FieldIdx_OCSHS_GenerateIPv4              =  0,
    FieldIdx_OCSHS_ValidateSuccessIPv4       =  1,
    FieldIdx_OCSHS_ValidateErrorIPv4         =  2,
    FieldIdx_OCSHS_GenerateTCP               =  3,
    FieldIdx_OCSHS_ValidateSuccessTCP        =  4,
    FieldIdx_OCSHS_ValidateErrorTCP          =  5,
    FieldIdx_OCSHS_GenerateUDP               =  6,
    FieldIdx_OCSHS_ValidateSuccessUDP        =  7,
    FieldIdx_OCSHS_ValidateErrorUDP          =  8,
    FieldIdx_OCSHS_GenerateRSVP              =  9,
    FieldIdx_OCSHS_ValidateSuccessRSVP       = 10,
    FieldIdx_OCSHS_ValidateErrorRSVP         = 11,
    FieldIdx_OCSHS_GenerateICMP              = 12,
    FieldIdx_OCSHS_ValidateSuccessICMP       = 13,
    FieldIdx_OCSHS_ValidateErrorICMP         = 14
} I2O_LAN_OPT_CHKSUM_HIST_STATS_FIELDIDX;


typedef struct _I2O_LAN_OPT_CHKSUM_HIST_STATS_SCALAR {
    U64                    GenerateIPv4;
    U64                    ValidateSuccessIPv4;
    U64                    ValidateErrorIPv4;
    U64                    GenerateTCP;
    U64                    ValidateSuccessTCP;
    U64                    ValidateErrorTCP;
    U64                    GenerateUDP;
    U64                    ValidateSuccessUDP;
    U64                    ValidateErrorUDP;
    U64                    GenerateRSVP;
    U64                    ValidateSuccessRSVP;
    U64                    ValidateErrorRSVP;
    U64                    GenerateICMP;
    U64                    ValidateSuccessICMP;
    U64                    ValidateErrorICMP;
} I2O_LAN_OPT_CHKSUM_HIST_STATS_SCALAR, *PI2O_LAN_OPT_CHKSUM_HIST_STATS_SCALAR;

/*-----------------------------------*/
/* - 802.3 Media specific statistics */

/* LAN Group 0200h - Required 802.3 Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_8023HS_RxAlignmentError          =  0,
    FieldIdx_8023HS_TxOneCollision            =  1,
    FieldIdx_8023HS_TxMultipleCollisions      =  2,
    FieldIdx_8023HS_TxDeferred                =  3,
    FieldIdx_8023HS_TxLateCollision           =  4,
    FieldIdx_8023HS_TxMaxCollisions           =  5,
    FieldIdx_8023HS_TxCarrierLost             =  6,
    FieldIdx_8023HS_TxExcessiveDeferrals      =  7
} I2O_LAN_802_3_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_802_3_HIST_STATS_SCALAR {
    U64                    RxAlignmentError;
    U64                    TxOneCollision;
    U64                    TxMultipleCollisions;
    U64                    TxDeferred;
    U64                    TxLateCollision;
    U64                    TxMaxCollisions;
    U64                    TxCarrierLost;
    U64                    TxExcessiveDeferrals;
} I2O_LAN_802_3_HIST_STATS_SCALAR, *PI2O_LAN_802_3_HIST_STATS_SCALAR;


/* LAN Group 0280h - Optional Supported 802.3 Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_8023HSS_StatisticsSupported =  0
} I2O_LAN_OPT_802_3_HSTATS_SUPP_FIELDIDX;

typedef struct _I2O_LAN_OPT_802_3_HIST_STATS_SUPP_SCALAR {
    U64                    StatisticsSupported;
} I2O_LAN_OPT_802_3_HIST_STATS_SUPP_SCALAR, *PI2O_LAN_OPT_802_3_HIST_STATS_SUPP_SCALAR;


/* LAN Group 0281h - Optional 802.3 Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_O8023HS_RxOverrun                 =  0,
    FieldIdx_O8023HS_TxUnderrun                =  1,
    FieldIdx_O8023HS_TxHeartbeatFailure        =  2
} I2O_LAN_OPT_802_3_HSTATS_FIELDIDX;

typedef struct _I2O_LAN_OPT_802_3_HIST_STATS_SCALAR {
    U64                    RxOverrun;
    U64                    TxUnderrun;
    U64                    TxHeartbeatFailure;
} I2O_LAN_OPT_802_3_HIST_STATS_SCALAR, *PI2O_LAN_OPT_802_3_HIST_STATS_SCALAR;


/*-----------------------------------*/
/* - 802.5 Media specific statistics */

/* LastRingStatus bit map defines */

#define I2O_LAN_802_5_RSTAT_RING_RECOVERY      0x0000000000000020
#define I2O_LAN_802_5_RSTAT_SINGLE_STATION     0x0000000000000040
#define I2O_LAN_802_5_RSTAT_COUNTER_OVERFLOW   0x0000000000000080
#define I2O_LAN_802_5_RSTAT_REMOVE_RECEIVED    0x0000000000000100
#define I2O_LAN_802_5_RSTAT_AUTO_REMOVAL_ERROR 0x0000000000000400
#define I2O_LAN_802_5_RSTAT_LOBE_WIRE_FAULT    0x0000000000000800
#define I2O_LAN_802_5_RSTAT_TRANSMIT_BEACON    0x0000000000001000
#define I2O_LAN_802_5_RSTAT_SOFT_ERROR         0x0000000000002000
#define I2O_LAN_802_5_RSTAT_HARD_ERROR         0x0000000000004000
#define I2O_LAN_802_5_RSTAT_SIGNAL_LOSS        0x0000000000008000


/* LAN Group 0300h - Required 802.5 Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_8025HS_LineErrors                =  0,
    FieldIdx_8025HS_LostFrames                =  1,
    FieldIdx_8025HS_ACError                   =  2,
    FieldIdx_8025HS_TxAbortDelimter           =  3,
    FieldIdx_8025HS_BurstErrors               =  4,
    FieldIdx_8025HS_FrameCopiedErrors         =  5,
    FieldIdx_8025HS_FrequencyErrors           =  6,
    FieldIdx_8025HS_InternalError             =  7,
    FieldIdx_8025HS_LastRingStatus            =  8,
    FieldIdx_8025HS_TokenError                =  9,
    FieldIdx_8025HS_UpstreamNodeAddress       = 10,
    FieldIdx_8025HS_LastRingID                = 11,
    FieldIdx_8025HS_LastBeaconType            = 12
} I2O_LAN_802_5_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_802_5_HIST_STATS_SCALAR {
    U64                    LineErrors;
    U64                    LostFrames;
    U64                    ACError;
    U64                    TxAbortDelimter;
    U64                    BurstErrors;
    U64                    FrameCopiedErrors;
    U64                    FrequencyErrors;
    U64                    InternalError;
    U64                    LastRingStatus;
    U64                    TokenError;
    U64                    UpstreamNodeAddress;
    U64                    LastRingID;
    U64                    LastBeaconType;
} I2O_LAN_802_5_HIST_STATS_SCALAR, *PI2O_LAN_802_5_HIST_STATS_SCALAR;


/* LAN Group 0380h - Optional Supported 802.5 Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_O8025HSS_StatisticsSupported =  0
} I2O_LAN_OPT_802_5_HSTATS_SUPP_FIELDIDX;

typedef struct _I2O_LAN_OPT_802_5_HIST_STATS_SUPP_SCALAR {
    U64                    StatisticsSupported;
} I2O_LAN_OPT_802_5_HIST_STATS_SUPP_SCALAR, *PI2O_LAN_OPT_802_5_HIST_STATS_SUPP_SCALAR;


/* LAN Group 0381h - Optional 802.5 Historical Statistics Parameter Group */

/* typedef struct _I2O_LAN_OPT_802_5_HIST_STATS_SCALAR { */
    /* None defined at this time */
/* } I2O_LAN_OPT_802_5_HIST_STATS_SCALAR, *PI2O_LAN_OPT_802_5_HIST_STATS_SCALAR; */


/*-----------------------------------*/
/* - FDDI Media specific statistics */

/* ConfigurationState defines */

#define I2O_LAN_FDDI_CONFIG_ISOLATED           0x0000000000000000
#define I2O_LAN_FDDI_CONFIG_LOCAL_A            0x0000000000000001
#define I2O_LAN_FDDI_CONFIG_LOCAL_B            0x0000000000000002
#define I2O_LAN_FDDI_CONFIG_LOCAL_AB           0x0000000000000003
#define I2O_LAN_FDDI_CONFIG_LOCAL_S            0x0000000000000004
#define I2O_LAN_FDDI_CONFIG_WRAP_A             0x0000000000000005
#define I2O_LAN_FDDI_CONFIG_WRAP_B             0x0000000000000006
#define I2O_LAN_FDDI_CONFIG_WRAP_AB            0x0000000000000007
#define I2O_LAN_FDDI_CONFIG_WRAP_S             0x0000000000000008
#define I2O_LAN_FDDI_CONFIG_C_WRAP_A           0x0000000000000009
#define I2O_LAN_FDDI_CONFIG_C_WRAP_B           0x000000000000000A
#define I2O_LAN_FDDI_CONFIG_C_WRAP_S           0x000000000000000B
#define I2O_LAN_FDDI_CONFIG_THROUGH            0x000000000000000C

/* Ring Management State (RingMgmtState) defines */

#define I2O_LAN_FDDI_RMGMT_ISOLATED            0x0000000000000000
#define I2O_LAN_FDDI_RMGMT_NON_OP              0x0000000000000001
#define I2O_LAN_FDDI_RMGMT_RING_OP             0x0000000000000002
#define I2O_LAN_FDDI_RMGMT_DETECT              0x0000000000000003
#define I2O_LAN_FDDI_RMGMT_NON_OP_DUP          0x0000000000000004
#define I2O_LAN_FDDI_RMGMT_RING_OP_DUP         0x0000000000000005
#define I2O_LAN_FDDI_RMGMT_DIRECTED            0x0000000000000006
#define I2O_LAN_FDDI_RMGMT_TRACE               0x0000000000000007

/* LConnection State defines */

#define I2O_LAN_FDDI_LCSTATE_OFF               0x0000000000000000
#define I2O_LAN_FDDI_LCSTATE_BREAK             0x0000000000000001
#define I2O_LAN_FDDI_LCSTATE_TRACE             0x0000000000000002
#define I2O_LAN_FDDI_LCSTATE_CONNECT           0x0000000000000003
#define I2O_LAN_FDDI_LCSTATE_NEXT              0x0000000000000004
#define I2O_LAN_FDDI_LCSTATE_SIGNAL            0x0000000000000005
#define I2O_LAN_FDDI_LCSTATE_JOIN              0x0000000000000006
#define I2O_LAN_FDDI_LCSTATE_VERIFY            0x0000000000000007
#define I2O_LAN_FDDI_LCSTATE_ACTIVE            0x0000000000000008
#define I2O_LAN_FDDI_LCSTATE_MAINTENANCE       0x0000000000000009


/* LAN Group 0400h - Required FDDI Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_FDDIHS_ConfigurationState        =  0,
    FieldIdx_FDDIHS_UpstreamNode              =  1,
    FieldIdx_FDDIHS_DownStreamNode            =  2,
    FieldIdx_FDDIHS_FrameErrors               =  3,
    FieldIdx_FDDIHS_FramesLost                =  4,
    FieldIdx_FDDIHS_RingMgmtState             =  5,
    FieldIdx_FDDIHS_LCTFailures               =  6,
    FieldIdx_FDDIHS_LEMRejects                =  7,
    FieldIdx_FDDIHS_LEMCount                  =  8,
    FieldIdx_FDDIHS_LConnectionState          =  9
} I2O_LAN_FDDI_HIST_STATS_FIELDIDX;

typedef struct _I2O_LAN_FDDI_HIST_STATS_SCALAR {
    U64                    ConfigurationState;
    U64                    UpstreamNode;
    U64                    DownStreamNode;
    U64                    FrameErrors;
    U64                    FramesLost;
    U64                    RingMgmtState;
    U64                    LCTFailures;
    U64                    LEMRejects;
    U64                    LEMCount;
    U64                    LConnectionState;
} I2O_LAN_FDDI_HIST_STATS_SCALAR, *PI2O_LAN_FDDI_HIST_STATS_SCALAR;


/* LAN Group 0480h - Optional Supported FDDI Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_OFDDIHSS_StatisticsSupported  =  0
} I2O_LAN_OPT_FDDI_HSTATS_SUPP_FIELDIDX;

typedef struct _I2O_LAN_OPT_FDDI_HIST_STATS_SUPP_SCALAR {
    U64                    StatisticsSupported;
} I2O_LAN_OPT_FDDI_HIST_STATS_SUPP_SCALAR, *PI2O_LAN_OPT_FDDI_HIST_STATS_SUPP_SCALAR;


/* LAN Group 0481h - Optional FDDI Historical Statistics Parameter Group */

/*typedef struct _I2O_LAN_OPT_FDDI_HIST_STATS_SCALAR { */
    /* None defined at this time */
/*} I2O_LAN_OPT_FDDI_HIST_STATS_SCALAR, *PI2O_LAN_OPT_FDDI_HIST_STATS_SCALAR; */



/*-----------------------------------*/
/* - Fibre Channel Media specific statistics */

/* LAN Group 0500h - Required Fibre Channel Historical Statistics Parameter Group */

/* typedef struct _I2O_LAN_FC_HIST_STATS_SCALAR { */
    /* None defined at this time */
/* } I2O_LAN_FC_HIST_STATS_SCALAR, *PI2O_LAN_FC_HIST_STATS_SCALAR; */


/* LAN Group 0580h - Optional Supported Fibre Channel Historical Statistics Parameter Group */

typedef enum {
    FieldIdx_OFCHSS_StatisticsSupported    =  0
} I2O_LAN_OPT_FC_HSTATS_SUPP_FIELDIDX;

typedef struct _I2O_LAN_OPT_FC_HIST_STATS_SUPP_SCALAR {
    U64                    StatisticsSupported;
} I2O_LAN_OPT_FC_HIST_STATS_SUPP_SCALAR, *PI2O_LAN_OPT_FC_HIST_STATS_SUPP_SCALAR;


/* LAN Group 0581h - Optional Fibre Channel Historical Statistics Parameter Group */

/* typedef struct _I2O_LAN_OPT_FC_HIST_STATS_SCALAR { */
    /* None defined at this time */
/* } I2O_LAN_OPT_FC_HIST_STATS_SCALAR, *PI2O_LAN_OPT_FC_HIST_STATS_SCALAR; */


PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif     /* I2O_LAN_HDR */



