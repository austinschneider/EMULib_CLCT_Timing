// $Id: GaugeEvent.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_GaugeEvent_h_
#define _toolbox_GaugeEvent_h_

#include "toolbox/Event.h"
#include <string>

namespace toolbox 
{
	class GaugeEvent: public toolbox::Event
	{
		public:

		GaugeEvent(const std::string& type, const std::string& name, void* originator=0);

		std::string getName();

		protected:

		std::string name_;

	};

	class GaugeAvailableEvent: public toolbox::GaugeEvent
	{
		public:
			GaugeAvailableEvent(const std::string& name, void* originator=0);
	};

	class GaugeRevokedEvent: public toolbox::GaugeEvent
	{
		public:
			GaugeRevokedEvent(const std::string& name, void* originator=0);
	};
}

#endif
