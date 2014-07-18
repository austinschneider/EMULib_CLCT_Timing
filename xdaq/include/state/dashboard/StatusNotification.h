// $Id: StatusNotification.h,v 1.2 2007/11/16 13:22:37 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _state_dashboard_StatusNotification_h_
#define _state_dashboard_StatusNotification_h_

#include "xoap/SOAPElement.h"
#include "state/dashboard/exception/Exception.h"

namespace state
{
namespace dashboard
{
	class StatusNotification
	{
	public:
		StatusNotification();

		StatusNotification(const StatusNotification& s);

		StatusNotification(xoap::SOAPElement& element) 
			throw (state::dashboard::exception::Exception);
	
		StatusNotification& operator= (const StatusNotification & request);

		std::string getIdentifier();
		std::string getNotifier();
		std::string getDateTime();
		std::string getSeverity();
		std::string getServiceURN();
		std::string getState();
		std::string getServiceType();

	protected:
		std::string identifier_;
		std::string notifier_;
		std::string datetime_; 
		std::string severity_;
		std::string serviceurn_;
		std::string state_;
		std::string servicetype_;
	};
}
}

#endif

