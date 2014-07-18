// $Id: NotificationSerializer.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_NotificationSerializer_h_
#define _statepanel_NotificationSerializer_h_

#include <string>
#include "state/panel/Notification.h"

#include "xoap/domutils.h"

namespace state
{
namespace panel
{
	class NotificationSerializer
	{
		public:

		static void importFrom( DOMNode * node, state::panel::Notification& notification);

	};
}
}
#endif

