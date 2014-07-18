// $Id: StatusNotifications.h,v 1.1 2007/11/16 13:22:37 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _state_dashboard_StatusNotifications_h_
#define _state_dashboard_StatusNotifications_h_

#include <vector>

#include "xoap/MessageReference.h"
#include "state/dashboard/StatusNotification.h"
#include "state/dashboard/exception/Exception.h"

namespace state
{
namespace dashboard
{
	class StatusNotifications
	{
	public:
		StatusNotifications();

		StatusNotifications(const StatusNotifications& s);

		StatusNotifications(xoap::MessageReference& msg) 
			throw (state::dashboard::exception::Exception);
	
		StatusNotifications& operator= (const StatusNotifications & request);

		std::vector<state::dashboard::StatusNotification>& getNotifications();

	protected:
		std::vector<state::dashboard::StatusNotification> notifications_;
	};
}
}

#endif

