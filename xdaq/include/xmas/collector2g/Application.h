// $Id: Application.h,v 1.9 2009/02/20 14:02:17 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_Application_h_
#define _xmas_collector2g_Application_h_

#include <string>
#include <map>

#include "toolbox/TimeVal.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/task/TimerTask.h"
#include "toolbox/task/Timer.h"
#include "toolbox/task/TimerFactory.h"

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Table.h"
#include "xdata/Double.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/FixedSizeInputStreamBuffer.h"
#include "xdata/exdr/FixedSizeOutputStreamBuffer.h"
#include "xdata/exdr/Serializer.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/EventingDialup.h"
#include "b2in/utils/SmartEventingPoolSubscriber.h"

#include "xmas/exception/Exception.h"
#include "xmas/collector2g/Collector.h"
#include "xmas/collector2g/TopicGathering.h"
#include "xmas/collector2g/exception/Exception.h"

#include "xdaq/ContextTable.h"

namespace xmas 
{
	namespace collector2g
	{
		class Application :
		public xdaq::Application, 
		public toolbox::ActionListener,
		public xdata::ActionListener,
		public toolbox::task::TimerListener
		{
		public:
			
			XDAQ_INSTANTIATOR();
			
			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();
			
			void actionPerformed(xdata::Event& e);
			
			void actionPerformed(toolbox::Event& e);			
			
			//
			// B2IN Interface
			//
			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);
			void protocolStackReceive (toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);
			
			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			void FlashlistsTabPage( xgi::Output * out );
			void StatisticsTabPage( xgi::Output * out );
			void CollectorTabPage( xgi::Output * out );
			void TabPanel( xgi::Output * out );

		protected:
			
			void publishCollectedData();

			void timeExpired(toolbox::task::TimerEvent& event);
			
		private:
			xdata::String subscribeGroup_;	// one or more comma separated groups hosting a b2in-eventing service for monitoring
			xdata::String publishGroup_;	// one or more comma separated groups hosting a b2in-eventing service for monitoring
			xdata::String subscribeBrokerURL_; // indicates the b2in address of the broker, for subscription
			xdata::String publishBrokerURL_; // indicates the b2in address of the broker, for notification
			xdata::String subscribeNetworkName_; // network use to subscribe to eventing pool , as broker default network 
			
			xdata::String brokerWatchdog_;
			xdata::String stagePeriod_;
			xdata::String subscribeExpiration_;
			
			xdata::UnsignedInteger64T outgoingReportLostCounter_;
			xdata::UnsignedInteger64T outgoingReportCounter_;

			xdata::Double committedPoolSize_;
			toolbox::BSem repositoryLock_;
			
			xdata::exdr::Serializer serializer_;
			xmas::collector2g::Collector * collector_;
			xdata::UnsignedInteger32 maxTableSize_; // in bytes
			toolbox::mem::Pool* pool_;
			
			b2in::utils::EventingDialup * dialup_;
			b2in::utils::SmartEventingPoolSubscriber * eventingPoolSubscriber_;
			xmas::collector2g::TopicGathering * topicGathering_;
		};
	}
}

#endif

