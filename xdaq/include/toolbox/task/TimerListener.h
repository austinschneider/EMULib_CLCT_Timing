// $Id: TimerListener.h,v 1.2 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_TimerListener_h_
#define _toolbox_task_TimerListener_h_

#include "toolbox/task/TimerEvent.h"

namespace toolbox
{
	namespace task
	{
		class TimerListener
		{
			public:
			virtual ~TimerListener()
			{
			}

			virtual void timeExpired(toolbox::task::TimerEvent& e) = 0;
		};
	}
}

#endif
