// $Id: Application.h,v 1.14 2008/11/14 14:35:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensord_Application_h_
#define _xmas_sensord_Application_h_

#include <string>
#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Double.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/Serializer.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "xmas/PulserSettings.h"
#include "xmas/exception/Exception.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/mem/Pool.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/EventingDialup.h"
#include "b2in/utils/TopicSplitupIncremental.h"
#include "b2in/utils/Statistics.h"

namespace xmas 
{
	namespace sensord
	{
		class BrokerCommunicationErrorHandler; // forward declaration
	
		class Application
			:public xdaq::Application, 
			 public toolbox::ActionListener, 
			 public xdata::ActionListener
		{
			friend class BrokerCommunicationErrorHandler;
		
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed( toolbox::Event& event );
			void timeExpired(toolbox::task::TimerEvent& e);

			
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
				
			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist)
				throw (b2in::nub::exception::Exception);

			void queryBroker ();

			void publishReport (toolbox::mem::Reference *  msg, xdata::Properties & plist);
			void publishHeartbeat (toolbox::mem::Reference *  msg,xdata::Properties & plist);



					
			protected:
			
			void StatisticsTabPage( xgi::Output * out );
			void TabPanel( xgi::Output * out );

			private:


			void applySensorSettings(const std::string & path);

			xdata::Boolean useBroker_; // indicates if broker is used for publishing to ws-eventings
			xdata::String brokerGroup_; // indicates the group the broker is running in
			xdata::String brokerURL_; // setting a broker URL avoids the use of service discovery for searching the broker
			xdata::String brokerProfile_; // indicates the profile to use for retrieving the services from the broker
			xdata::String brokerDialupWatchdog_;
			xdata::String brokerTopicsWatchdog_;
			xdata::String eventingURL_;
			xdata::String autoConfSearchPath_;
			
						
			xdata::String publishGroup_;
			
			
			xdata::UnsignedInteger32  lossReportCounter_; // only print send errors every (msg % lossReportCounter) = 1		
			
			xdata::exdr::Serializer serializer_;
			toolbox::mem::Pool* pool_;
			
			bool deadBand_;
			xdata::Double committedPoolSize_;
			xdata::Double highThreshold_;
			xdata::Double lowThreshold_;
			xdata::UnsignedInteger32 maxReportMessageSize_;

			b2in::utils::EventingDialup * dialup_;
			b2in::utils::TopicSplitupIncremental * splitup_;

			std::list<std::string> flashlists_;
			std::map<std::string, b2in::utils::Statistics> counters_;
			xdata::UnsignedInteger64 heartbeatInternalLossCounter_;
			xdata::UnsignedInteger64 heartbeatEnqueuedCounter_;
			xdata::UnsignedInteger64 heartbeatNoNetworkLossCounter_;
			xdata::UnsignedInteger64  heartbeatIncomingCounter_;
		};
	}
}
#endif
