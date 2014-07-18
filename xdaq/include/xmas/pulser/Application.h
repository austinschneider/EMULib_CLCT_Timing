// $Id: Application.h,v 1.14 2008/07/18 15:28:27 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_pulser_Application_h_
#define _xmas_pulser_Application_h_

#include <string>

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdata/UnsignedInteger64.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Integer32.h"
#include "xdata/ActionListener.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"


#include "ws/addressing/EndpointReference.h"

// easy life with ws-eventing
#include "ws/utils/WSEventingProxy.h"
#include "ws/utils/SubscriptionRegistry.h"
// remember discovered applications
#include "xplore/utils/DescriptorsCache.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "xmas/exception/Exception.h"
#include "xmas/pulser/exception/Exception.h"
#include "xmas/PulserSettings.h"
#include "toolbox/BSem.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"

namespace xmas 
{
	namespace pulser 
	{
		class Application : 
			 public xdaq::Application, 
			 public toolbox::ActionListener,
 			 public toolbox::task::TimerListener,
			 public xdata::ActionListener
		{
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed( toolbox::Event& event );
			
			void timeExpired( toolbox::task::TimerEvent& e );

			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void retrieveHeartbeatTable(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

					
			/*! CGI form callback for pulser settings			    
			*/
			void applySettings(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			/*! Activate pulser events by name or uuid in format
				<activate>
					<event name="<NAME>"/>
					...
					<event uuid="<UUID>"/>
					...
				</activate>
			*/
			xoap::MessageReference activate (xoap::MessageReference msg) throw (xoap::exception::Exception);
			
			/*! Dectivate pulser events by name or uuid in format
				<deactivate>
					<event name="<NAME>"/>
					...
					<event uuid="<UUID>"/>
					...
				</deactivate>
			*/
			xoap::MessageReference deactivate (xoap::MessageReference msg) throw (xoap::exception::Exception);	
			
			// from xmas::sensor through ws-eventing subscription				
			xoap::MessageReference heartbeat (xoap::MessageReference msg) throw (xoap::exception::Exception);				
							

			protected:

		
			void loadPulserEvents(const std::string& path)
				throw (xmas::pulser::exception::Exception);
				
			// -- Temporary functions for discovery services integration --
			//
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);						
			void discoveryLock();			
			void discoveryUnlock();			
			
			//
			// -- Temporary functions for discovery services integration --
			//			
						
			//! Receive a list of all discovered sensor applications in the group
			//
			std::list<xdaq::ApplicationDescriptorImpl> getDestinations();
			void removeDestination(xdaq::ApplicationDescriptor & d);
			void addDestination(toolbox::Properties & p);

			private:
			
			// HyperDAQ page with overview information table
			//
			void TabPanel( xgi::Output * out );
			void PulseEventsTabPage( xgi::Output * out );
			void StatisticsTabPage( xgi::Output * out );
			void SensorsTabPage( xgi::Output * out );

			//! Helpers function to check if heartbeat older than heartbeatTimeout_
			//  Remove descriptor and return false, otherwise return true
			//
			bool validateDescriptorHeartbeat(const std::string& uuid);
			
			//! Set the attribute "enabled" of an event identified by a uuid \param event to "true" or "false"
			//
			void setPulseEventEnabled(const std::string& event, const std::string& enabled)
				throw (xmas::exception::Exception);
			
			xdata::Boolean useDiscovery_; // indicates if discovery services are used, default is true
			xdata::Vector<xdata::String> settingsURLs_;
			xdata::String inputProfile_; // configuration file
			xmas::PulserSettings settings_;

			//			
			std::list<xdaq::ApplicationDescriptor*> discoveredDestinations_; // temporary
			xdaq::ContextTable discoveredContexts_; // temporary
			toolbox::BSem discoveryLock_;
			xdata::UnsignedInteger64T pulseLostCounter_;
			
			xplore::utils::DescriptorsCache descriptorsCache_;
			ws::utils::WSEventingProxy wsEventingProxy_;
			std::map<std::string, toolbox::TimeVal> heartbeatTimestamps_;
			xdata::Integer32 heartbeatTimeout_; // in seconds
		};
	}
}
#endif
