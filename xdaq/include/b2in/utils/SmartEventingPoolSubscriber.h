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

#ifndef _b2in_utils_SmartEventingPoolSubscriber_h_
#define _b2in_utils_SmartEventingPoolSubscriber_h_

#include <map>
#include <set>

#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/exception/Exception.h"

#include "xdaq/Object.h"

#include "xdata/Properties.h"
#include "xdata/UnsignedInteger64.h"

#include "toolbox/BSem.h"
#include "toolbox/TimeInterval.h"
#include "toolbox/task/Timer.h"

namespace b2in 
{
	namespace utils
	{
		class SmartEventingPoolSubscriber : public xdaq::Object, public toolbox::task::TimerListener
		{
			public:

			SmartEventingPoolSubscriber (xdaq::Application * owner, const std::string & brokerURL, const std::string & defaultNetworkName, const std::string & subscribeNetworkName, toolbox::TimeInterval scanPeriod,
				toolbox::TimeInterval expirationPeriod, std::set<std::string> & topics, std::set<std::string> groups) 
				throw(b2in::utils::exception::Exception);

			virtual ~SmartEventingPoolSubscriber (); 

			void updateEventings(xdata::Properties & plist);

			void updateTopics(std::set<std::string> & topics);

			std::string getBrokerURL();
			xdata::UnsignedInteger64T getBrokerCounter();
			xdata::UnsignedInteger64T getBrokerLostCounter();

			std::set<std::string> getEventingURLs();
			xdata::UnsignedInteger64T getEventingCounter();
			xdata::UnsignedInteger64T getEventingLostCounter();

			protected:
			class BrokerAsynchronousExceptionNotification : public b2in::utils::MessengerCacheListener {
			public:
				BrokerAsynchronousExceptionNotification(b2in::utils::SmartEventingPoolSubscriber& parent) : parent_(parent)
				{
				}
				void asynchronousExceptionNotification(xcept::Exception& e);
			private:
				b2in::utils::SmartEventingPoolSubscriber& parent_;
			} brokerAsynchronousExceptionNotification_;

			class EventingAsynchronousExceptionNotification : public b2in::utils::MessengerCacheListener {
			public:
				EventingAsynchronousExceptionNotification(b2in::utils::SmartEventingPoolSubscriber& parent) : parent_(parent)
				{
				}
				void asynchronousExceptionNotification(xcept::Exception& e);
			private:
				b2in::utils::SmartEventingPoolSubscriber& parent_;
			} eventingAsynchronousExceptionNotification_;

			void requesting();

			void refreshSubscriptions ();

			void sendBrokerQuery ();

			toolbox::BSem mutex_;
			std::set<std::string> groups_;
			std::map<std::string, std::string> topicMap_;
			
			void timeExpired(toolbox::task::TimerEvent& e);

 			std::string brokerURL_;       // broker address for dynamic eventing configuration
			b2in::utils::MessengerCache * brokerMessengerCache_;
			b2in::utils::MessengerCache * eventingMessengerCache_;

			// Message counters
			xdata::UnsignedInteger64T brokerCounter_;
			xdata::UnsignedInteger64T brokerLostCounter_;
			xdata::UnsignedInteger64T subscriptionCounter_;
			xdata::UnsignedInteger64T subscriptionLostCounter_;

			//TBD eventingLostCounters ...

			std::set<std::string> eventingURLs_;
			std::map<std::string, xdata::Properties> subscriptions_; // indexed by topic (equals flashlist name)

			toolbox::TimeInterval expirationPeriod_;
		};
	}
}

#endif

