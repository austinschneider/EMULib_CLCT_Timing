// $Id: Application.h,v 1.2 2008/07/18 15:27:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_broker_Application_h_
#define _ws_broker_Application_h_

#include <string>
#include <map>

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
#include "xmas/exception/Exception.h"

#include "xdaq/ContextTable.h"

// Identical copy to sensor objects, just change scope. They could be re-used in both if put in to a utils library
#include "ws/broker/SubscriptionRegistry.h"

#include "ws/broker/utils/ModelRegistry.h"

namespace ws 
{
	namespace broker 
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
			
			void displayModelToHTML( xgi::Output * out,  std::string& model, const std::string & expand )
				throw (ws::broker::exception::Exception);			

			void view(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
	
			void TabPanel(xgi::Output * out );
			void SettingsTabPage(xgi::Output * out );
			void ModelsTabPage(xgi::Output * out );
			
			/*! Apply settings:
			 */
			void applySettings(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			/*! Clear exception history
			 */
			void clear(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			//
			// SOAP interface
			//
			
			//! Receive metrics from a sensor
			xoap::MessageReference report (xoap::MessageReference msg) throw (xoap::exception::Exception);
				
			//! Broker interface
			xoap::MessageReference getProfiles (xoap::MessageReference msg) throw (xoap::exception::Exception);
			xoap::MessageReference select (xoap::MessageReference msg) throw (xoap::exception::Exception);
				
			protected:
				
			// -- Temporary functions for discovery services integration --
			//		
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);
							
			// Returns a subscription id in UUID format as a string
			//
			std::string subscribeToWSEventing( xdaq::ApplicationDescriptor* d )
				throw (ws::broker::exception::Exception);
				
			void renewSubscriptionToWSEventing(xdaq::ApplicationDescriptor * d, const std::string & uuid) 
				throw (ws::broker::exception::Exception);
				
			
			void refreshSubscriptionsToWSEventing() throw (ws::broker::exception::Exception);

			//
			// -- Temporary functions for discovery services integration --
			
			std::list<xdaq::ApplicationDescriptorImpl> getWSEventingServices(std::set<std::string>& groups);
			
			void displayTableToHTML( xgi::Output * out, xdata::Serializable * ) throw (xgi::exception::Exception);

			private:

			xdata::Boolean useDiscovery_; // indicates if discovery services are used, default is true
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for monitoring
			xdata::String watchdog_; // watchdog timer for cleanup
			
			// Support for discovery service
			std::list<xdaq::ApplicationDescriptor*> wsEventingServices_; // temporary
			xdaq::ContextTable discoveredContexts_; // temporary
			ws::broker::SubscriptionRegistry subscriptions_;
			toolbox::BSem discoveryLock_;
			toolbox::BSem repositoryLock_;
			
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			xdata::UnsignedInteger64T reportLostCounter_;
			toolbox::Properties settings_;

			ws::broker::utils::ModelRegistry *modelRegistry;
		};
	}
}
#endif
