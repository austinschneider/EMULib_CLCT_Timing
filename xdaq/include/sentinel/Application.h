// $Id: Application.h,v 1.11 2009/04/06 13:44:55 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_Application_h_
#define _sentinel_Application_h_

#include <string>
#include <stack>
#include <set>
#include <map>

#include "xdata/Boolean.h"
#include "xdata/TimeVal.h"
#include "xdata/ActionListener.h"
#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ContextTable.h"
#include "xdaq/ApplicationContext.h" 
#include "xdaq/ApplicationDescriptorImpl.h"
#include "xoap/exception/Exception.h"
#include "xoap/MessageReference.h" 
#include "toolbox/ActionListener.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/TimerFactory.h"
#include "sentinel/exception/Exception.h"
#include "xplore/Advertisement.h"
#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "sentinel/SubscriptionRegistry.h"

namespace sentinel
{
	const size_t MaxNumberOfRetry = 10;
	
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

		void TabPanel(xgi::Output * out );
		void ExceptionsTabPage(xgi::Output * out );

		//! Send a sentinel news article in SOAP format to a WS-Eventing in group 'exception'
		//
		void news (toolbox::Properties& article) 
			throw (sentinel::exception::Exception);

		void notify (const std::string & command, xcept::Exception& e) 
			throw (sentinel::exception::Exception);

		xoap::MessageReference notify (xoap::MessageReference msg) throw (xoap::exception::Exception);

		void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);

		bool handleException(xcept::Exception& ex, void* context);

		protected:
		
		void timeExpired(toolbox::task::TimerEvent& e);

		void renewSubscriptionToWSEventing(xdaq::ApplicationDescriptor * d, const std::string & uuid) 
			throw (sentinel::exception::Exception);

		void refreshSubscriptionsToWSEventing() 
			throw (sentinel::exception::Exception);

		std::string subscribeToWSEventing (xdaq::ApplicationDescriptor* d ) 
			throw (sentinel::exception::Exception);
			
		std::list<xdaq::ApplicationDescriptorImpl>  getWSEventingServices(std::set<std::string>& groups);

		// Exported variables
		xdata::Boolean useDiscovery_; // default is true
		xdata::String eventingURL_; // setting a eventing URL avoids the use of service discovery for searching the eventing for the error reporting

		sentinel::SubscriptionRegistry subscriptions_;
		std::list<xdaq::ApplicationDescriptor*> wsEventingServices_; // temporary
		xdaq::ContextTable discoveredContexts_; // temporary
		toolbox::BSem discoveryLock_;

		xdata::String collectRouting_; // tells from which ws-eventing to accept messages for relaying
		xdata::String publishRouting_; // tells to which ws-eventing to publish to
		xdata::String watchdog_;       // an interval for a watchdog to deliver exceptions
		
		std::list<std::pair<xcept::Exception, size_t> > exceptions_;
		toolbox::BSem repositoryLock_;
		size_t retry_;	

		bool discoveryActive_;
		xdata::InfoSpace* alarms_; // infospace for receiving alarms from applications
	};
}
#endif
