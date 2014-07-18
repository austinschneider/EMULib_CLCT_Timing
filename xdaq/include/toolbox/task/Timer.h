// $Id: Timer.h,v 1.6 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_Timer_h_
#define _toolbox_task_Timer_h_

#include <string>
#include <vector>
#include <pthread.h>
#include <queue>
#include <stack>
#include <algorithm>
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/TimerTask.h"
#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"
#include "toolbox/task/exception/Exception.h"
#include "toolbox/task/exception/InvalidListener.h"
#include "toolbox/task/exception/InvalidSubmission.h"
#include "toolbox/task/exception/NotActive.h"
#include "toolbox/task/exception/NoJobs.h"
#include "toolbox/task/exception/JobNotFound.h"


#include "toolbox/exception/Dispatcher.h"
#include "toolbox/Task.h"


namespace toolbox
{
	namespace task
	{		
		class Timer: public Task
		{					
			public:
						
			Timer(const std::string & name);
			~Timer();
			
			//! Schedules the specified task for execution after the specified delay
			void scheduleAtFixedRate (
						toolbox::TimeVal& start,
						toolbox::task::TimerListener* listener,
						toolbox::TimeInterval& period,
						void* context,
						const std::string& name) 
				throw (toolbox::task::exception::InvalidListener, toolbox::task::exception::InvalidSubmission, toolbox::task::exception::NotActive);
			
			//! Schedules the specified task for execution at the specified time
			void schedule (toolbox::task::TimerListener* listener, toolbox::TimeVal& time, void * context, const std::string & name) 
					throw (toolbox::task::exception::InvalidListener, toolbox::task::exception::InvalidSubmission, toolbox::task::exception::NotActive)
;
					
				
			void remove (const std::string& name) 
				throw (toolbox::task::exception::NotActive, toolbox::task::exception::NoJobs, toolbox::task::exception::JobNotFound );

			void start()  throw (toolbox::task::exception::Exception);

			void stop() throw (toolbox::task::exception::NotActive);

			bool isActive();
		
			std::vector<toolbox::task::TimerTask>  getScheduledTasks() throw (toolbox::task::exception::NotActive);
			
			void addExceptionListener( toolbox::exception::Listener * listener );

                        void removeExceptionListener( toolbox::exception::Listener * listener ) 
                                throw (toolbox::exception::Exception);

			
			protected:
						
			int svc();			
						
			private:
			
			// keep record of current schedule by name, only unique names are allowed
			std::map<std::string, toolbox::task::TimerTask, std::less<std::string> > schedules_;
			
			std::priority_queue<toolbox::task::TimerTask, std::vector<toolbox::task::TimerTask>, std::greater<toolbox::task::TimerTask> > jobs_;
			
			pthread_mutex_t conditionMutex_;
			pthread_cond_t conditionVar_;
			pthread_mutexattr_t mattr_;
			pthread_condattr_t cvattr_;
			
			bool done_;
			bool active_;
			
			toolbox::exception::Dispatcher dispatcher_;
		}; // end of Timer		
	} // ns task
} // ns toolbox

#endif
