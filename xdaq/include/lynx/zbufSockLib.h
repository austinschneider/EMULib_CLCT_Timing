// $Id: zbufSockLib.h,v 1.3 2008/07/18 15:27:31 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

/* zbufSockLib.h - zeroCopy buffer socket interface library header */

/* Copyright 1984-1994 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,08nov94,dzb  written.
*/

#ifndef __INCzbufSockLibh
#define __INCzbufSockLibh

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

#include "zbufLib.h"
#include <sys/types.h>

#ifdef lynx
#include <socket.h>
#include "typeslynx.h"
#else
#include <sys/socket.h>
#include "types.h"
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
 


/* typedefs */

typedef struct				/* ZBUF_SOCK_FUNC */
    {
    FUNCPTR	libInitRtn;		/* zbufLibInit()	*/
    FUNCPTR	sendRtn;		/* zbufSockSend()	*/
    FUNCPTR	sendtoRtn;		/* zbufSockSendto()	*/
    FUNCPTR	bufSendRtn;		/* zbufSockBufSend()	*/
    FUNCPTR	bufSendtoRtn;		/* zbufSockBufSend()	*/
    FUNCPTR	recvRtn;		/* zbufSockRecv()	*/
    FUNCPTR	recvfromRtn;		/* zbufSockRecvfrom()	*/
    } ZBUF_SOCK_FUNC;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	zbufSockLibInit (void);
extern int	zbufSockSend (int s, ZBUF_ID zbufId, int zbufLen, int flags);
extern int	zbufSockSendto (int s, ZBUF_ID zbufId, int zbufLen, int flags,
                    struct sockaddr *to, int tolen);
extern int	zbufSockBufSend (int s, char *buf, int bufLen,
                    VOIDFUNCPTR freeRtn, int freeArg, int flags);
extern int	zbufSockBufSendto (int s, char *buf, int bufLen,
                    VOIDFUNCPTR freeRtn, int freeArg, int flags,
                    struct sockaddr *to, int tolen);
extern ZBUF_ID	zbufSockRecv (int s, int flags, int *pLen);


#ifdef linux		    
extern ZBUF_ID	zbufSockRecvfrom (int s, int flags, int *pLen,
                    struct sockaddr *from, socklen_t *pFromLen);
#else
extern ZBUF_ID	zbufSockRecvfrom (int s, int flags, int *pLen,
                    struct sockaddr *from, int *pFromLen);
#endif
#else	/* __STDC__ */

extern STATUS	zbufSockLibInit ();
extern int	zbufSockSend ();
extern int	zbufSockSendto ();
extern int	zbufSockBufSend ();
extern int	zbufSockBufSendto ();
extern ZBUF_ID	zbufSockRecv ();
extern ZBUF_ID	zbufSockRecvfrom ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCzbufSockLibh */
