/* i2oPeerLib.h - I2O Peer to Peer API */

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


#ifndef __INCi2oPeerLibh
#define __INCi2oPeerLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "i2o/i2oDdmLib.h"
#include "i2o/i2oObjLib.h"
#include "i2o/i2oPageLib.h"
#include "i2o/i2oIopLib.h"
#include "i2o/shared/i2otypes.h"
#include "i2o/shared/i2omsg.h"
#include "i2o/shared/i2outil.h"

typedef struct i2oPeerObj *     I2O_PEER_OBJ_ID;

/* service create flags */

typedef U32 I2O_PEER_SVC_CREATE_FLAGS;

#define I2O_PEER_SVC_USE_TRANSPORT  0x00000001
#define I2O_PEER_SVC_USE_QOS_EXACT  0x00000002
#define I2O_PEER_SVC_USE_QOS_MIN    0x00000004
#define I2O_PEER_SVC_USE_XFR_ATTRIB 0x00000008

/* data redirect flags */

typedef U32 I2O_PEER_REDIR_FLAGS;

#define     I2O_PEER_DATA_REDIR_INDICATE 0x40000000
#define     I2O_PEER_DATA_REDIR_CALLBACK 0x80000000

/* requested quality of service */

typedef enum
    {
    I2O_PEER_QOS_DATAGRAM = 1,
    I2O_PEER_QOS_GUARANTEED = 2
    } I2O_PEER_QOS;

/* cancel modes */

typedef enum
    {
    I2O_PEER_CANCEL_MATCHING = 1,
    I2O_PEER_CANCEL_ALL = 2,
    I2O_PEER_CANCEL_PT = 3
    } I2O_PEER_CANCEL_MODE;

/* peer transfer memory access attributes */

typedef enum
    {
    I2O_PEER_XFR_ACCESS_SYSTEM_LOCAL = 0,
    I2O_PEER_XFR_ACCESS_SYSTEM_NONLOCAL,
    I2O_PEER_XFR_ACCESS_BUS_SPECIFIC,
    I2O_PEER_XFR_ACCESS_ALL_ADAPTERS_LOCAL,
    I2O_PEER_XFR_ACCESS_ALL_ADAPTERS_NONLOCAL,
    I2O_PEER_XFR_ACCESS_LOCAL_ADAPTERS,
    I2O_PEER_XFR_ACCESS_PRIVATE
    } I2O_PEER_XFR_ATTR;

/* peer transfer flags */

typedef U32 I2O_PEER_XFR_FLAGS;

#define I2O_PEER_XFR_DIR_REVERSE        0x00000001
#define I2O_PEER_XFR_NO_EVENT           0x00000002
#define I2O_PEER_XFR_SRC_SGL_CONTEXT_64 0x00000004
#define I2O_PEER_XFR_DST_SGL_CONTEXT_64 0x00000008

/* data send create buffer */

typedef struct _I2O_PEER_DATA_SEND_CREATE
    {
    I2O_SIZE        dataSendCreateSize;
    U32             dataSendCreateVersion;
    I2O_PEER_OBJ_ID dataSendId;
    I2O_SIZE        maxDataSize;
} I2O_PEER_DATA_SEND_CREATE;

/* data move create buffer */

typedef struct _I2O_PEER_DATA_MOVE_CREATE
    {
    I2O_SIZE        dataMoveCreateSize;
    U32             dataMoveCreateVersion;
    I2O_PEER_OBJ_ID dataMoveId;
} I2O_PEER_DATA_MOVE_CREATE;

/* remote alloc flags */

typedef U32 I2O_PEER_REMALLOC_ADDR_FLAGS;

#define I2O_PEER_REMALLOC_ADDR_64_BIT   0x00000001

/* remote alloc address buffer */

typedef struct _I2O_PEER_REMALLOC_ADDR_BUFFER
    {
    I2O_SIZE                     remAddrBufferSize;
    U32                          remAddrBufferVersion;
    I2O_PEER_REMALLOC_ADDR_FLAGS addrFlags;
    I2O_SG_ELEMENT               sgl;
} I2O_PEER_REMALLOC_ADDR_BUFFER;

/* received SGL flags */

typedef U32 I2O_PEER_REC_SGL_FLAGS;

#define I2O_PEER_REC_SGL_CONTEXT_64 0x00000001

/* data receive element */

typedef struct _I2O_PEER_REC_ELEMENT
    {
    I2O_SG_ELEMENT *       pRecData;
    I2O_PEER_REC_SGL_FLAGS sglFlags;
    I2O_UNIT_ID            sourceUnit;
    I2O_IOP_ID             sourceIop;
    I2O_TID                sourceTid;
    U32                    reserved;
    } I2O_PEER_REC_ELEMENT;

/* transaction return list */

