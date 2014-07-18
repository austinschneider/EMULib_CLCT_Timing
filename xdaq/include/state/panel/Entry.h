// $Id: Entry.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_Entry_h_
#define _statepanel_Entry_h_

#include <string>
#include <list>
#include <set>
#include <map>

#include "state/panel/Notification.h"

#include "toolbox/TimeVal.h"

namespace state
{
namespace panel
{
	class Entry
	{
		public:

		Entry(const Notification& value);

		~Entry();

		void addNotification(const Notification& value);
		//! tries to mark the notifications and returns a list of uuids for which this failed
		std::set<std::string> setMark(const std::string& action, const std::set<std::string>& uuids);

		const std::string& getIdentifier() const;
		const std::string& getMessage() const;
		toolbox::TimeVal getLastUpdate() const;
		size_t hasMark(const std::string& mark) const;

		const std::map<std::string, state::panel::Notification>& getNotifications() const;

		protected:
		void decrementMark(const std::string& mark);
		void incrementMark(const std::string& mark);

		std::string identifier_;
		std::string message_;
		toolbox::TimeVal lastUpdate_;
		std::map<std::string,state::panel::Notification> notifications_;
		std::map<std::string, size_t> marks_;
	};
}
}
#endif

