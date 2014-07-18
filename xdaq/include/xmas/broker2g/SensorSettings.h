/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_SensorSettings_h_
#define _xmas_broker2g_SensorSettings_h_

#include <string>
#include <map>

#include "xmas/broker2g/Utils.h"

#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"

#include "xdata/UnsignedInteger32.h"

namespace xmas
{
namespace broker2g
{
	class SensorSettings
	{
		public:
			SensorSettings(DOMNode* flashNode, const std::string& flashlistName);

			virtual ~SensorSettings();

			const std::string& getFlashlistName();
			const std::string& getPublish();
			xdata::UnsignedInteger32T getRequests();
			void incrementRequests();
		private:
			std::string flashlistName_;
			std::string publish_;
			xdata::UnsignedInteger32T requests_;
	};
}
}
#endif

