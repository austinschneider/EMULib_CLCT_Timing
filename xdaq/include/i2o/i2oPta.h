/* i2oPta.h - I2O Peer Transport Agent definitions */

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


#ifndef __INC_I2OPTA_H
#define __INC_I2OPTA_H

#include "i2o/shared/i2otypes.h"
#include "i2o/shared/i2opeer.h"
#include "i2o/i2oPeerLib.h"
#include "i2o/i2oIopLib.h"

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

/* Message function codes */

#define     I2O_PTA_SERVICE_ESTABLISH                   0x91

/* Generic PTA object ID */

typedef U32 PEER_OBJ_ID;

/*
 * IRTOS interface functions for use by PTA
 */

typedef void (*IRTOS_SVC_CREATE_COMP_FUNC) (PEER_OBJ_ID*,
                                            I2O_EVENT_QUEUE_ID,
                                            I2O_EVENT_PRI,
                                            I2O_EVENT_HANDLER,
                                            I2O_OBJ_CONTEXT,
                                            I2O_STATUS,
                                            I2O_STATUS*);

/*
 * PTA interface functions for use by the IRTOS
 */

typedef void (*PTA_GENERIC_SERVICE_DELETE_FUNC) (PEER_OBJ_ID, U32*);

typedef void (*PTA_DATA_SEND_CREATE_FUNC) (I2O_OWNER_ID,
					   I2O_TID,
					   I2O_UNIT_ID,
					   I2O_IOP_ID,
					   I2O_TID,
					   I2O_EVENT_QUEUE_ID, 
					   I2O_EVENT_PRI,
					   I2O_TID,
					   I2O_PEER_QOS, 
					   I2O_PEER_XFR_ATTR,
					   I2O_BUS_ID,
					   I2O_BUS_SPACE,
					   I2O_PEER_SVC_CREATE_FLAGS,
					   I2O_OBJ_CONTEXT,
					   I2O_EVENT_HANDLER,
					   I2O_PEER_DATA_SEND_CREATE*,
					   I2O_SIZE,
					   U32*);

typedef void (*PTA_DATA_SEND_FUNC) (PEER_OBJ_ID,
                                    I2O_SG_ELEMENT*,
                                    I2O_COUNT,
                                    I2O_OBJ_CONTEXT,
                                    I2O_EVENT_HANDLER,
				    I2O_PEER_XFR_FLAGS,
                                    U32*);

typedef void (*PTA_DATA_SEND_CANCEL_FUNC) (PEER_OBJ_ID,
                                           I2O_PEER_CANCEL_MODE,
                                           I2O_OBJ_CONTEXT,
                                           U32*) ;

typedef PTA_GENERIC_SERVICE_DELETE_FUNC PTA_DATA_SEND_DELETE_FUNC;


typedef PEER_OBJ_ID (*PTA_DATA_REC_CREATE_FUNC) (I2O_OWNER_ID,
						 I2O_TID,
						 I2O_EVENT_QUEUE_ID,
						 I2O_EVENT_PRI,
						 I2O_OBJ_CONTEXT,
						 I2O_EVENT_HANDLER,
						 U32*);

typedef void (*PTA_DATA_REC_FREE_FUNC) (PEER_OBJ_ID,
					I2O_TRL_CONTROL_WORD,
					I2O_PEER_REC_RET_LIST*,
					U32*);

typedef PTA_GENERIC_SERVICE_DELETE_FUNC PTA_DATA_REC_DELETE_FUNC;


typedef void (*PTA_DATA_MOVE_CREATE_FUNC) (I2O_OWNER_ID,
					   I2O_TID,
					   I2O_UNIT_ID,
					   I2O_IOP_ID,
					   I2O_TID,
					   I2O_PEER_XFR_ATTR,
					   I2O_BUS_ID,
					   I2O_BUS_SPACE,
					   I2O_PEER_XFR_ATTR,
					   I2O_BUS_ID,
					   I2O_BUS_SPACE,
					   I2O_PEER_SVC_CREATE_FLAGS,
					   I2O_EVENT_QUEUE_ID,
					   I2O_EVENT_PRI,
					   I2O_OBJ_CONTEXT,
					   I2O_EVENT_HANDLER,
					   I2O_PEER_DATA_MOVE_CREATE*,
					   I2O_SIZE,
					   U32*);

