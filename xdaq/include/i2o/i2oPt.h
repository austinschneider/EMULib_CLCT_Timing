/* i2oPt.h - I2O Peer Transport definitions */

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

#ifndef __INC_I2OPT_H
#define __INC_I2OPT_H

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

#include "i2o/shared/i2otypes.h"
#include "i2o/shared/i2opeer.h"
#include "i2o/i2oPeerLib.h"

/* Message function codes */

#define     I2O_PT_SERVICE_ESTABLISH                    0x92

/* Peer transport ID */

typedef I2O_OBJ_CONTEXT I2O_PEER_TP_ID;

/* Peer transport connection status */

typedef U32 I2O_PT_CON_STATUS;

#define I2O_PT_CON_STATUS_CONNECTED    TRUE
#define I2O_PT_CON_STATUS_DISCONNECTED FALSE

/* Peer transport Event Notification definitions */

#define I2O_PT_EVENT_DATA_LINK_DOWN                     0x000000001
#define I2O_PT_EVENT_DATA_LINK_UP                       0x000000002

/* Peer Transport Event Data definition */

typedef struct _I2O_PT_EVENT_DATA
{
    BF                UnitID:I2O_UNIT_ID_SZ;
    BF                IopID:I2O_IOP_ID_SZ;
    BF                reserved:I2O_RESERVED_4BITS;
} I2O_PT_EVENT_DATA, *PI2O_PT_EVENT_DATA;

/* Peer Transport memory transfer capabilities definitions. */

/* Number of source memory types.
 * Actual source memory defs are enumerated in I2O_PEER_XFR_ATTR in i2oPeerLib.h
 */

#define I2O_PEER_MEM_SOURCE_TYPES 7

/* Bit definitions for transfer destination memory */

#define I2O_PEER_XFR_CAP_PRIVATE               (1 << 0)
#define I2O_PEER_XFR_CAP_LOCAL_ADAPTERS        (1 << 1)
#define I2O_PEER_XFR_CAP_ALL_ADAPTERS_NONLOCAL (1 << 2)
#define I2O_PEER_XFR_CAP_ALL_ADAPTERS_LOCAL    (1 << 3)
#define I2O_PEER_XFR_CAP_BUS_SPECIFIC          (1 << 4)
#define I2O_PEER_XFR_CAP_SYSTEM_NONLOCAL       (1 << 5)
#define I2O_PEER_XFR_CAP_SYSTEM_LOCAL          (1 << 6)

/* Peer Transport memory transfer capabilities structure */

typedef struct _I2O_PEER_MEM_XFR_CAP
    {
    U32 sendXfrCap[I2O_PEER_MEM_SOURCE_TYPES];
    U32 moveXfrCap[I2O_PEER_MEM_SOURCE_TYPES];
    } I2O_PEER_MEM_XFR_CAP;

/* memory allocation operation identification */

typedef enum
    {
    I2O_PEER_MEM_ALLOC = 1,
    I2O_PEER_MEM_FREE  = 2
    } I2O_PEER_MEM_OPERATION;

/* memory allocation services identification */

typedef enum
    {
    I2O_PEER_MEM_REDIR_ALLOC = 1,
    I2O_PEER_MEM_REM_ALLOC   = 2
    } I2O_PEER_MEM_SVC_TYPE;

/*
 * Peer Transport Agent interface functions for use by Peer Transports
 */

typedef void (*PTA_STATUS_CHANGE_FUNC) (I2O_PEER_TP_ID,
                                        I2O_OBJ_CONTEXT,
                                        I2O_OBJ_CONTEXT,
                                        I2O_UNIT_ID,
                                        I2O_IOP_ID,
                                        U32,
                                        I2O_SIZE,
                                        I2O_SIZE,
					I2O_PEER_MEM_XFR_CAP*,
                                        I2O_OBJ_CONTEXT*,
                                        I2O_OBJ_CONTEXT*,
                                        I2O_PT_CON_STATUS,
                                        U32*);

typedef void (*PTA_SEND_CREATE_COMP_FUNC) (I2O_OBJ_CONTEXT,
                                           I2O_OBJ_CONTEXT,
                                           I2O_STATUS);

typedef void (*PTA_SEND_COMP_FUNC) (I2O_OBJ_CONTEXT,
                                    I2O_OBJ_CONTEXT,
                                    I2O_STATUS);


typedef I2O_SG_ELEMENT * (*PTA_RECEIVE_FUNC) (I2O_OBJ_CONTEXT,
					      I2O_OBJ_CONTEXT,
                                              I2O_SG_ELEMENT*,
					      I2O_PEER_REC_SGL_FLAGS,
                                              U32*);

