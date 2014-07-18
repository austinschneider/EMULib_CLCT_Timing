// $Id: Task.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

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
// --    The Task class
// --
// --  ABSTRACT:
// --    The Task class provides functionality to run threads or
// --    tasks on different operating systems.
// --
// --  VERSION:
// --    1.0
// --
// --  MODIFICATION:
// --    Date           Purpose                               Author
// --    04-Aug-1999    Creation.                             JG


#ifndef _toolbox_Task_H_
#define _toolbox_Task_H_

//
// The architecture dependent task class is included
// according to the include path given in the makefile
//

#include "toolbox/ArchTask.h"

namespace toolbox
{
	//
	// Forward declaration
	//
	class TaskAttributes;


	class Task: public ArchTask
	{
	 public:
	  Task(const char * name);
	  virtual ~Task();

	  int set (TaskAttributes* attrib);
	  int get (TaskAttributes* attrib);

	  int activate (int argc, char* argv[]) throw (toolbox::exception::FailedToActivateTask);
	  int activate (int argc = 0, ...) throw (toolbox::exception::FailedToActivateTask);

	  int kill();

	  int wakeup();

	  void yield (int every_n_times);

	  virtual int svc()     = 0; // service routine to be defined by user

	protected:

	  //
	  // these members are usable from within derived classes
	  //
	  int sleep (int seconds);
	  int pause ();

	  //
	  // arguments accessible from within the svc
	  //
	  int                argc_;
	  char**             argv_;
	};
}
#endif // Task_H