typedef void (*PTA_DATA_MOVE_FUNC) (PEER_OBJ_ID,
				    I2O_SG_ELEMENT*,
				    I2O_SG_ELEMENT*,
				    I2O_PEER_XFR_FLAGS,
				    I2O_OBJ_CONTEXT,
				    I2O_EVENT_HANDLER,
				    U32*);

typedef void (*PTA_DATA_MOVE_CANCEL_FUNC) (PEER_OBJ_ID,
					   I2O_PEER_CANCEL_MODE,
					   I2O_OBJ_CONTEXT,
					   U32*);

typedef PTA_GENERIC_SERVICE_DELETE_FUNC PTA_DATA_MOVE_DELETE_FUNC;

typedef void (*PTA_DATA_REDIR_CREATE_FUNC) (I2O_OWNER_ID,
					    I2O_TID,
					    I2O_UNIT_ID,
					    I2O_IOP_ID,
					    I2O_TID,
					    I2O_SIZE,
					    I2O_SIZE,
					    I2O_SIZE,
					    I2O_PEER_REDIR_CREATE*,
					    I2O_SIZE,
					    I2O_TID,
					    I2O_MEM_ACCESS_ATTR,
					    I2O_BUS_ID,
					    I2O_BUS_SPACE,
					    I2O_MEM_ACCESS_ATTR,
					    I2O_BUS_ID,
					    I2O_BUS_SPACE,
					    I2O_PEER_SVC_CREATE_FLAGS,
					    I2O_EVENT_QUEUE_ID,
					    I2O_EVENT_PRI,
					    I2O_OBJ_CONTEXT,
					    I2O_EVENT_HANDLER,
					    U32*);

typedef void (*PTA_DATA_REDIR_FUNC) (PEER_OBJ_ID,
				     I2O_PEER_REDIR_LIST*,
				     I2O_COUNT,
				     I2O_ADDR32,
				     I2O_COUNT,
				     I2O_PEER_REDIR_FLAGS,
				     I2O_OBJ_CONTEXT,
				     I2O_EVENT_HANDLER,
				     U32*);

typedef void (*PTA_DATA_REDIR_CANCEL_FUNC) (PEER_OBJ_ID,
					    I2O_PEER_CANCEL_MODE,
					    I2O_OBJ_CONTEXT,
					    U32*);

typedef PTA_GENERIC_SERVICE_DELETE_FUNC PTA_DATA_REDIR_DELETE_FUNC;

typedef void (*PTA_REMOTE_MEM_ALLOC_FUNC) (I2O_OWNER_ID,
					   I2O_TID,
					   I2O_UNIT_ID,
					   I2O_IOP_ID,
					   I2O_COUNT,
					   I2O_MEM_CACHE_ATTR,
					   I2O_MEM_ACCESS_ATTR,
					   I2O_BUS_ID,
					   I2O_SIZE,
					   I2O_SIZE,
					   I2O_PEER_REMALLOC_ADDR_BUFFER*,
					   I2O_SIZE,
					   PEER_OBJ_ID*,
					   I2O_EVENT_QUEUE_ID,
					   I2O_EVENT_PRI,
					   I2O_OBJ_CONTEXT,
					   I2O_EVENT_HANDLER,
					   U32*);

typedef PTA_GENERIC_SERVICE_DELETE_FUNC PTA_REMOTE_MEM_FREE_FUNC;

typedef void (*PTA_MAP_SVC_TO_TRANSPORT_FUNC) (I2O_OWNER_ID,
					       PEER_OBJ_ID,
					       I2O_TID*,
					       U32*);

/*
 * Message interface between IRTOS and Peer Transport Agent.
 */

/* ptaSvcEstablish Function Message Frame structure. */

