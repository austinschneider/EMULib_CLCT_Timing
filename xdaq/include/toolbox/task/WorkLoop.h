// $Id: WorkLoop.h,v 1.9 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_WorkLoop_h_
#define _toolbox_task_WorkLoop_h_

#include<string>
#include<vector>
#include<pthread.h>

#include "toolbox/task/exception/Exception.h"
#include "toolbox/task/Action.h"

namespace toolbox
{
	namespace task
	{	
		void * thread_func (void* workLoop);
		
		class WorkLoop
		{
			public:
			
			
			//! CTOR, takes a name and a type that can be "waiting" or "polling"
			//
			WorkLoop(std::string name, std::string type);
			
			//! DTOR, also calls cancel inside
			//
			virtual ~WorkLoop();
			
			//! Schedule a method to be executed in the work Loop. The ActionSignature must be implemented
			//
			virtual void submit (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception) = 0;

			//! Remove a scheduled method from the work loop.
			//
			virtual void remove (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception) = 0;
			
			//! Create a task inside the workloop. The function fails if the work loop is already active
			//
			void activate() throw (toolbox::task::exception::Exception);
			
			//! End the task of the work loop. The function fails if the work loop is not active
			//
			virtual void cancel() throw (toolbox::task::exception::Exception);

			//! Resize the work loop queue size. No more than \param n jobs can be enqueued at a time
			//
			virtual void resize(size_t n) throw (toolbox::task::exception::Exception);
			
			//! Returns the name of the work loop
			//
			std::string getName();
			
			//! Returns the type of the work loop ("polling", or "waiting")
			//
			std::string getType();
			
			//! Returns true if the work loop task is running, false otherwise
			//
			bool isActive();
			
			
			protected:
						
			friend void * thread_func (void* workLoop);

			//! The task routine of the work loop
			//
			virtual void process() = 0;			
			
			protected:
			
			void run();
			
			pthread_t	thread_id_;
			pthread_attr_t	thread_attributes_;
			
			std::string 	type_;
			std::string 	name_;
			bool		active_;
			bool 		stopped_;
			size_t 		size_;			
		};
	}
}

#endif