typedef I2O_TRANSACTION_CONTEXT* I2O_PEER_REC_RET_LIST;

/* Redirect Buffer flags */

typedef U32 I2O_PEER_REDIR_BFR_FLAGS;

#define I2O_PEER_REDIR_BFR_64_BIT 0x00000001
#define I2O_PEER_REDIR_BFR_PROXY  0x00000002

/* redirect create structure */

typedef struct _I2O_PEER_REDIR_CREATE
    {
    I2O_SIZE                 redirCreateSize;
    U32                      redirCreateVersion;
    I2O_PEER_OBJ_ID          dataRedirId;
    I2O_SIZE                 redirBufferSize;
    I2O_PEER_REDIR_BFR_FLAGS redirBufferFlags;
    I2O_ADDR32               redirBufferLow;
    I2O_ADDR32               redirBufferHigh;
    } I2O_PEER_REDIR_CREATE;

/* redirect list structure */

typedef struct _I2O_PEER_REDIR_LIST
    {
    I2O_SIZE redirSegmentOffset;
    I2O_SIZE redirSegmentSize;
    } I2O_PEER_REDIR_LIST;

/* function prototypes */

/* data send service */

extern void i2oPeerDataSendCreate
    (
    I2O_OWNER_ID                ownerId,
    I2O_TID                     sourceTid,
    I2O_UNIT_ID                 destUnit,
    I2O_IOP_ID                  destIop,
    I2O_TID                     destTid,
    I2O_EVENT_QUEUE_ID          sendEvtQId,
    I2O_EVENT_PRI               sendEvtPri,
    I2O_TID                     reqTransport,
    I2O_PEER_QOS                reqQos,
    I2O_PEER_XFR_ATTR           sourceAccessAttr,
    I2O_BUS_ID                  sourceBusId,
    I2O_BUS_SPACE               sourceBusSpace,
    I2O_PEER_SVC_CREATE_FLAGS   sendCreateFlags,
    I2O_OBJ_CONTEXT             sendCreateContext,
    I2O_EVENT_HANDLER           sendCreateEvtHandler,
    I2O_PEER_DATA_SEND_CREATE * pDataSendCreateBuffer,
    I2O_SIZE                    sendCreateBufferSize,
    I2O_STATUS *                pStatus
    );

extern void i2oPeerDataSend
    (
    I2O_PEER_OBJ_ID     dataSendId,
    I2O_SG_ELEMENT *    pListPtr,
    I2O_COUNT           listTransCount,
    I2O_OBJ_CONTEXT     sendContext,
    I2O_EVENT_HANDLER   sendEvtHandler,
    I2O_PEER_XFR_FLAGS  xferFlags,
    I2O_STATUS *        pStatus
    );

extern void i2oPeerDataSendCancel
    (
    I2O_PEER_OBJ_ID      dataSendId,
    I2O_PEER_CANCEL_MODE cancelMode,
    I2O_OBJ_CONTEXT      sendContext,
    I2O_STATUS *         pStatus
    );

/* data receive service */

extern I2O_PEER_OBJ_ID i2oPeerDataRecCreate
    (
    I2O_OWNER_ID       ownerId,
    I2O_TID            recTid,
    I2O_EVENT_QUEUE_ID recEvtQId,
    I2O_EVENT_PRI      recEvtPri,
    I2O_OBJ_CONTEXT    recContext,
    I2O_EVENT_HANDLER  recEvtHandler,
    I2O_STATUS *       pStatus
    );

extern void i2oPeerDataRecFree
    (
    I2O_PEER_OBJ_ID         dataRecId,
    I2O_TRL_CONTROL_WORD    recRetWord,
    I2O_PEER_REC_RET_LIST * pRecRetList,
    I2O_STATUS *            pStatus
    );

/* data move service */

extern void i2oPeerDataMoveCreate
    (
    I2O_OWNER_ID                ownerId,
    I2O_TID                     sourceTid,
    I2O_UNIT_ID                 destUnit,
    I2O_IOP_ID                  destIop,
    I2O_TID                     reqTransport,
    I2O_PEER_XFR_ATTR           localAccessAttr,
    I2O_BUS_ID                  localBusId,
    I2O_BUS_SPACE               localBusSpace,
    I2O_PEER_XFR_ATTR           remoteAccessAttr,
    I2O_BUS_ID                  remoteBusId,
    I2O_BUS_SPACE               remoteBusSpace,
    I2O_PEER_SVC_CREATE_FLAGS   moveCreateFlags,
    I2O_EVENT_QUEUE_ID          moveEvtQId,
    I2O_EVENT_PRI               moveEvtPri,
    I2O_OBJ_CONTEXT             moveCreateContext,
    I2O_EVENT_HANDLER           moveCreateEvtHandler,
    I2O_PEER_DATA_MOVE_CREATE * pDataMoveCreateBuffer,
    I2O_SIZE                    moveCreateBufferSize,
    I2O_STATUS *                pStatus
    );

