/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_bridge2g_Application_h_
#define _sentinel_bridge2g_Application_h_

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

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

#include "sentinel/bridge2g/exception/Exception.h"

#include "xoap/SOAPMessage.h"

#include "b2in/nub/exception/Exception.h"
#include "b2in/utils/EventingDialup.h"
#include "b2in/utils/Statistics.h"

namespace sentinel
{
namespace bridge2g
{
	class Application: 
		public xdaq::Application, 
		public toolbox::ActionListener,
		public xdata::ActionListener
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

		void publishEvent (const std::string & command, xcept::Exception& e) 
			throw (sentinel::bridge2g::exception::Exception);

		/*! CGI callback */
		void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
		void StatisticsTabPage(xgi::Output * out) throw (xgi::exception::Exception);

		/*! SOAP callback */
		xoap::MessageReference notify(xoap::MessageReference msg) throw (xoap::exception::Exception);
		xoap::MessageReference revoke(xoap::MessageReference msg) throw (xoap::exception::Exception);

		/*! B2IN callback */
		void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) 
			throw (b2in::nub::exception::Exception);

		protected:
		
		// Exported variables
		xdata::Double committedPoolSize_;
 		xdata::UnsignedInteger32 maxExceptionMessageSize_;
		xdata::String brokerWatchdog_;	// watchdog for running the broker re-negotiation
		xdata::String brokerURL_;	// broker address for dynamic eventing configuration
 		xdata::String publishGroup_;	// group the b2in-eventing for reporting
		xdata::String eventingURL_;	// static eventing address configuration

  		toolbox::mem::Pool* pool_;

		// eventing negotiation with broker
		b2in::utils::EventingDialup * dialup_;

		b2in::utils::Statistics statistics_;
	};
}
}

#endif

