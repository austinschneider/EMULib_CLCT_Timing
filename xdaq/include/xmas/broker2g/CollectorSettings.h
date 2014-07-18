/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_CollectorSettings_h_
#define _xmas_broker2g_CollectorSettings_h_

#include <string>
#include <map>

#include "xmas/broker2g/Utils.h"

#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"

namespace xmas
{
namespace broker2g
{
	class CollectorSettings
	{
		public:
			CollectorSettings(DOMNode* flashNode, const std::string& flashlistName);

			virtual ~CollectorSettings();

			const std::string& getFlashlistName();
			const std::string& getPublish();
			const std::string& getSubscribe();
			const std::string& getHashKey();
			const std::string& getFlush();
			const std::string& getClear();
			const toolbox::TimeVal& getExpires();
			const std::string& getCollectorAddress();

			bool isExpired();
			void setExpires(const toolbox::TimeInterval& value);
			void setCollectorAddress(const std::string& value);
		private:
			std::string flashlistName_;
			std::string publish_;
			std::string subscribe_;
			std::string hashkey_;
			std::string flush_;
			std::string clear_;
			toolbox::TimeVal expires_;
			std::string collectorAddress_;
	};
}
}
#endif

