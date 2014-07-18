// $Id: NotificationEvent.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_NotificationEvent_h_
#define _statepanel_NotificationEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "state/panel/Notification.h"

namespace state
{
namespace panel
{
	/*!
		An event that encapsulates an operator Notification.
	*/
	class NotificationEvent:  public toolbox::Event
	{
		public:

		NotificationEvent(state::panel::Notification* n, const std::string & name);

		~NotificationEvent();

		//! Obtain a copy of a reference to the underlying SOAP message
		/*!
			The underlying notification is automatically deleted when
			the last user of the event gives up using the reference to the event.
		*/
		state::panel::Notification* getNotification();

		std::string name();

		protected:

		state::panel::Notification* notification_;
		std::string name_;
	};
}
}
#endif

