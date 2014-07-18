/* i2oPtPci.h - I2O Logical PCI Peer Transport definitions */

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

#ifndef __INC_I2OPTPCI_H_
#define __INC_I2OPTPCI_H_

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

#define     I2O_PCI_PT_CONNECT                      0x84

#define     I2O_PCI_PT_POST_RECEIVE                 0x86
#define     I2O_PCI_PT_REMOTE_ALLOCATE              0x88

#define     I2O_PCI_PT_REMOTE_FREE                  0x89
#define     I2O_PCI_PT_REDIRECT                     0x8a
#define     I2O_PCI_PT_REDIRECT_ALLOCATE            0x8b
#define     I2O_PCI_PT_REDIRECT_DEALLOCATE          0x8c

/* Request Status codes for Peer Transport reply messages */

#define PT_SUCCESS                                  0
#define PT_TRANSACTION_ERROR                        1

/* Detailed Status Codes     */

#define     PT_DETAIL_STATUS_SUCCESS                  0x0000
#define     PT_DETAIL_STATUS_INVALID_ACCESS_ATTR      0x0021
#define     PT_DETAIL_STATUS_INVALID_BUS_ID           0x0022
#define     PT_DETAIL_STATUS_INVALID_ALIGNMENT        0x0023
#define     PT_DETAIL_STATUS_INVALID_HANDLE           0x0024
#define     PT_DETAIL_STATUS_INVALID_OFFSET           0x0025
#define     PT_DETAIL_STATUS_INVALID_SIZE             0x0026
#define     PT_DETAIL_STATUS_DMA_ERROR                0x0027
#define     PT_DETAIL_STATUS_PEER_SVC_LOST            0x0028
#define     PT_DETAIL_STATUS_INSUFFICIENT_MEMORY      0x0029
#define     PT_DETAIL_STATUS_INVALID_SGL              0x002a
#define     PT_DETAIL_STATUS_UNKNOWN_ERROR            0x002b
#define     PT_DETAIL_STATUS_INVALID_CACHE_ATTR       0x002c
#define     PT_DETAIL_STATUS_INVALID_REQUEST_SIZE     0x002d


/* ptConnect reply ReqStatus values */

#define     I2O_PT_CONNECT_STATUS_ALLOWED 0x00
#define     I2O_PT_CONNECT_STATUS_ERROR   0x01

/* ptConnect reply DetailedStatusCode values */

#define I2O_PT_CONNECT_DETAILED_ERROR_OTHER            0x0001
#define I2O_PT_CONNECT_DETAILED_ERROR_CON_DENIED       0x0002
#define I2O_PT_CONNECT_DETAILED_ERROR_INCOMPATIBLE_PT  0x0003

enum PLP_RCV_SIG_METHOD_TYPES {RCV_SIG_I2O_MESSAGE=1};

typedef struct _I2O_PLP_PT_CONNECT_MESSAGE {

    I2O_MESSAGE_FRAME           StdMessageFrame;
    U32                         TransactionContext;
    U16                         PtaSvcMsgVersion;
    U16                         Reserved;
    U32                         ReqMaxData;

} I2O_PLP_PT_CONNECT_MESSAGE, *PI2O_PLP_PT_CONNECT_MESSAGE;


typedef struct _I2O_PLP_PT_CONNECT_REPLY {

    I2O_SINGLE_REPLY_MESSAGE_FRAME  SingleReplyMessageFrame;
    U32                             MaxData;

} I2O_PLP_PT_CONNECT_REPLY, *PI2O_PLP_PT_CONNECT_REPLY;



#define RECEIVE_BUFFER_POST_SGL_OFFSET  3 << 4  /* # words - shift to upper nibble */

typedef struct _I2O_PCI_PT_RECEIVE_BUFFER_POST_MESSAGE {
    I2O_MESSAGE_FRAME                   StdMessageFrame;
    I2O_SGE_SIMPLE_CONTEXT_ELEMENT      SGL;
} I2O_PCI_PT_RECEIVE_BUFFER_POST_MESSAGE, *PI2O_PCI_PT_RECEIVE_BUFFER_POST_MESSAGE;


typedef struct _I2O_PCI_PT_TRL_SIZE {
   U32                         Size:8;
   U32                         Rsvd:24;
} I2O_PCI_PT_TRL_SIZE, *PI2O_PCI_PT_TRL_SIZE;


typedef struct _PCI_PT_TRL {
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_PCI_PT_TRL_SIZE         RsvdSize;
    U32                         Reserved;
    U32                         BufferSize[1];
} PCI_PT_TRL, *PPCI_PT_TRL;


#define RCV_BUFFER_POST_REPLY_TRL_OFFSET 5 << 4  /* offset of TRL in 32 bit words - shifted to upper nibble */

