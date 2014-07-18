// $Id: archSys.h,v 1.3 2008/07/18 15:27:31 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

//
//  File Name:
//
//      archSys.h
//
//  File Type:
//
//      C++ Header file
//
//  Creative Authors:
//
//      Luciano B. ORSINI
//      CERN, EP Division
//      CMD group
//      CMS TriDAS
//      Compact Muon Solenoid - Trigger and Data Acquisition
//      Geneva, Switzerland
//
//      Tel: (+41) 22 76 71615 
//
//  Change History:
//
//      $Log: archSys.h,v $
//      Revision 1.3  2008/07/18 15:27:31  gutleber
//      Changed Copyright date 2000-2009
//
//      Revision 1.2  2004/09/02 09:55:37  xdaq
//      File header
//
//      Revision 1.1  1999/12/07 13:40:17  lorsini
//      Reference: FD
//      Software Change:
//      	Source created.
//
//      Revision 1.1  1999/11/15 16:40:16  lorsini
//      Reference: LO
//      Software Change:
//      	re-structure repository.
//
//      Revision 1.1  1999/08/13 12:58:31  lorsini
//      Reference: LO
//      Software Change:
//      	Source created.
//
//      Revision 1.1  1999/04/14 13:50:57  lorsini
//      Reference: LORSINI
//      Software Change:
//      	Source Created.
//      	Porting toolbox to sun4u/sparc platform.
//
//      Revision 1.1  1999/11/30 drouhin
//      Reference: FDROUHIN
//      Software Change:
//              Porting toolbox to lynx/ces604 platform. 
//
// 
//  ------------------------------------------------------------------------
//  ------------------  Pre-processor Control Directives  ------------------
//  ------------------------------------------------------------------------
 
// The following pre-processor directives ensure that spurious errors will not
// be generated in the event that this header file is included several times.

#include <errno.h>        
#include <sys/types.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#ifdef lynx
#include <time.h>
#include "typeslynx.h"
#include <pthread.h>
#else
#include <sys/time.h>
#include "types.h"
#endif

#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <iostream.h>
#include "zbufLib.h"
#include "limits.h"
#include "rngLib.h"
#include "semLib.h"
#include "zbufSockLib.h"


typedef struct timeval TimeSpec;

// Terminate the #if ... #endif pre-processor control directive located at the
// start of this header file.
 
//#endif /* ifndef  __archSys_h__ */

