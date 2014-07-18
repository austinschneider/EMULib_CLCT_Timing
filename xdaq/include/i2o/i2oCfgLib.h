/* i2oConfigLib.h - DDM configuration support library header file */

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

#ifndef __INCi2oConfigLibh
#define __INCi2oConfigLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "i2o/shared/i2omsg.h"
#include "i2o/i2oObjLib.h"
#include "i2o/i2oDdmLib.h"

/* Field set/get, row add/delete function */

typedef U8 (*I2O_PARAMS_FIELD_ACCESS_FUNC) ();

/* Group clear function */

typedef U8 (*I2O_PARAMS_CLEAR_FUNC)
    (
    I2O_OBJ_CONTEXT     context,   /* User-defined context */
    U16                 groupNum,  /* Group number */
    I2O_MESSAGE_FRAME * pMsg       /* Config request message frame */
    );

/* Get keys function */

typedef U8 (*I2O_PARAMS_GET_KEYS_FUNC)
    (
    I2O_OBJ_CONTEXT     context,          /* User-defined context */
    U16                 groupNum,         /* Group number */
    I2O_ADDR32          pPrevKey,         /* Previous key value */
    I2O_COUNT           resultBufLen,     /* Length of result buffer */
    I2O_ADDR32          pResultBuf,       /* Result buffer */
    U16 *               pNumKeysReturned, /* Number of keys returned */
    U16 *               pNumKeysTotal,    /* Total number of keys in group */
    I2O_MESSAGE_FRAME * pMsg              /* Config request message frame */
    );

/* I2O field info structure */

typedef struct _I2O_PARAMS_FIELD_DEF
    {
    I2O_PARAMS_FIELD_ACCESS_FUNC addSetFunc;  /* write field or add a row */
    I2O_PARAMS_FIELD_ACCESS_FUNC delGetFunc;  /* read field or delete a row */
    I2O_COUNT                    size;        /* Size in bytes of this field */
    U32                          constant;    /* Const associated with field */
} I2O_PARAMS_FIELD_DEF;

/* I2O group info structure */

typedef struct _I2O_PARAMS_GROUP_DEF
    {
    U16                      groupNumber;   /* Group ID */
    U16                      fieldCount;    /* Number of fields in group */
    I2O_PARAMS_FIELD_DEF*    pFieldArray;   /* Array of field definitions */
    I2O_PARAMS_GET_KEYS_FUNC getKeysFunc;   /* Func returning keys of group */
    I2O_PARAMS_CLEAR_FUNC    clearFunc;     /* Func to delete all rows */
} I2O_PARAMS_GROUP_DEF;

#define I2O_PARAMS_FIELD_COUNT(X) (sizeof(X) / sizeof(I2O_PARAMS_FIELD_DEF))
#define I2O_PARAMS_GROUP_COUNT(X) (sizeof(X) / sizeof(I2O_PARAMS_GROUP_DEF))

/* Event client info structure */

typedef struct _I2O_EVENT_CLIENT_INFO
{
    I2O_TID               TargetAddress;
    I2O_TID               InitiatorAddress;
    U64                   InitiatorContext;
    U32                   Flags;
    U64                   TransactionContext;
    U32                   EventMask;
} I2O_EVENT_CLIENT_INFO;

/* Event client info flags bits */

#define I2O_EVENT_CLIENT_FLAGS_CONTEXT_64  0x00000002

/* Event client list structure */

typedef struct _I2O_EVENT_CLIENT_LIST
{
    I2O_COUNT             clientCount;
    U32                   reserved;
    I2O_EVENT_CLIENT_INFO clientList[1];
} I2O_EVENT_CLIENT_LIST;

/* function prototypes */

extern void i2oCfgParamMsgReply (I2O_DEV_ID              devId,
				 I2O_OBJ_CONTEXT         context,
				 I2O_MESSAGE_FRAME *     pMsg,
				 I2O_COUNT               numGroups,
				 I2O_PARAMS_GROUP_DEF *  pGroupArray,
				 I2O_EVENT_CLIENT_LIST * pEventClientList,
				 I2O_STATUS *            pStatus);

extern void i2oCfgDialogMsgReply (I2O_DEV_ID              devId,
				  I2O_OBJ_CONTEXT         context,
				  I2O_COUNT               setNum,
				  I2O_MESSAGE_FRAME *     pMsg,
				  I2O_COUNT               numGroups,
				  I2O_PARAMS_GROUP_DEF *  pGroupArray,
				  I2O_EVENT_CLIENT_LIST * pEventClientList,
				  I2O_STATUS *            pStatus);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCi2oConfigLibh */
