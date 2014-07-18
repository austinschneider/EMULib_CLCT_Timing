// $Id: ArchTask.h,v 1.3 2008/07/18 15:27:31 gutleber Exp $

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
// --    The architecture specific part of the task class.
// --
// --  ABSTRACT:
// --    Although class Task inherits from this class it also hosts
// --    some architecture specific calls, like pthread_mutex_lock.
// --    This is, because we have not yet wrapped the mutexes. 
// --    class Task should be the clean interface that the user sees.
// --
// --  VERSION:
// --    1.0
// --
// --  MODIFICATION:
// --    Date           Purpose                               Author
// --    04-Aug-1999    Creation.                             JG

#ifndef _toolbox_ArchTask_H_
#define _toolbox_ArchTask_H_

//
// Include the Posix stuff
//
#include <pthread.h>
#include "toolbox/exception/FailedToActivateTask.h"

namespace toolbox 
{

// 
// Forward declarations
//
class TaskGroup;
class TaskAttributes;
class Task;

int task_spawn (TaskAttributes*  attrib, Task* task) throw (toolbox::exception::FailedToActivateTask);

class ArchTask
{
 public:
 
  ArchTask();
  ~ArchTask();

  //
  // for the moment public, as it is called from
  // within thread hook which is a C function
  //
  void incRefCount();
  void decRefCount();
  void initTaskGroup(TaskGroup* group);

 protected:
  TaskAttributes* attrib_;
  pthread_t       threadid_;
  int 		  yield_counter_;

  //
  // Synchronisation variables needed for
  // sleep, pause and wakeup
  //
  pthread_mutex_t task_condvar_lock;
  pthread_cond_t  task_condvar;

  //
  // Just a wrapper to pthread_thread_create
  //
  friend int task_spawn (TaskAttributes*  attrib, Task* task) throw (toolbox::exception::FailedToActivateTask);
  
  TaskGroup* group_;
};

}

#endif 
