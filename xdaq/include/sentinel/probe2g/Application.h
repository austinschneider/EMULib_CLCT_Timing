/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_probe2g_Application_h_
#define _sentinel_probe2g_Application_h_

#include <string>
#include <stack>
#include <set>
#include <map>

#include "xdata/Boolean.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/Double.h"
#include "xdata/TimeVal.h"
#include "xdata/ActionListener.h"
#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ContextTable.h"
#include "xdaq/ApplicationContext.h" 
#include "xdaq/ApplicationDescriptorImpl.h"

#include "toolbox/ActionListener.h"
#include "toolbox/fsm/AsynchronousFiniteStateMachine.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/TimerFactory.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

#include "b2in/nub/exception/Exception.h"
#include "b2in/utils/MessengerCache.h"

#include "b2in/utils/EventingDialup.h"

#include "sentinel/probe2g/exception/Exception.h"

namespace sentinel
{
namespace probe2g
{
	class Application: 
		public xdaq::Application, 
		public toolbox::ActionListener, 
		public xdata::ActionListener,
		public toolbox::task::TimerListener
	{
		public:

		XDAQ_INSTANTIATOR();


		Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);

		~Application();

		/*! Callback to be implemented when discovery service comes back with a xplore::DiscoveryEvent
		*/
		void actionPerformed(toolbox::Event& event);

		/*! Callback to be implemented for receiving default parameter setting
		*/
		void actionPerformed (xdata::Event& e);

		void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
		void view(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
		void inject(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

		void TabPanel(xgi::Output * out );
		void ExceptionsTabPage(xgi::Output * out );
		void StatisticsTabPage(xgi::Output * out );

		void publishEvent (const std::string & command, xcept::Exception& e) 
			throw (sentinel::probe2g::exception::Exception);

		bool handleException(xcept::Exception& ex, void* context);

		void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) 
			throw (b2in::nub::exception::Exception);

		protected:
		
		void timeExpired(toolbox::task::TimerEvent& e);

		// Exported variables
		xdata::String watchdog_;       // an interval for a watchdog to deliver exceptions
		xdata::Double committedPoolSize_;
 		xdata::UnsignedInteger32 maxExceptionMessageSize_;
		xdata::String brokerWatchdog_;	// watchdog for running the broker re-negotiation
		xdata::String brokerURL_;	// broker address for dynamic eventing configuration
 		xdata::String publishGroup_;	// group the b2in-eventing for reporting
		xdata::String eventingURL_;	// static eventing address configuration

		//! lock for the alarm, revoke and exception queues and infospaces
		toolbox::BSem repositoryLock_;
		//! infospace for receiving alarms from applications
		xdata::InfoSpace* alarms_;
		//! queue for exceptions to be sent out
		std::list<std::pair<xcept::Exception, size_t> > exceptions_;
		//! queue for revokes to send out
		std::list<xcept::Exception> revokes_;

  		toolbox::mem::Pool* pool_;

		// eventing negotiation with broker
		b2in::utils::EventingDialup * dialup_;

		void processPendingEvents ();
	};
}
}

#endif

