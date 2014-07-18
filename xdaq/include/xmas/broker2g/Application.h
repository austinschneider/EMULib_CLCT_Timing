// $Id: Application.h,v 1.5 2009/02/20 13:59:25 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_Application_h_
#define _xmas_broker2g_Application_h_

#include <string>
#include <map>

#include "xdaq/Application.h" 

#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/Serializer.h"

#include "xmas/exception/Exception.h"
#include "xmas/broker2g/ModelRegistry.h"
#include "xmas/broker2g/exception/Exception.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/ServiceProxy.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/MessengerCacheListener.h"

#include "toolbox/task/TimerListener.h"

namespace xmas 
{
	namespace broker2g
	{
		class EventingCommunicationErrorHandler; // forward declaration

		class Application :public xdaq::Application, 
			public xdata::ActionListener,
			public toolbox::task::TimerListener,
			public b2in::utils::MessengerCacheListener
		{
			friend class EventingCommunicationErrorHandler;

			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			//
			// B2IN callbacks
			//
			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);
			
			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			void StatisticsTabPage(xgi::Output * out );
			
			void asynchronousExceptionNotification(xcept::Exception& e);

			protected:
				
			void displayTableToHTML( xgi::Output * out, xdata::Serializable * ) throw (xgi::exception::Exception);

			void timeExpired(toolbox::task::TimerEvent& event);

			private:

			void refreshSubscriptionsToEventing() throw (xmas::exception::Exception);

			xdata::String subscribeGroup_;      // one or more comma separated groups hosting a b2in eventing service for monitoring
			xdata::String watchdog_;            // watchdog timer for cleanup
			xdata::String scanPeriod_;          // period for scanning eventings to retrieve statistics flashlists
			xdata::String subscribeExpiration_; // expiration timeout for subscriptions to eventings
			xdata::String topics_;              // topics to subscribe to (comma separated)
			xdata::String autoloadPath_;        // path to load the broker models

			xmas::broker2g::ModelRegistry *modelRegistry_;

			std::map<std::string, xdata::Properties> subscriptions_; // indexed by topic (equals flashlist name)
			b2in::utils::ServiceProxy* b2inEventingProxyInput_;
			bool b2inEventingInputScan_;

			xdata::exdr::Serializer serializer_;

			b2in::utils::ServiceProxy* b2inBrokerProxyOutput_;
			xmas::broker2g::EventingCommunicationErrorHandler* eventingErrorHandler_;
		};

		class EventingCommunicationErrorHandler: public b2in::utils::MessengerCacheListener
		{
			public:
			virtual ~EventingCommunicationErrorHandler();

			EventingCommunicationErrorHandler(xmas::broker2g::Application* app);
			
			void asynchronousExceptionNotification(xcept::Exception& e);
			
			private:
			
			xmas::broker2g::Application* application_;
		};
	}
}
#endif

