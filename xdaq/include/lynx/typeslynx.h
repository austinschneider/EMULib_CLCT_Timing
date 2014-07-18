// $Id: typeslynx.h,v 1.3 2008/07/18 15:27:31 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef __INCvxTypesOldh
#define __INCvxTypesOldh

#ifdef __cplusplus
extern "C" {
#endif
#define TRUE          1
#define ERROR         (-1)
#define FALSE         0

typedef char *  caddr_t;

typedef    int             BOOL;
typedef    int             STATUS;

#ifdef __cplusplus
typedef int 		(*FUNCPTR) (...);     /* ptr to function returning int */
typedef void 		(*VOIDFUNCPTR) (...); /* ptr to function returning void */
typedef double 		(*DBLFUNCPTR) (...);  /* ptr to function returning double*/
typedef float 		(*FLTFUNCPTR) (...);  /* ptr to function returning float */
typedef void            (*VOIDINTFUNCPTR) (int); /* ptr to function returning void */
#else
typedef int 		(*FUNCPTR) ();	   /* ptr to function returning int */
typedef void 		(*VOIDFUNCPTR) (); /* ptr to function returning void */
typedef double 		(*DBLFUNCPTR) ();  /* ptr to function returning double*/
typedef float 		(*FLTFUNCPTR) ();  /* ptr to function returning float */
#endif			/* _cplusplus */

#ifdef __cplusplus
}
#endif


#endif /* __INCvxTypesOldh */
