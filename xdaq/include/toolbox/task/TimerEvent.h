// $Id: TimerEvent.h,v 1.2 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_TimerEvent_h_
#define _toolbox_task_TimerEvent_h_

#include <string>
#include "toolbox/Event.h"


namespace toolbox 
{
	namespace task
	{
		class TimerTask;

		class TimerEvent: public toolbox::Event
		{
			public:


			TimerEvent(void* originator, toolbox::task::TimerTask * task): toolbox::Event("TimerEvent", originator)
			{
				task_ = task;
			}

			toolbox::task::TimerTask * getTimerTask()
			{
				return task_;
			}


			protected:

			toolbox::task::TimerTask * task_;


		};
	}

}

#endif
