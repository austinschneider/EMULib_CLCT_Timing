/* i2oErrorLib.h - error library header file */

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

#ifndef __INCi2oErrorLibh
#define __INCi2oErrorLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* i2o error/status typedefs */

typedef	enum		
    {
    I2O_STS_OK			 	= 0,
    I2O_STS_INVALID_OBJ_ID		= 1,
    I2O_STS_INVALID_OWNER_ID		= 2,
    I2O_STS_NOT_ISR_CALLABLE		= 3,
    I2O_STS_TIMER_IN_USE		= 4,
    I2O_STS_TIMER_EVT_IN_USE		= 5,
    I2O_STS_TIMER_INACTIVE		= 6,
    I2O_STS_INVALID_OBJ_NAME		= 7,
    I2O_STS_NOT_IMPLEMENTED		= 8,
    I2O_STS_ALLOCATION_FAILED		= 9,
    I2O_STS_MAX_EVENTS_OUTSTANDING	= 10,
    I2O_STS_INVALID_ISR_FUNC		= 11,
    I2O_STS_LIB_NOT_INSTALLED		= 12,
    I2O_STS_UNKNOWN_ERROR		= 13,
    I2O_STS_FUNC_NOT_IMPLEMENTED	= 14,
    I2O_STS_FRAME_ALREADY_FREE		= 15,
    I2O_STS_FRAME_ALLOCATION_FAILED	= 16,
    I2O_STS_FRAME_POST_ERROR		= 17,
    I2O_STS_FRAME_INVALID		= 18,
    I2O_STS_FRAME_DISPATCH_ERROR	= 19,
    I2O_STS_DMA_UNSUPPORTED_BUS		= 20,
    I2O_STS_DMA_INVALID			= 21,
    I2O_STS_DMA_ERROR			= 22,
    I2O_STS_DMA_CHAIN_ERROR		= 23,
    I2O_STS_TOO_MANY_ENTRIES		= 24,
    I2O_STS_TID_ERROR			= 25,
    I2O_STS_ARG_NOT_IMPLEMENTED		= 26,
    I2O_STS_DMA_PAGE_SIZE_ERROR		= 27,
    I2O_STS_ARG_ERROR			= 28,
    I2O_STS_INVALID_USER_FUNC		= 29,
    I2O_STS_INVALID_BLOCK		= 30,
    I2O_STS_SEM_INIT_ERROR		= 31,
    I2O_STS_SEM_TAKE_ERROR		= 32,
    I2O_STS_SEM_GIVE_ERROR		= 33,
    I2O_STS_PIPE_SEND_ERROR		= 34,
    I2O_STS_PIPE_RECEIVE_ERROR		= 35,
    I2O_STS_DMA_FULL  			= 36,
    I2O_STS_INVALID_EVENT_PRI		= 37,
    I2O_STS_INVALID_ERR_ACT		= 38,
    I2O_STS_INSUFFICIENT_MEMORY		= 39,
    I2O_STS_INVALID_PAGE_ARRAY		= 40,
    I2O_STS_INVALID_CONFIG_MESSAGE      = 41,
    I2O_STS_DMA_NO_CANCEL		= 42,
    I2O_STS_DMA_RESUME_FAILED		= 43,
    I2O_STS_DMA_OBJECT_SUSPENDED	= 44,
    I2O_STS_MPB_SIZE_ERROR              = 45,
    I2O_STS_NO_NVS			= 46,
    I2O_STS_NVS_CREATE_ERROR		= 47,
    I2O_STS_NVS_OPEN_ERROR		= 48,
    I2O_STS_NVS_CLOSE_ERROR		= 49,
    I2O_STS_NVS_DELETE_ERROR		= 50,
    I2O_STS_NVS_WRITE_ERROR		= 51,
    I2O_STS_BBU_NOT_PRESENT		= 52,
    I2O_STS_INSUFFICIENT_NVRAM		= 53,
    I2O_STS_NVRAM_ACCESS_ERROR		= 54,
    I2O_STS_INVALID_EVENT_HANDLER	= 55,
    I2O_STS_OBJ_DESTROY_ERROR		= 56,
    I2O_STS_UNAVAILABLE			= 57,
    I2O_STS_TIMEOUT			= 58,
    I2O_STS_TIMER_DESTROY_ERROR         = 59,
    I2O_STS_INTERRUPT_DESTROY_ERROR     = 60,
    I2O_STS_PAGE_SET_DESTROY_ERROR      = 61,
    I2O_STS_MEM_SET_DESTROY_ERROR       = 62,
    I2O_STS_THREAD_DESTROY_ERROR        = 63,
    I2O_STS_PIPE_DESTROY_ERROR          = 64,
    I2O_STS_SEM_DESTROY_ERROR           = 65,
    I2O_STS_EVENT_Q_DESTROY_ERROR       = 66,
    I2O_STS_DMA_DESTROY_ERROR           = 67,
    I2O_STS_DDM_DESTROY_ERROR           = 68,
    I2O_STS_DEV_DESTROY_ERROR           = 69,
    I2O_STS_PEER_INVALID_DEST           = 70,
    I2O_STS_PEER_QOS_NOT_AVAIL          = 71,
    I2O_STS_PEER_SVC_LOST               = 72,
    I2O_STS_PEER_INVALID_SGL            = 73,
    I2O_STS_PEER_NO_TX                  = 74,
    I2O_STS_PEER_PARTIAL_TX             = 75,
    I2O_STS_PEER_INVALID_LOCAL_SGL      = 76,
    I2O_STS_PEER_INVALID_REMOTE_SGL     = 77,
    I2O_STS_PEER_INVALID_SIZE           = 78,
    I2O_STS_PEER_INVALID_SIZE_PROXY     = 79,
    I2O_STS_PEER_NO_TRANSFER            = 80,
    I2O_STS_PEER_PARTIAL_TRANSFER       = 81,
    I2O_STS_PEER_INVALID_REDIR_SIZE     = 82,
    I2O_STS_PEER_INVALID_REDIR_SEG      = 83,
    I2O_STS_PEER_INSUF_MEM              = 84,
    I2O_STS_PEER_NOT_READY              = 85,
    I2O_STS_PEER_DATA_DELIVERED         = 86,
    I2O_STS_PEER_LOCAL_TID_UNALIASED    = 87,
    I2O_STS_PEER_XFR_ATTR_NOT_AVAIL     = 88,
    I2O_STS_DMA_GROUP_ERROR             = 89,
    I2O_STS_DMA_SYNC_ERROR              = 90,
    I2O_STS_INDIRECT_ERROR              = 91,
    I2O_STS_INVALID_ADDR                = 92,
    I2O_STS_NO_RESOURCES                = 93
    } I2O_STATUS;					

typedef void		(*I2O_ERROR_FUNC) (I2O_STATUS);  /* I2O_ERROR_FUNC */
    
#define	I2O_NO_STATUS	(I2O_STATUS *) NULL	/* I2O_NO_STATUS */

/* i2o error action codes */

typedef	enum					/* I2O_ERROR_ACTION */
    {
    I2O_ERR_ACT_DEFAULT		= 0,
    I2O_ERR_ACT_PRINTMSG	= 1,
    I2O_ERR_ACT_IGNORE		= 2,
    I2O_ERR_ACT_USER		= 3,
    I2O_ERR_ACT_DEBUG		= 4,
    I2O_ERR_ACT_DESTROY_DDM	= 5
    } I2O_ERROR_ACTION;

/* function declarations */

extern void		i2oErrorSet (I2O_STATUS errorCode, 
			  	     I2O_STATUS * status);
extern void		i2oErrorAction (I2O_STATUS errorCode, 
					I2O_ERROR_ACTION errorAction);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCi2oErrorLibh */

