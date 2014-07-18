// $Id: TimerFactory.h,v 1.3 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_TimerFactory_h_
#define _toolbox_task_TimerFactory_h_

#include<string>
#include<list>
#include<map>
#include "toolbox/net/URN.h"
#include "toolbox/task/Timer.h"

namespace toolbox
{
	namespace task
	{
		class TimerFactory
		{
			public:
			
			//! Create a timer, if \param name already existing, throw
			Timer* createTimer(const std::string & name) throw (toolbox::task::exception::Exception);
			
			/*! Create a timer, if \param name already existing, throw
			*
			* The URN format identifying a work loop is as follows:
			*
			* urn:toolbox-task-timer:<name>
			*
			*/
			Timer* createTimer(toolbox::net::URN & urn) throw (toolbox::task::exception::Exception);
			
			//! Returns true if timer if existing, false otherwise
			//
			bool hasTimer(const std::string & name);
			
			/*! Returns true if timer if existing, false otherwise
			*
			* The URN format identifying a work loop is as follows:
			*
			* urn:toolbox-task-timer:<name>
			*
			*/
			bool hasTimer(toolbox::net::URN & urn);
			
			//! Returns timer if existing, throws otherwise
			//
			Timer* getTimer(const std::string & name) throw (toolbox::task::exception::Exception);
			
			/*! Returns timer if existing, throws otherwise
			*
			* The URN format identifying a work loop is as follows:
			*
			* urn:toolbox-task-timer:<name>
			*
			*/
			Timer* getTimer(toolbox::net::URN & urn) throw (toolbox::task::exception::Exception);
			
			void removeTimer(const std::string & name) throw (toolbox::task::exception::Exception);
			
			void removeTimer(toolbox::net::URN & urn) throw (toolbox::task::exception::Exception);
			
			std::list<Timer*> getTimers();
	
			//! Retrieve a pointer to the toolbox::task::TimerFactory singleton
			//
			static TimerFactory* getInstance();
			
			//! Destoy the factory and all associated timers
			//
			static void destroyInstance();
			
			private:
			
			static TimerFactory* instance_;
			
			std::map<std::string, toolbox::task::Timer*, std::less<std::string> > timers_;
			
		};
		
		//! Retrieve a pointer to the toolbox::task::TimerFactory singleton
		//
		TimerFactory* getTimerFactory();
	}
}

#endif
