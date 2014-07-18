// $Id: archConditionPrivate.i,v 1.2 2008/07/18 15:27:30 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

pthread_mutex_t      	condMutex_;    // mutex for condition
pthread_cond_t		condVar_;	// condition variable
unsigned int		existInfo_; // indicates that a thread wants to signal information

// added by Wojciech BIALAS, CERN UAT, 29.01.2004
struct timespec ttw_ ;
