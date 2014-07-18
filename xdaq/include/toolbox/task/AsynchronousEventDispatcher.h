// $Id: AsynchronousEventDispatcher.h,v 1.5 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_AsynchronousEventDispatcher_h_
#define _toolbox_task_AsynchronousEventDispatcher_h_

#include <list>
#include "toolbox/BSem.h"
#include "toolbox/lang/Class.h"
#include "toolbox/rlist.h"
#include "toolbox/EventDispatcher.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/exception/OverThreshold.h"
#include "toolbox/task/exception/Overflow.h"
#include "toolbox/task/exception/InternalError.h"
#include "toolbox/task/EventReference.h"

namespace toolbox 
{
	namespace task 
	{
		class AsynchronousEventDispatcher: public toolbox::lang::Class
		{
			public:

			//! threshold give the size in percent for the dead band algorithm // e.g 0.1 means 10%
			AsynchronousEventDispatcher(const std::string & workloop,const std::string & type, double threshold, size_t qsize = 1024 );

			void addActionListener( toolbox::ActionListener * l ) throw (toolbox::exception::Exception);

			void removeActionListener( toolbox::ActionListener * l ) throw (toolbox::exception::Exception);

			void fireEvent ( toolbox::task::EventReference & e) 
				throw (toolbox::task::exception::OverThreshold, toolbox::task::exception::Overflow,
				toolbox::task::exception::InternalError);

			protected:

			bool processNotification(toolbox::task::WorkLoop* wl);

			private:

			toolbox::task::WorkLoop* workLoop_;
			toolbox::EventDispatcher dispatcher_;
			std::list<toolbox::ActionListener*> actionListenerList_;
			toolbox::task::ActionSignature* processNotificationJob_;			
			toolbox::rlist<toolbox::task::EventReference*> notificationQueue_;			
			toolbox::BSem mutex_;
			
			// dead band algorithm
			size_t threshold_;
			bool deadBand_;
			
		};
	}
}
#endif
