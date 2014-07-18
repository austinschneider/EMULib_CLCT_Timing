// $Id: WorkLoopFactory.h,v 1.5 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_WorkLoopFactory_h_
#define _toolbox_task_WorkLoopFactory_h_

#include<string>
#include<list>
#include<map>
#include "toolbox/net/URN.h"
#include "toolbox/task/WorkLoop.h"

namespace toolbox
{
	namespace task
	{
		class WorkLoopFactory
		{
			public:
			
			WorkLoop* getWorkLoop(const std::string & name, const std::string & type) throw (toolbox::task::exception::Exception);
			
			/**
			* The URN format identifying a work loop is as follows:
			*
			* urn:toolbox-task-workloop:<name>/<polling|waiting>
			*
			*/
			WorkLoop* getWorkLoop(toolbox::net::URN & urn, const std::string & type) throw (toolbox::task::exception::Exception);
			
			void removeWorkLoop(const std::string & name, const std::string & type) throw (toolbox::task::exception::Exception);
			
			void removeWorkLoop(toolbox::net::URN & urn) throw (toolbox::task::exception::Exception);
			
			std::list<WorkLoop*> getWorkLoops();
	
			//! Retrieve a pointer to the toolbox::task::WorkLoopFactory singleton
			//
			static WorkLoopFactory* getInstance();
			
			//! Destoy the factory and all associated work loops
			//
			static void destroyInstance();
			
			private:
			
			static WorkLoopFactory* instance_;
			
			std::map<std::string, toolbox::task::WorkLoop*, std::less<std::string> > workLoops_;
			
		};
		
		//! Retrieve a pointer to the toolbox::task::WorkLoopFactory singleton
		//
		WorkLoopFactory* getWorkLoopFactory();
	}
}

#endif
