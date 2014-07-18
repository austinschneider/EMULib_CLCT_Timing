// $Id: TaskAttributes.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

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
// --    Attributes that can be passed to a task.
// --
// --  ABSTRACT:
// --    An instance of such an attribute class can be passed
// --    to a Task object either before activation or after.
// --    In the former case the task uses these parameters when
// --    spawned. In the latter the running tasks parameters are
// --    modificed. This will have an effect on the runtime.
// --
// --  VERSION:
// --    1.0
// --
// --  MODIFICATION:
// --    Date           Purpose                               Author
// --    04-Aug-1999    Creation.                             JG

#ifndef _toolbox_TaskAttributes_H_
#define _toolbox_TaskAttributes_H_

//
// The architecture dependent ArchTaskAttributes class is
// included according to the include path given in the makefile
//

#include "toolbox/ArchTaskAttributes.h"


namespace toolbox
{
	class TaskAttributes: public ArchTaskAttributes
	{
	public:
	  TaskAttributes();
	  ~TaskAttributes();

	  // These members also return error variables.
	  // Later they should throw exceptions as well.
	  //
	  int   name(const char* name);
	  char* name();

	  int   priority(int level);
	  int   priority(); // return priority

	  int   stacksize(int size);
	  int   stacksize(); // return stacksize

	  int	detached(bool detach);
	  bool	detached(); // return if the task is decoupled from the creating task
	};
}
#endif 
