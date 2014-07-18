/* i2oDdmLib.h - i2o DDM support library header file */

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

#ifndef __INCi2oDdmLibh
#define __INCi2oDdmLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "i2o/i2o.h"
#include "i2o/shared/i2otypes.h"
#include "i2o/i2oEvtQLib.h"
#include "i2o/i2oObjLib.h"
#include "i2o/i2oThreadLib.h"
#include "i2o/i2oErrorLib.h"
#include "i2o/i2oAdapterLib.h"
#include "i2o/shared/i2omsg.h"

/* privates */
typedef struct 	i2oDdm* 	I2O_DDM_ID;	     /* DDM object */
typedef struct 	i2oDev* 	I2O_DEV_ID;	     /* DEV object */
typedef struct 	i2oDispatchId* 	I2O_DISPATCH_TBL_ID; /* Dispatch object */

typedef U16  I2O_ORG_ID;
typedef U16  I2O_MOD_ID;

typedef struct
    {
    I2O_ORG_ID  orgId;
    I2O_MOD_ID  modId;
    } I2O_DDM_TAG;


/* I2O DDM message codes */
#define I2O_DDM_ADAPTER_ATTACH      0xE0
#define I2O_DDM_ADAPTER_RECONFIG    0xE1
#define I2O_DDM_ADAPTER_RELEASE     0xE2
#define I2O_DDM_ADAPTER_RESUME      0xE3
#define I2O_DDM_ADAPTER_SUSPEND     0xE4
#define I2O_DDM_DEVICE_ATTACH       0xE5
#define I2O_DDM_DEVICE_RELEASE      0xE6
#define I2O_DDM_DEVICE_RESET        0xE7
#define I2O_DDM_DEVICE_RESUME       0xE8
#define I2O_DDM_DEVICE_SUSPEND      0xE9
#define I2O_DDM_SELF_RESET          0xEA
#define I2O_DDM_SELF_RESUME         0xEB
#define I2O_DDM_SELF_SUSPEND        0xEC
#define I2O_DDM_SYSTEM_CHANGE       0xED
#define I2O_DDM_SYSTEM_ENABLE       0xEE
#define I2O_DDM_SYSTEM_HALT         0xEF
#define I2O_DDM_ATTACH_COMPLETE	    0xF0

#define I2O_USER_TID_UNCLAIMED	0xFFF

#define I2O_ANL_SZ		8

#define I2O_DDM_ATTACH_DEVICE_RESERVE_SZ	(32 - I2O_TID_SZ)
#define I2O_DDM_ATTACH_COMPLETE_RESERVE_SZ	(32 - I2O_ANL_SZ)

typedef U32           I2O_TID;
typedef U32           I2O_DEV_FLAGS;
typedef I2O_CLASS_ID  I2O_DEV_CLASS;
typedef U32           I2O_DEV_SUBCLASS;
typedef U8            I2O_DEV_IDENTITY_TAG;
typedef U32           I2O_DEV_EVENT_CAPABILITIES;
typedef U8            I2O_DEV_BIOS_INFO;
typedef U32           I2O_DEV_CHANGE_INDICATOR;

/* I2O adapter attach message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_ADAPTER_ID              AdapterId;
} I2O_DDM_ADAPTER_ATTACH_MESSAGE, *PI2O_DDM_ADAPTER_ATTACH_MESSAGE;

/* I2O adapter reconfig message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_ADAPTER_ID              AdapterId;
} I2O_DDM_ADAPTER_RECONFIG_MESSAGE, *PI2O_DDM_ADAPTER_RECONFIG_MESSAGE;

/* I2O adapter release message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_ADAPTER_ID              AdapterId;
    U8                          Reserved[3];
    U8                          OperationFlags;
} I2O_DDM_ADAPTER_RELEASE_MESSAGE, *PI2O_DDM_ADAPTER_RELEASE_MESSAGE;

/* I2O adapter resume message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_ADAPTER_ID              AdapterId;
} I2O_DDM_ADAPTER_RESUME_MESSAGE, *PI2O_DDM_ADAPTER_RESUME_MESSAGE;

/* I2O adapter suspend message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    I2O_ADAPTER_ID              AdapterId;
} I2O_DDM_ADAPTER_SUSPEND_MESSAGE, *PI2O_DDM_ADAPTER_SUSPEND_MESSAGE;

/* I2O device attach message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         DeviceTID:I2O_TID_SZ;
    U32                         Reserved:I2O_DDM_ATTACH_DEVICE_RESERVE_SZ;
    I2O_CLASS_ID                ClassIdentifier;
    U32                         DeviceFlags;
} I2O_DDM_DEVICE_ATTACH_MESSAGE, *PI2O_DDM_DEVICE_ATTACH_MESSAGE;

/* I2O device release message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         DeviceTID:I2O_TID_SZ;
    U32                         Reserved:I2O_DDM_ATTACH_DEVICE_RESERVE_SZ;
} I2O_DDM_DEVICE_RELEASE_MESSAGE, *PI2O_DDM_DEVICE_RELEASE_MESSAGE;

/* I2O device reset message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         DeviceTID:I2O_TID_SZ;
    U32                         Reserved:I2O_DDM_ATTACH_DEVICE_RESERVE_SZ;
} I2O_DDM_DEVICE_RESET_MESSAGE, *PI2O_DDM_DEVICE_RESET_MESSAGE;

/* I2O device resume message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         DeviceTID:I2O_TID_SZ;
    U32                         Reserved:I2O_DDM_ATTACH_DEVICE_RESERVE_SZ;
} I2O_DDM_DEVICE_RESUME_MESSAGE, *PI2O_DDM_DEVICE_RESUME_MESSAGE;

/* I2O device suspend message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32                         DeviceTID:I2O_TID_SZ;
    U32                         Reserved:I2O_DDM_ATTACH_DEVICE_RESERVE_SZ;
} I2O_DDM_DEVICE_SUSPEND_MESSAGE, *PI2O_DDM_DEVICE_SUSPEND_MESSAGE;

/* I2O self reset message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SELF_RESET_MESSAGE, *PI2O_DDM_SELF_RESET_MESSAGE;

/* I2O self resume message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SELF_RESUME_MESSAGE, *PI2O_DDM_SELF_RESUME_MESSAGE;

/* I2O self suspend message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SELF_SUSPEND_MESSAGE, *PI2O_DDM_SELF_SUSPEND_MESSAGE;

/* I2O system change message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SYSTEM_CHANGE_MESSAGE, *PI2O_DDM_SYSTEM_CHANGE_MESSAGE;

/* I2O system enable message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SYSTEM_ENABLE_MESSAGE, *PI2O_DDM_SYSTEM_ENABLE_MESSAGE;

/* I2O system halt message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
} I2O_DDM_SYSTEM_HALT_MESSAGE, *PI2O_DDM_SYSTEM_HALT_MESSAGE;

/* I2O attach complete message structure */
typedef struct
    {
    I2O_MESSAGE_FRAME           StdMessageFrame;
    I2O_TRANSACTION_CONTEXT     TransactionContext;
    U32				Level:I2O_ANL_SZ;
    U32				Reserved:I2O_DDM_ATTACH_COMPLETE_RESERVE_SZ;
} I2O_DDM_ATTACH_COMPLETE_MESSAGE, *PI2O_DDM_ATTACH_COMPLETE_MESSAGE;