typedef struct _I2O_PCI_PT_RECEIVE_BUFFER_POST_REPLY {
    I2O_MESSAGE_FRAME                   StdMessageFrame;
    I2O_TRL_CONTROL_WORD                TrlControlWord;
    U16                                 DetailedStatusCode;
    U8                                  reserved;
    U8                                  ReqStatus;
    PCI_PT_TRL                          TRL;
} I2O_PCI_PT_RECEIVE_BUFFER_POST_REPLY, *PI2O_PCI_PT_RECEIVE_BUFFER_POST_REPLY;



/* Logical PCI Peer Transport Redirect Messages */

#define REDIR_ALLOC_SGL_OFFSET      10 << 4      /* offset of SGL in 32 bit words - shifted to upper nibble */

typedef struct _I2O_PLP_REDIR_ALLOC_MESSAGE {

    I2O_MESSAGE_FRAME                   StdMessageFrame;
    I2O_TRANSACTION_CONTEXT             TransactionContext;
    I2O_SIZE                            redirReqSize;
    I2O_SIZE                            redirMinReqSize;
    I2O_MEM_ACCESS_ATTR                 redirAccessAttr;
    I2O_BUS_ID                          redirBusId;
    I2O_BUS_SPACE                       redirAddrSpace;
    I2O_SIZE                            redirAlignment;
    I2O_SGE_SIMPLE_ELEMENT              SGL;
} I2O_PLP_REDIR_ALLOC_MESSAGE, *PI2O_PLP_REDIR_ALLOC_MESSAGE;


typedef struct _I2O_PLP_REDIR_ALLOC_REPLY {

    I2O_SINGLE_REPLY_MESSAGE_FRAME  SingleReplyMessageFrame;
    U32                             redirBufferFlags;
    U32                             redirBufferLow;
    U32                             redirBufferHigh;
    I2O_OBJ_CONTEXT                 redirHandle;
    I2O_SIZE                        redirAllocdSize;

} I2O_PLP_REDIR_ALLOC_REPLY, *PI2O_PLP_REDIR_ALLOC_REPLY;


#define REDIR_SGL_OFFSET            7 << 4

typedef struct _I2O_PLP_REDIR_MESSAGE {

    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         redirFlags;
    I2O_OBJ_CONTEXT             redirHandle;
    U32                         redirCount;
    I2O_SG_ELEMENT              redirSGL;
} I2O_PLP_REDIR_MESSAGE, *PI2O_PLP_REDIR_MESSAGE;


/* Redirect Message Operation Flags - these are defined in i2oPeerLib.h */


typedef struct _REDIR_ARRAY
{
    I2O_SIZE        redirSegmentOffset;
    I2O_SIZE        redirSegmentSize;
} REDIR_ARRAY, *PREDIR_ARRAY;


typedef struct _I2O_PLP_REDIR_DEALLOC_MESSAGE {

    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_OBJ_CONTEXT             redirHandle;
} I2O_PLP_REDIR_DEALLOC_MESSAGE, *PI2O_PLP_REDIR_DEALLOC_MESSAGE;


/* Peer Data Services Remote Memory Allocate Messages */

#define REM_ALLOC_SGL_OFFSET        10  <<  4       /* Offset in 32 bit words */

typedef struct _I2O_PT_REM_MEM_ALLOC_REQUEST {

    I2O_MESSAGE_FRAME                   StdMessageFrame;
    I2O_TRANSACTION_CONTEXT             TransactionContext;
    U32                                 totalMem;
    U32                                 bucketSize;
    U32                                 alignment;
    U32                                 remAccessAttr;
    U32                                 remCacheAttr;
    U32                                 remBusId;
    I2O_SGE_SIMPLE_ELEMENT              storeSGL;

} I2O_PT_REM_MEM_ALLOC_REQUEST, *PI2O_PT_REM_MEM_ALLOC_REQUEST;


typedef struct _I2O_PT_REM_MEM_ALLOCATE_REPLY {

    I2O_SINGLE_REPLY_MESSAGE_FRAME  SingleReplyMessageFrame;
    I2O_OBJ_CONTEXT                 remMemHandle;

} I2O_PT_REM_MEM_ALLOC_REPLY, *PI2O_PT_REM_MEM_ALLOC_REPLY;


typedef struct _I2O_PT_REM_MEM_FREE_REQUEST {

    I2O_MESSAGE_FRAME                   StdMessageFrame;
    I2O_TRANSACTION_CONTEXT             TransactionContext;
    I2O_OBJ_CONTEXT                     remMemHandle;

} I2O_PT_REM_MEM_FREE_REQUEST, *PI2O_PT_REM_MEM_FREE_REQUEST;

PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif /* __INC_I2OPTPCI_H_  */
