// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_Topic_h_
#define _xmas_collector2g_Topic_h_

#include <set>
#include <string>
#include "toolbox/TimeInterval.h"

namespace xmas 
{
	namespace collector2g
	{
		class Topic
                {
			public:

			bool operator==(const xmas::collector2g::Topic &other) const;
			bool operator!=(const xmas::collector2g::Topic &other) const;

			std::string getPublishTopic();
			std::string getSubscribeTopic();
			std::string getFlashlistName();
			std::set<std::string> getHashKey();
			toolbox::TimeInterval getStagingPeriod(); 
			bool getAutoClear();

			std::string publishTopicName_;
			std::string subscribeTopicName_;
			std::string flashlistName_;
			std::set<std::string> hashKey_;
			toolbox::TimeInterval stagingPeriod_;
			bool autoClear_;
			
		};

	}
}

#endif