extern void i2oPeerDataMove
    (
    I2O_PEER_OBJ_ID     dataMoveId,
    I2O_SG_ELEMENT *    pLocalList,
    I2O_SG_ELEMENT *    pRemoteList,
    I2O_PEER_XFR_FLAGS  xferFlags,
    I2O_OBJ_CONTEXT     moveContext,
    I2O_EVENT_HANDLER   moveEvtHandler,
    I2O_STATUS *        pStatus
    );

extern void i2oPeerDataMoveCancel
    (
    I2O_PEER_OBJ_ID      dataMoveId,
    I2O_PEER_CANCEL_MODE cancelMode,
    I2O_OBJ_CONTEXT      moveContext,
    I2O_STATUS *         pStatus
    );

/* data redirect service */

extern void i2oPeerDataRedirCreate
    (
    I2O_OWNER_ID              ownerId,
    I2O_TID                   sourceTid,
    I2O_UNIT_ID               destUnit,
    I2O_IOP_ID                destIop,
    I2O_TID                   destTid,
    I2O_SIZE                  redirReqSize,
    I2O_SIZE                  redirMinReqSize,
    I2O_SIZE                  alignment,
    I2O_PEER_REDIR_CREATE *   pRedirCreateBuffer,
    I2O_SIZE                  redirCreateBufferSize,
    I2O_TID                   reqTransport,
    I2O_MEM_ACCESS_ATTR       redirAccessAttr,
    I2O_BUS_ID                redirBusId,
    I2O_BUS_SPACE             redirBusSpace,
    I2O_MEM_ACCESS_ATTR       redirProxyAccessAttr,
    I2O_BUS_ID                redirProxyBusId,
    I2O_BUS_SPACE             redirProxyBusSpace,
    I2O_PEER_SVC_CREATE_FLAGS redirCreateFlags,
    I2O_EVENT_QUEUE_ID        redirEvtQId,
    I2O_EVENT_PRI             redirEvtPri,
    I2O_OBJ_CONTEXT           redirCreateContext,
    I2O_EVENT_HANDLER         redirEvtHandler,
    I2O_STATUS *              pStatus
    );

extern void i2oPeerDataRedir
    (
    I2O_PEER_OBJ_ID       dataRedirId,
    I2O_PEER_REDIR_LIST * pRedirList,
    I2O_COUNT             redirCount,
    I2O_ADDR32            userData,
    I2O_COUNT             userDataCount,
    I2O_PEER_REDIR_FLAGS  redirFlags,
    I2O_OBJ_CONTEXT       redirContext,
    I2O_EVENT_HANDLER     redirEvtHandler,
    I2O_STATUS *          pStatus
    );

extern void i2oPeerDataRedirCancel
    (
    I2O_PEER_OBJ_ID      dataRedirId,
    I2O_PEER_CANCEL_MODE cancelMode,
    I2O_OBJ_CONTEXT      redirContext,
    I2O_STATUS *         pStatus
    );

/* remote memory allocation service */

extern void i2oPeerRemoteMemAlloc
    (
    I2O_OWNER_ID                    ownerId,
    I2O_TID                         sourceTid,
    I2O_UNIT_ID                     remUnit,
    I2O_IOP_ID                      remIop,
    I2O_COUNT                       totalMem,
    I2O_MEM_CACHE_ATTR              cacheAttr,
    I2O_MEM_ACCESS_ATTR             accessAttr,
    I2O_BUS_ID                      remBusId,
    I2O_SIZE                        alignment,
    I2O_SIZE                        bucketSize,
    I2O_PEER_REMALLOC_ADDR_BUFFER * pRetAddrBuffer,
    I2O_SIZE                        retAddrBufferSize,
    I2O_PEER_OBJ_ID *               pRemAllocId,
    I2O_EVENT_QUEUE_ID              remAllocEvtQId,
    I2O_EVENT_PRI                   remAllocEvtPri,
    I2O_OBJ_CONTEXT                 remAllocContext,
    I2O_EVENT_HANDLER               remAllocEvtHandler,
    I2O_STATUS *                    pStatus
    );

/* miscellaneous */

extern void i2oPeerMapSvcToTransport
    (
    I2O_OWNER_ID    ownerId,
    I2O_PEER_OBJ_ID serviceObject,
    I2O_TID *       pTransportTid,
    I2O_STATUS *    pStatus
    );

extern void i2oSvcExtEventRegister
    (
    I2O_UTIL_EVENT_REGISTER_MESSAGE * pUtilEventRegMsg,
    U32                               serviceId,
    I2O_STATUS *                      pStatus
    );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCi2oPeerLibh */
