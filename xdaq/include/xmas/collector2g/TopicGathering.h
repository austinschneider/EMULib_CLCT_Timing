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

#ifndef _xmas_collector2g_TopicGathering_h_
#define _xmas_collector2g_TopicGathering_h_

#include <map>
#include <list>

#include "xdaq/Object.h"

#include "xdata/Properties.h"
#include "xdata/UnsignedInteger64.h"

#include "toolbox/BSem.h"
#include "toolbox/task/Timer.h"

#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/MessengerCacheListener.h"
#include "xmas/collector2g/exception/Exception.h"

#include "xmas/collector2g/Topic.h"

namespace xmas 
{
	namespace collector2g
	{
		class TopicGathering : public b2in::utils::MessengerCacheListener, public xdaq::Object, public toolbox::task::TimerListener
		{
			public:

			TopicGathering (xdaq::Application * owner, const std::string & brokerURL, const std::string & networkName, toolbox::TimeInterval interval) 
				throw(xmas::collector2g::exception::Exception);

			virtual ~TopicGathering ()
				throw();

			void update (xdata::Properties & plist)
				throw();


			// Statistics information for hyperdaq visualization
			xmas::collector2g::Topic getAssignedTopic() 
				throw(xmas::collector2g::exception::Exception);

			std::string getBrokerURL()
				throw();
			xdata::UnsignedInteger64T getBrokerCounter()
				throw();
			xdata::UnsignedInteger64T getBrokerLostCounter()
				throw();
			std::string getStateName()
				throw();

			protected:
			void requesting()
				throw();
  			bool isSynchronized()
				throw();

			void sendBrokerQuery ()
				throw();

			toolbox::BSem topicMutex_;
			
			void asynchronousExceptionNotification(xcept::Exception& e)
				throw();

			void timeExpired(toolbox::task::TimerEvent& e)
				throw();

			toolbox::TimeInterval scanPeriod_;
 			std::string brokerURL_;       // broker address for dynamic eventing configuration
			xmas::collector2g::Topic  * topic_;
			b2in::utils::MessengerCache * brokerMessengerCache_;

			xdata::UnsignedInteger64T brokerCounter_;
			xdata::UnsignedInteger64T brokerLostCounter_;
			
		};
	}
}

#endif

