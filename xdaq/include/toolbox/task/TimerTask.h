// $Id: TimerTask.h,v 1.3 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_TimerTask_h_
#define _toolbox_task_TimerTask_h_

#include <string>
#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"

namespace toolbox 
{
	namespace task
	{
			class TimerListener;

			class TimerTask
			{
				public:
				
				toolbox::TimeVal schedule; // absolute time for execution
				toolbox::TimeInterval period; // delay after which action is executed
				toolbox::TimeVal lastExecutionTime; // time of last actual execution
				toolbox::task::TimerListener* listener; // listener for time expiration
				void * context;
				bool fixedRate;
				std::string name;
				
				bool operator>(const TimerTask& t) const
				{
					return (schedule > t.schedule);
				}
			};
	}

}

#endif