typedef struct _I2O_PTA_SVC_EST_MESSAGE {
    I2O_MESSAGE_FRAME        StdMessageFrame;
    I2O_TRANSACTION_CONTEXT  TransactionContext;
    I2O_SGE_SIMPLE_ELEMENT   SGL;
}  I2O_PTA_SVC_EST_MESSAGE, *PI2O_PTA_SVC_EST_MESSAGE;

/* ptaSvcEstablish input buffer structure */

typedef struct _I2O_PTA_SVC_EST_INDATA
{
    U32                                 structureVersion;

    PTA_DATA_SEND_CREATE_FUNC           ptaDataSendCreate;
    PTA_DATA_SEND_FUNC                  ptaDataSend;
    PTA_DATA_SEND_CANCEL_FUNC           ptaDataSendCancel;
    PTA_DATA_SEND_DELETE_FUNC           ptaDataSendDelete;

    PTA_DATA_REC_CREATE_FUNC            ptaDataRecCreate;
    PTA_DATA_REC_FREE_FUNC              ptaDataRecFree;
    PTA_DATA_REC_DELETE_FUNC            ptaDataRecDelete;

    PTA_DATA_MOVE_CREATE_FUNC           ptaDataMoveCreate;
    PTA_DATA_MOVE_FUNC                  ptaDataMove;
    PTA_DATA_MOVE_CANCEL_FUNC           ptaDataMoveCancel;
    PTA_DATA_MOVE_DELETE_FUNC           ptaDataMoveDelete;

    PTA_DATA_REDIR_CREATE_FUNC          ptaDataRedirCreate;
    PTA_DATA_REDIR_FUNC                 ptaDataRedir;
    PTA_DATA_REDIR_CANCEL_FUNC          ptaDataRedirCancel;
    PTA_DATA_REDIR_DELETE_FUNC          ptaDataRedirDelete;

    PTA_REMOTE_MEM_ALLOC_FUNC           ptaRemoteMemAlloc;
    PTA_REMOTE_MEM_FREE_FUNC            ptaRemoteMemFree;

    PTA_MAP_SVC_TO_TRANSPORT_FUNC       ptaMapSvcToTransport;

} I2O_PTA_SVC_EST_INDATA, *PI2O_PTA_SVC_EST_INDATA;

/* Version info for input buffer */

#define I2O_PTA_SVC_EST_INDATA_VERSION 0x1

/* ptaSvcEstablish output buffer structure */

typedef struct _I2O_PTA_SVC_EST_OUTDATA
{
    U32                                 structureVersion;
    IRTOS_SVC_CREATE_COMP_FUNC          irtosSvcCreateComplete;
} I2O_PTA_SVC_EST_OUTDATA, *PI2O_PTA_SVC_EST_OUTDATA;

/* Version info for output buffer */

#define I2O_PTA_SVC_EST_OUTDATA_VERSION 0x1

/*
 * PTA Service Data Units interface Peer Transport Agents.
 * NOTE: these SDUs are passed "as data" via Peer Transports, not via
 * standard I2O messaging.
 */

/* PTA version for use in Peer Transport service establishment */

#define I2O_PTA_VERSION 0x1

/* Service message header */

typedef struct _I2O_PTA_DATA_SEND_SERVICE_HDR
{
    U32         serviceType;
    U16         sourceUnit;
    U16         sourceIop;
    U16         sourceTid;
    U16         destUnit;
    U16         destIop;
    U16         destTid;

} I2O_PTA_DATA_DELIVER_SERVICE_HDR, *PPTA_DATA_DELIVER_SERVICE_HDR;

/* PTA Service message service types */

#define I2O_PTA_SERVICE_TYPE_DATA_DELIVER          0

typedef struct _I2O_PTA_SERVICE_HDR_DATA_DELIVERY
    {
    U32 serviceType;
    U16 sourceUnit;
    U16 sourceIop;
    U16 sourceTid;
    U16 destUnit;
    U16 destIop;
    U16 destTid;
} I2O_PTA_SERVICE_HDR_DATA_DELIVERY;

PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif /* __INC_I2OPTA_H  */
