// $Id: ThreadGroup.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

// --  DOMAIN:
// --    POSLIB - Portable Operating System LIBrary
// --
// --  FACILITY:
// --    A Class to manage groups of tasks
// --
// --  ABSTRACT:
// --
// --
// --  VERSION:
// --    1.0
// --
// --  MODIFICATION:
// --    Date           Purpose                               Author
// --    04-Aug-1999    Creation.                             JG

#ifndef _toolbox_TaskGroup_H_
#define _toolbox_TaskGroup_H_

/*! This class is deprecated! If you needs threads, use toolbox::tasl::WorkLoop instead
*/
namespace toolbox
{
	class Task;

	class ThreadGroup
	{
	 public:
	  ThreadGroup();
	  ~ThreadGroup();

	  void incRefCount();
	  void decRefCount();

	  int join();

	private:
	  //
	  // Synchronisation variables needed for join.
	  // Although available in POSIX we emulate it
	  // for compatibility reasons with VxWorks.
	  //
	  pthread_mutex_t join_condvar_lock;
	  pthread_mutex_t join_release_lock;
	  int refCount;
	};
}
#endif // Task_H
