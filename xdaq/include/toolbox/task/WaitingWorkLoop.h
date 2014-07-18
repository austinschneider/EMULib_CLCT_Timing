// $Id: WaitingWorkLoop.h,v 1.6 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_WaitingWorkLoop_h_
#define _toolbox_task_WaitingWorkLoop_h_

#include<string>
#include<vector>
#include<pthread.h>
#include "toolbox/task/WorkLoop.h"
#include "toolbox/squeue.h"
#include "toolbox/task/Action.h"


namespace toolbox
{
	namespace task
	{
		
		class WaitingWorkLoop: public toolbox::task::WorkLoop
		{
			public:
			
			WaitingWorkLoop(const std::string & name);
			
			void submit (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception);
			void remove (toolbox::task::ActionSignature* action) throw (toolbox::task::exception::Exception);
			
			void activate() throw (toolbox::task::exception::Exception);
			
			void cancel() throw (toolbox::task::exception::Exception);

			void resize(size_t n) throw (toolbox::task::exception::Exception);
		
			protected:
			
			
			void process();
						
			private:
			
			toolbox::squeue<toolbox::task::ActionSignature*> jobs_;			
		};
		
	}
}

#endif
