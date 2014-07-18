/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _state_dashboard_Application_h_
#define _state_dashboard_Application_h_

#include <string>
#include <map>
#include <list>
#include <set>

#include "toolbox/ActionListener.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/UnsignedInteger64.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "ws/addressing/EndpointReference.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "state/dashboard/exception/Exception.h"

#include "xdaq/ContextTable.h"

// Identical copy to sensor objects, just change scope. Could be re-used if put in to a utils library
#include "state/dashboard/SubscriptionRegistry.h"

#include "state/dashboard/StatusNotification.h"

namespace state
{
namespace dashboard 
{
		class Application :public xdaq::Application, 
			public toolbox::ActionListener, 
			public xdata::ActionListener
		{
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed( toolbox::Event& event );

			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			void TabPanel(xgi::Input * in, xgi::Output * out );
			void JobsTabPage(xgi::Output * out, std::string group );
			
			/*! Clear exception history
			 */
			void clear(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			//
			// SOAP interface
			//
			
			//! Receive metrics from a sensor
			xoap::MessageReference notify (xoap::MessageReference msg) throw (xoap::exception::Exception);
				
			protected:
				
			// -- Temporary functions for discovery services integration --
			//		
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);
							
			// Returns a subscription id in UUID format as a string
			//
			std::string subscribeToWSEventing( xdaq::ApplicationDescriptor* d )
				throw (state::dashboard::exception::Exception);
				
			void renewSubscriptionToWSEventing(xdaq::ApplicationDescriptor * d, const std::string & uuid) 
				throw (state::dashboard::exception::Exception);
				
			
			void refreshSubscriptionsToWSEventing() throw (state::dashboard::exception::Exception);

			//
			// -- Temporary functions for discovery services integration --
			
			std::list<xdaq::ApplicationDescriptorImpl> getWSEventingServices(std::set<std::string>& groups);			
			
			private:

			std::map<std::string, state::dashboard::StatusNotification > notifications_; // ordered by time 
			std::set<std::string> groups_;
						
			xdata::Boolean useDiscovery_; // indicates if discovery services are used, default is true
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for exceptions
			
			// Support for discovery service
			std::list<xdaq::ApplicationDescriptor*> wsEventingServices_; // temporary
			xdaq::ContextTable discoveredContexts_; // temporary
			state::dashboard::SubscriptionRegistry subscriptions_;
			toolbox::BSem discoveryLock_;
			toolbox::BSem repositoryLock_;
			
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			xdata::UnsignedInteger64T exceptionsLostCounter_;
//			toolbox::Properties settings_;		
		};
}
}

#endif