typedef struct
    {
    I2O_EVENT_HANDLER	func;
    U8		msgCode;
    U8		pri;
    } I2O_FUNC_ENTRY;

typedef struct 
    {
    I2O_TID                        LocalTID;
    I2O_DEV_FLAGS                  Flags;
    I2O_DEV_CLASS                  Class;
    I2O_DEV_SUBCLASS               Subclass;
    I2O_TID                        UserTID;
    I2O_TID                        ParentTID;
    I2O_DEV_IDENTITY_TAG           IdentityTag[I2O_IDENTITY_TAG_SZ];
    I2O_DEV_EVENT_CAPABILITIES     EventCapabilities;
    I2O_DEV_BIOS_INFO              BiosInfo;
    I2O_DEV_CHANGE_INDICATOR       ChangeIndicator;
    } I2O_LCT_INFO;


/* function declarations */
extern I2O_DDM_ID	i2oDdmCreate (I2O_DDM_TAG               ddmTag, 
                                      int                       i2oVersion,
                                      I2O_LCT_INFO*             pLctInfo,
                                      I2O_OBJ_CONTEXT           devContext,
                                      I2O_THREAD_OPTIONS        tOptions,
                                      I2O_SIZE                  tStackSize,
                                      I2O_FUNC_ENTRY*           pFuncArray,
                                      I2O_COUNT                 numFuncs,
                                      I2O_STATUS*               pStatus);

extern I2O_DEV_ID	i2oDdmDevGet (I2O_DDM_ID                ddmId,
                                      I2O_STATUS*               pStatus);

extern void  		i2oDdmMpbStore (I2O_DDM_ID              ddmId,
                                        I2O_SG_ELEMENT*	        pMpb,
                                        I2O_STATUS*             pStatus);

extern void  		i2oDdmTidRelease (I2O_DDM_ID            ddlTid,
                                          I2O_TID               tid,
                                          I2O_STATUS*           pStatus);

extern I2O_DEV_ID	i2oDevCreate (I2O_OWNER_ID              ownerId,
                                      I2O_OBJ_CONTEXT           devContext,
                                      I2O_EVENT_QUEUE_ID            evtQId, 
                                      I2O_DISPATCH_TBL_ID       dispatchId,
                                      I2O_LCT_INFO*             pLctInfo,
                                      I2O_STATUS*               pStatus);

extern I2O_TID		i2oDevTidGet   (I2O_DEV_ID              devId,
                                        I2O_STATUS*             pStatus);

extern I2O_EVENT_QUEUE_ID   i2oDevEventQGet (I2O_DEV_ID             devId,
                                         I2O_STATUS*            pStatus);

extern I2O_DISPATCH_TBL_ID i2oDevDispatchTblGet (I2O_DEV_ID         devId,
                                             I2O_STATUS*        pStatus);

extern void		i2oDevLctInfoGet (I2O_DEV_ID            devId,
                                          I2O_LCT_INFO*         pLctInfo,
                                          I2O_STATUS*           pStatus);

extern void		i2oDevLctFlagsSet(I2O_DEV_ID            devId,
                                          I2O_DEV_FLAGS         devFlags,
                                          I2O_DEV_FLAGS         devMask,
                                          I2O_STATUS*           pStatus);

extern void		i2oDevUserTidSet (I2O_DEV_ID		devId,
                                          I2O_TID		userTid,
                                          I2O_DEV_FLAGS         claimFlags,
                                          I2O_STATUS*		pStatus);

extern I2O_DISPATCH_TBL_ID  i2oDispatchTblCreate 
                                  (I2O_OWNER_ID                 ownerId,
                                   I2O_FUNC_ENTRY*              pFuncArray,
                                   I2O_COUNT                    numFuncs,
                                   I2O_STATUS*                  pStatus);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCi2oDdmLibh */
