// $Id: ArchTaskAttributes.h,v 1.2 2008/07/18 15:27:30 gutleber Exp $

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
// --    Architecture specific class to the task parameters
// --
// --  ABSTRACT:
// --    This class holds all necessary attributes for performing
// --    a mapping of the generic task attributes to platform specific
// --    parameters.
// --
// --  VERSION:
// --    1.0
// --
// --  MODIFICATION:
// --    Date           Purpose                               Author
// --    04-Aug-1999    Creation.                             JG

#ifndef _toolbox_ArchTaskAttributes_H_
#define _toolbox_ArchTaskAttributes_H_

#include "toolbox/exception/FailedToActivateTask.h"

//
// Include the Posix stuff
//
#include <pthread.h>

namespace toolbox
{
	// 
	// Forward declaration
	//
	class TaskAttributes;
	class Task;

	int task_spawn (TaskAttributes*  attrib, Task* task) throw (toolbox::exception::FailedToActivateTask);



	class ArchTaskAttributes
	{
	public:
	  ArchTaskAttributes();
	  ~ArchTaskAttributes();

	protected:
	  pthread_attr_t     attr_; // POSIX thread attributes
	  char*              name_; // task name for VxWorks compatibility

	  //
	  // A wrapper to the pthread_thread_create call
	  //
	  friend int task_spawn (TaskAttributes*  attrib, Task* task) throw (toolbox::exception::FailedToActivateTask);
	};
}

#endif 