typedef void (*PTA_MOVE_CREATE_COMP_FUNC) (I2O_OBJ_CONTEXT,
                                           I2O_OBJ_CONTEXT,
                                           I2O_STATUS);

typedef void (*PTA_MOVE_COMP_FUNC) (I2O_OBJ_CONTEXT,
                                    I2O_OBJ_CONTEXT,
                                    I2O_STATUS);

typedef void (*PTA_REDIR_CREATE_COMP_FUNC) (I2O_OBJ_CONTEXT,
					    I2O_OBJ_CONTEXT,
					    I2O_ADDR32,
					    I2O_ADDR32,
					    I2O_SIZE,
					    I2O_PEER_REDIR_BFR_FLAGS,
					    I2O_OBJ_CONTEXT,
					    I2O_STATUS);

typedef void (*PTA_REDIR_COMP_FUNC) (I2O_OBJ_CONTEXT,
				     I2O_OBJ_CONTEXT,
				     I2O_STATUS);

typedef void (*PTA_REM_MEM_ALLOC_COMP_FUNC) (I2O_OBJ_CONTEXT,
					     I2O_OBJ_CONTEXT,
					     I2O_OBJ_CONTEXT,
					     I2O_STATUS);

typedef void (*PTA_REM_MEM_UPDATE_FUNC) (I2O_SIZE,
					 I2O_PEER_MEM_OPERATION,
					 I2O_PEER_MEM_SVC_TYPE,
					 U32*);

/*
 * Peer Transport functions for use by Peer Transport Agent
 */

typedef void (*PTP_SEND_CREATE_FUNC) (I2O_OBJ_CONTEXT,
				      I2O_OBJ_CONTEXT,
				      I2O_PEER_XFR_ATTR,
				      I2O_BUS_ID,
				      I2O_BUS_SPACE,
				      U32*);

typedef void (*PTP_SEND_FUNC) (I2O_OBJ_CONTEXT,
			       I2O_SG_ELEMENT*,
			       I2O_COUNT,
			       I2O_PEER_XFR_FLAGS,
			       I2O_OBJ_CONTEXT,
			       U32*);

typedef void (*PTP_SEND_CANCEL_FUNC) (I2O_OBJ_CONTEXT,
				      I2O_PEER_CANCEL_MODE,
				      I2O_OBJ_CONTEXT,
				      I2O_STATUS*);

typedef void (*PTP_SEND_DELETE_FUNC) (I2O_OBJ_CONTEXT,
                                      U32*);

typedef void (*PTP_RECEIVE_COMP_FUNC) (I2O_OBJ_CONTEXT,
				       I2O_OBJ_CONTEXT,
				       I2O_TRL_CONTROL_WORD,
				       I2O_PEER_REC_RET_LIST*);

typedef void (*PTP_MOVE_CREATE_FUNC) (I2O_OBJ_CONTEXT,
				      I2O_OBJ_CONTEXT,
				      I2O_PEER_XFR_ATTR,
				      I2O_BUS_ID,
				      I2O_BUS_SPACE,
				      I2O_PEER_XFR_ATTR,
				      I2O_BUS_ID,
				      I2O_BUS_SPACE,
				      I2O_STATUS*);

typedef void (*PTP_MOVE_FUNC) (I2O_OBJ_CONTEXT,
			       I2O_SG_ELEMENT*,
			       I2O_SG_ELEMENT*,
			       I2O_PEER_XFR_FLAGS,
			       I2O_OBJ_CONTEXT,
			       I2O_STATUS*);

typedef void (*PTP_MOVE_CANCEL_FUNC) (I2O_OBJ_CONTEXT,
				      I2O_PEER_CANCEL_MODE,
				      I2O_OBJ_CONTEXT,
				      I2O_STATUS*);

typedef void (*PTP_MOVE_DELETE_FUNC) (I2O_OBJ_CONTEXT,
                                      I2O_STATUS*);

typedef void (*PTP_REDIR_CREATE_FUNC) (I2O_OBJ_CONTEXT,
				       I2O_SIZE,
				       I2O_SIZE,
				       I2O_MEM_ACCESS_ATTR,
				       I2O_BUS_ID,
				       I2O_BUS_SPACE,
				       I2O_MEM_ACCESS_ATTR,
				       I2O_BUS_ID,
				       I2O_BUS_SPACE,
				       I2O_SIZE,
				       I2O_ADDR32,
				       I2O_SIZE,
				       I2O_OBJ_CONTEXT,
				       I2O_STATUS*);

typedef void (*PTP_REDIR_FUNC) (I2O_OBJ_CONTEXT,
				I2O_PEER_REDIR_LIST*,
				I2O_COUNT,
				I2O_ADDR32,
				I2O_COUNT,
				I2O_PEER_REDIR_FLAGS,
				I2O_OBJ_CONTEXT,
				I2O_OBJ_CONTEXT,
				I2O_STATUS*);

