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

#ifndef _b2in_utils_TopicSplitupIncremental_h_
#define _b2in_utils_TopicSplitupIncremental_h_

#include <map>
#include <list>

#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/exception/Exception.h"

#include "xdaq/Object.h"

#include "xdata/Properties.h"
#include "xdata/UnsignedInteger64.h"

#include "toolbox/BSem.h"
#include "toolbox/task/Timer.h"

namespace b2in 
{
	namespace utils
	{
		class TopicSplitupIncremental : public b2in::utils::MessengerCacheListener, public xdaq::Object, public toolbox::task::TimerListener
		{
			public:

			TopicSplitupIncremental (xdaq::Application * owner, const std::string & brokerURL, const std::string & networkName, toolbox::TimeInterval interval,
				std::list<std::string> & names) 
				throw(b2in::utils::exception::Exception);

			virtual ~TopicSplitupIncremental (); 

			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist);

			void update(std::list<std::string> & names);

			// Statistics information for hyperdaq visualization
			std::string getTopic(std::string & name);
			std::string getBrokerURL();
			xdata::UnsignedInteger64T getBrokerCounter();
			xdata::UnsignedInteger64T getBrokerLostCounter();
			std::string getStateName();

			protected:
			void requesting();

			bool isSynchronized();

			void sendBrokerQuery ();

			toolbox::BSem topicMutex_;
			std::list<std::string> nameList_;
			std::map<std::string, std::string> topicMap_;
			
			void asynchronousExceptionNotification(xcept::Exception& e);

			void timeExpired(toolbox::task::TimerEvent& e);

 			std::string brokerURL_;       // broker address for dynamic eventing configuration
			b2in::utils::MessengerCache * brokerMessengerCache_;

			xdata::UnsignedInteger64T brokerCounter_;
			xdata::UnsignedInteger64T brokerLostCounter_;
		};
	}
}

#endif

