// $Id: PollingWorkLoop.h,v 1.7 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_PollingWorkLoop_h_
#define _toolbox_task_PollingWorkLoop_h_

#include<string>
#include<vector>
#include<pthread.h>

#include "toolbox/task/WorkLoop.h"
#include "toolbox/rlist.h"
#include "toolbox/BSem.h"
#include "toolbox/task/Action.h"

namespace toolbox
{
	namespace task
	{
		
		
		class PollingWorkLoop: public toolbox::task::WorkLoop
		{
			public:
			
			PollingWorkLoop(const std::string &  name);

			void submit (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception);
			void remove (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception);
			void resize(size_t n) throw (toolbox::task::exception::Exception);
			
			protected:
			
			void process();
			
			private:
			
			toolbox::rlist<toolbox::task::ActionSignature*> schedule_;
			toolbox::rlist<toolbox::task::ActionSignature*> jobs_;
			toolbox::BSem mutex_;
			
		};
	}
}

#endif