typedef void (*PTP_REDIR_CANCEL_FUNC) (I2O_OBJ_CONTEXT,
				       I2O_PEER_CANCEL_MODE,
				       I2O_OBJ_CONTEXT,
				       I2O_STATUS*);

typedef void (*PTP_REDIR_DELETE_FUNC) (I2O_OBJ_CONTEXT,
				       I2O_OBJ_CONTEXT,
				       I2O_STATUS*);

typedef void (*PTP_REM_MEM_ALLOC_FUNC) (I2O_OBJ_CONTEXT,
					I2O_SIZE,
					I2O_SIZE,
					I2O_MEM_CACHE_ATTR,
					I2O_MEM_ACCESS_ATTR,
					I2O_BUS_ID,
					I2O_SIZE,
					I2O_ADDR32,
					I2O_COUNT,
					I2O_OBJ_CONTEXT,
					I2O_STATUS*);

typedef void (*PTP_REM_MEM_FREE_FUNC) (I2O_OBJ_CONTEXT,
				       I2O_OBJ_CONTEXT,
				       I2O_STATUS*);

/*
 * Message interface between Peer Transport Agent and Peer Transport
 */

/* ptSvcEstablish Function Message Frame structure */

typedef struct _I2O_PT_SVC_EST_MESSAGE {
    I2O_MESSAGE_FRAME        StdMessageFrame;
    I2O_TRANSACTION_CONTEXT  TransactionContext;
    I2O_SGE_SIMPLE_ELEMENT   SGL;
} I2O_PT_SVC_EST_MESSAGE, *PI2O_PT_SVC_EST_MESSAGE;

/* ptSvcEstablish input buffer structure */

typedef struct  _I2O_PT_SVC_EST_INDATA
{
    U32                                 structureVersion;
    U32                                 ptPriority;
    I2O_PEER_QOS                        ptQos;
    PTP_SEND_CREATE_FUNC                ptSendCreateFunc;
    PTP_SEND_FUNC                       ptSendFunc;
    PTP_SEND_CANCEL_FUNC                ptSendCancelFunc;
    PTP_SEND_DELETE_FUNC                ptSendDeleteFunc;
    PTP_RECEIVE_COMP_FUNC               ptReceiveCompFunc;
    PTP_MOVE_CREATE_FUNC                ptMoveCreateFunc;
    PTP_MOVE_FUNC                       ptMoveFunc;
    PTP_MOVE_CANCEL_FUNC                ptMoveCancelFunc;
    PTP_MOVE_DELETE_FUNC                ptMoveDeleteFunc;
    PTP_REDIR_CREATE_FUNC               ptRedirCreateFunc;
    PTP_REDIR_FUNC                      ptRedirFunc;
    PTP_REDIR_CANCEL_FUNC               ptRedirCancelFunc;
    PTP_REDIR_DELETE_FUNC               ptRedirDeleteFunc;
    PTP_REM_MEM_ALLOC_FUNC              ptRemMemAllocFunc;
    PTP_REM_MEM_FREE_FUNC               ptRemMemFreeFunc;

} I2O_PT_SVC_EST_INDATA, *PI2O_PT_SVC_EST_INDATA;

/* Version info for input buffer */

#define I2O_PT_SVC_EST_INDATA_VERSION 0x1

/* ptSvcEstablish output buffer structure */

typedef struct  _I2O_PT_SVC_EST_OUTDATA
{
    U32                                 structureVersion;
    U32                                 ptaVersion;
    I2O_PEER_TP_ID                      ptId;
    PTA_STATUS_CHANGE_FUNC              ptaStatusChangeFunc;
    PTA_SEND_CREATE_COMP_FUNC           ptaSendCreateCompFunc;
    PTA_SEND_COMP_FUNC                  ptaSendCompFunc;
    PTA_RECEIVE_FUNC                    ptaReceiveFunc;
    PTA_MOVE_CREATE_COMP_FUNC           ptaMoveCreateCompFunc;
    PTA_MOVE_COMP_FUNC                  ptaMoveCompFunc;
    PTA_REDIR_CREATE_COMP_FUNC          ptaRedirCreateCompFunc;
    PTA_REDIR_COMP_FUNC                 ptaRedirCompFunc;
    PTA_REM_MEM_ALLOC_COMP_FUNC         ptaRemMemAllocCompFunc;
    PTA_REM_MEM_UPDATE_FUNC             ptaRemMemUpdateFunc;

} I2O_PT_SVC_EST_OUTDATA, *PI2O_PT_SVC_EST_OUTDATA;

/* Version info for input buffer */

#define I2O_PT_SVC_EST_OUTDATA_VERSION 0x1


PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif /* __INC_I2OPT_H  */

