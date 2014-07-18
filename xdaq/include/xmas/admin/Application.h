// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_admin_Application_h_
#define _xmas_admin_Application_h_

#include <string>
#include <map>

#include "xdaq/Application.h" 
#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"
#include "xdata/Properties.h"
#include "xmas/admin/exception/Exception.h"
#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "b2in/nub/Method.h"
#include "b2in/utils/ServiceProxy.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/MessengerCacheListener.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/TimerEvent.h"

namespace xmas 
{
	namespace admin
	{
		class CollectorProxyErrorHandler;
		class LASProxyErrorHandler;
		class HeartbeatProxyErrorHandler;

		class Application :public xdaq::Application, 
			public xdata::ActionListener,
			public toolbox::task::TimerListener
		{
			friend class EventingCommunicationErrorHandler;

			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void clear(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void reset(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			void StatisticsTabPage(xgi::Output * out );
			
			void asynchronousExceptionNotification(xcept::Exception& e);

			protected:
				
			void timeExpired(toolbox::task::TimerEvent& event);
			void forwardRequest(xdata::Properties & plist) throw (xmas::admin::exception::Exception);


			private:


			xdata::String scanPeriod_;          // period for scanning eventings to retrieve statistics flashlists
			xdata::Boolean lasClearEnable_; // default is false, clear message is forwarded to las if true

			b2in::utils::ServiceProxy* collectorProxyXMAS_;
			b2in::utils::ServiceProxy* collectorProxyCollection_;
			b2in::utils::ServiceProxy* lasProxy_;
			b2in::utils::ServiceProxy* heartbeatProxy_;

		};

		class CollectorProxyErrorHandler: public b2in::utils::MessengerCacheListener
		{
			public:
			
			CollectorProxyErrorHandler(xmas::admin::Application* app);
			
			void asynchronousExceptionNotification(xcept::Exception& e);
			
			private:
			
			xmas::admin::Application* application_;
		};

		class LASProxyErrorHandler: public b2in::utils::MessengerCacheListener
		{
			public:
			
			LASProxyErrorHandler(xmas::admin::Application* app);
			
			void asynchronousExceptionNotification(xcept::Exception& e);
			
			private:
			
			xmas::admin::Application* application_;
		};
		class HeartbeatProxyErrorHandler: public b2in::utils::MessengerCacheListener
		{
			public:
			
			HeartbeatProxyErrorHandler(xmas::admin::Application* app);
			
			void asynchronousExceptionNotification(xcept::Exception& e);
			
			private:
			
			xmas::admin::Application* application_;
		};
	}
}
#endif

