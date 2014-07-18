//$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_ConnectEvent_h_
#define _b2in_utils_ConnectEvent_h_

#include <string>
#include "toolbox/Event.h"

namespace b2in
{
	namespace utils
	{
		class ConnectEvent : public toolbox::Event
		{
		public:
			ConnectEvent(const std::string & url, void* originator = 0) : Event("connect", originator)
			{
				url_ = url;
			}

			virtual ~ConnectEvent()
			{
			}

			std::string getURL()
			{
				return url_;
			}

		protected:
			std::string url_;
		};
	}
}

#endif

