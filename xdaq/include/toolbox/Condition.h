// $Id: Condition.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Condition_h_
#define _toolbox_Condition_h_

#include "toolbox/archCondition.h" 
#include "toolbox/exception/Timeout.h" 


//! Thread synchronization with wait and signal.
/* Implements thread synchronization based on
   condition variables using wait and signal. Multiple
   threads can wait on a condition. If a thread signals,
   arbitrarily one is chosen to be unblocked. Alternatively
   the signalling thread can issue a broadcast that causes
   all waiting threads to be unblocked.
*/
namespace toolbox 
{
	class Condition
	{
	  public:

	    Condition();
	    ~Condition();

		//! Suspend the thread until the condition becomes true
		//
    		inline int wait();

		//! Suspend the thread until the condition becomes true or until the timeout is reached
		/*! The function will throw a Condition exception if the timeout is reached */
    		inline int timedwait(time_t sec, suseconds_t usec) throw (toolbox::exception::Timeout);

		//! Signal that a condition became true. This will unblock one of the threads hanging on \function wait
		//
    		inline int signal();

		//! Signal that a condition became true. This will unblock all threads hanging on \function wait
		//
    		inline int broadcast();

	  protected:

#include "toolbox/archConditionPrivate.i"
	};

#include "toolbox/archCondition.i"
}

#endif
