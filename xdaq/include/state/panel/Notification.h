// $Id: Notification.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_Notification_h_
#define _statepanel_Notification_h_

#include <string>
#include <list>

#include "toolbox/TimeVal.h"

namespace state
{
namespace panel
{
	class Notification
	{
		public:

		Notification();

		~Notification();

		void setNotifier(const std::string& value);
		void setIdentifier(const std::string& value);
		void setUniqueId(const std::string& value);
		void setMessage(const std::string& value);
		void setMark(const std::string& value);
		void setTimeStamp(const toolbox::TimeVal& value);
		void addExceptionUniqueId(const std::string& value);
		void addServiceURL(const std::string& value);

		const std::string& getNotifier() const;
		const std::string& getIdentifier() const;
		const std::string& getUniqueId() const;
		const std::string& getMessage() const;
		const std::string& getMark() const;
		const toolbox::TimeVal& getTimeStamp() const;
		const std::list<std::string>& getExceptionUniqueIds() const;
		const std::list<std::string>& getServiceURLs() const;

		protected:

		std::string notifier_;
		std::string identifier_;
		std::string uniqueid_;
		std::string message_;
		std::string mark_;
		toolbox::TimeVal timestamp_;
		std::list<std::string> exceptionUniqueIds_;
		std::list<std::string> serviceURLs_;
	};
}
}
#endif

