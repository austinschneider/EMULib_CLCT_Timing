// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_SmartEventingDialup_h_
#define _b2in_utils_SmartEventingDialup_h_

#include <vector>
#include <map>
#include <string>

#include "xdaq/Object.h"
#include "xdata/Properties.h"
#include "xdata/UnsignedInteger64.h"

#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "b2in/utils/exception/Exception.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/MessengerCacheListener.h"

#include "toolbox/BSem.h"
#include "toolbox/TimeVal.h"
#include "toolbox/lang/Class.h"
#include "toolbox/exception/Handler.h"
#include "toolbox/task/Timer.h"
#include "toolbox/fsm/AsynchronousFiniteStateMachine.h"
#include "b2in/nub/exception/InternalError.h"
#include "b2in/nub/exception/QueueFull.h"
#include "b2in/nub/exception/OverThreshold.h"

namespace b2in 
{
	namespace utils
	{
		class SmartEventingDialup: public xdaq::Object, public toolbox::task::TimerListener
	 	{

			public:

			SmartEventingDialup (xdaq::Application * owner, const std::string & publishGroup, const std::string & brokerURL,
				const std::string & eventingURL, const std::string & networkName, toolbox::TimeInterval interval) 
				throw(b2in::utils::exception::Exception);

			virtual ~SmartEventingDialup (); 

			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist);

			//!
			//
			bool isEstablished ();

			//!
			//
			void send (toolbox::mem::Reference* msg, xdata::Properties & plist) 
				throw (b2in::utils::exception::Exception);
				
			std::string getEventingURL();
			std::string getBrokerURL();
			xdata::UnsignedInteger64T getOutgoingReportCounter();
			xdata::UnsignedInteger64T getOutgoingReportLostCounter();
			xdata::UnsignedInteger64T getBrokerCounter();
			xdata::UnsignedInteger64T getBrokerLostCounter();
			std::string getStateName();

			protected:
			class BrokerAsynchronousExceptionNotification : public b2in::utils::MessengerCacheListener {
			public:
				BrokerAsynchronousExceptionNotification(b2in::utils::SmartEventingDialup& parent) : parent_(parent)
				{
				}

				virtual ~BrokerAsynchronousExceptionNotification();

				void asynchronousExceptionNotification(xcept::Exception& e);
			private:
				b2in::utils::SmartEventingDialup& parent_;
			} brokerAsynchronousExceptionNotification_;

			class EventingAsynchronousExceptionNotification : public b2in::utils::MessengerCacheListener {
			public:
				EventingAsynchronousExceptionNotification(b2in::utils::SmartEventingDialup& parent) : parent_(parent)
				{
				}

				virtual ~EventingAsynchronousExceptionNotification();

				void asynchronousExceptionNotification(xcept::Exception& e);
			private:
				b2in::utils::SmartEventingDialup& parent_;
			} eventingAsynchronousExceptionNotification_;

			void negociate(const std::string & url);
			std::string findEndpointURL(const std::string & context, const  std::string & network)
         			throw (b2in::utils::exception::Exception);


			void timeExpired(toolbox::task::TimerEvent& e);

			// Finite State Machine for broker negociation
 			void connecting (toolbox::fsm::FiniteStateMachine& fsm) throw (toolbox::fsm::exception::Exception);
                	void negociating (toolbox::fsm::FiniteStateMachine& fsm) throw (toolbox::fsm::exception::Exception);
                	void ignore (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
  			void setEventingURL (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
                	void hangup (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
			void failAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);


      			std::string eventing_;
                	xdata::UnsignedInteger64T outgoingReportCounter_ ;
                	xdata::UnsignedInteger64T outgoingReportLostCounter_ ;
                	xdata::UnsignedInteger64T brokerCounter_;
                	xdata::UnsignedInteger64T brokerLostCounter_;

 			std::string brokerURL_;       // broker address for dynamic eventing configuration
                	std::string publishGroup_;    // group the b2in-eventing for reporting
	                std::string eventingURL_;     // static eventing address configuration
			std::string networkName_;     // network for destination endpoint (b2in-eventing)

			b2in::utils::MessengerCache * brokerMessengerCache_;
			b2in::utils::MessengerCache * eventingMessengerCache_;

			toolbox::fsm::AsynchronousFiniteStateMachine fsm_;
		};
	}
}

#endif

