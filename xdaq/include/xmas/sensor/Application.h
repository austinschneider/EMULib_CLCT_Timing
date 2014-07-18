// $Id: Application.h,v 1.43 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_Application_h_
#define _xmas_sensor_Application_h_

#include <string>
#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/Serializer.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

/*
#include "ws/eventing/MemoryStorageAdapter.h"
#include "ws/eventing/SubscriptionManagerService.h"
#include "ws/eventing/NotificationManagerService.h"
#include "ws/eventing/PeerTransportService.h"
*/

#include "ws/addressing/EndpointReference.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "xmas/exception/Exception.h"
#include "xmas/sensor/FlashListMonitorRegistry.h"
#include "xmas/sensor/MetricsScheduler.h"
#include "xmas/sensor/MonitorReportEvent.h"
#include "xmas/sensor/soap/MonitorReportSerializer.h"

#include "xmas/sensor/exception/DuplicateConsumer.h"
#include "xmas/sensor/exception/ConsumerNotFound.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"
#include "xdaq/ContextTable.h"
// easy life with ws-eventing
#include "ws/utils/WSEventingProxy.h"
// remember discovered applications
#include "xplore/utils/DescriptorsCache.h"

#include "ws/broker/utils/BrokerCache.h"

namespace xmas 
{
	namespace sensor 
	{
		class Application
			:public xdaq::Application, 
			 public toolbox::ActionListener, 
			 public xdata::ActionListener,
			 public toolbox::task::TimerListener
		{
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed( toolbox::Event& event );
			void timeExpired(toolbox::task::TimerEvent& e);
			
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void browseSelection(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

				
			//! Create SOAP message from MonitorReport with SOAP tag <name>
			//
			// xoap::MessageReference createMessage (MonitorReport & report, const std::string& name) throw (xmas::exception::Exception);
			
			//! Post report for sending to EndpointReference
			//
			// void post (MonitorReport & report) throw (xmas::exception::Exception);
			
			
			
			// SOAP interface
			//
			
			//! Install a monitor setting
			//
			xoap::MessageReference install (xoap::MessageReference msg) throw (xoap::exception::Exception);

			//! Uninstall a previously installed setting, identified by flashlist
			//
			xoap::MessageReference uninstall (xoap::MessageReference msg) throw (xoap::exception::Exception);

			//! Remove all settings and flashlist definitions
			//
			xoap::MessageReference reset (xoap::MessageReference msg) throw (xoap::exception::Exception);

			//! Low level data retrieve for a single flashlist, get data identified by group and/or flashlist through a specified sampler
			//
			xoap::MessageReference fetch (xoap::MessageReference msg) throw (xoap::exception::Exception);

			//! Retrieve collected data for a given flashlist
			//
			xoap::MessageReference retrieve (xoap::MessageReference msg) throw (xoap::exception::Exception);

			//! Pulse the sensor for a group and/or flashlist together with a specification of the publisher to send the data
			/*!
				<Pulse burst="10" frequency="1" interval=60 tag="a,b,c" flashlist="urn:xdaq-flashlist:name">
					<publisher type="type name"/>
					...
				</Pulse>
			*/
			xoap::MessageReference pulse (xoap::MessageReference msg) throw (xoap::exception::Exception);
			
			//! Receive metrics from a sensor
			xoap::MessageReference report (xoap::MessageReference msg) throw (xoap::exception::Exception);
				
			protected:
			
			void FlashlistsTabPage( xgi::Output * out );
			void StatisticsTabPage( xgi::Output * out );
			void InfospacesTabPage( xgi::Output * out );
			void TabPanel( xgi::Output * out );

				
			// -- Temporary functions for discovery services integration --
			//		
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);
				
			void subscribeToWSEventing() throw (xmas::sensor::exception::Exception);
			
			// Returns a subscription id in UUID format as a string
			//
			std::string subscribeFlashListToWSEventing(const std::string& name, xdaq::ApplicationDescriptor* d )
				throw (xmas::sensor::exception::Exception);
				
			void renewFlashListSubscriptionToWSEventing(xdaq::ApplicationDescriptor * d, const std::string & uuid) 
				throw (xmas::sensor::exception::Exception);
				
			void discoveryLock();			
			
			void discoveryUnlock();
			
			void refreshWSEventingSubscriptions() throw (xmas::sensor::exception::Exception);

			//
			// -- Temporary functions for discovery services integration --
			
			std::list<xdaq::ApplicationDescriptorImpl> getWSEventingServices(std::set<std::string>& groups);
			
			// Erase a WS-Eventing application descriptor from the temporary, application local cache
			//
			void eraseWSEventingService (xdaq::ApplicationDescriptorImpl& descriptor);

			private:
			void heartbeat();
			void subscription();
			void publishReport(xmas::sensor::MonitorReportEvent & report);

			std::set<std::string> scanLocalServices();
			void applySensorSettings(const std::string & path);

			void processPulse (xoap::MessageReference msg) throw (xmas::sensor::exception::Exception);
			void processReport (xoap::MessageReference msg, size_t maxRetry) throw (xmas::sensor::exception::Exception);

			
			void displayTableToCSV( xdata::Table*  table );
			
			// Schedule a remote query of the WS-Broker 
			//
			void queryWSBroker(const std::string& group);

			
			xdata::Boolean useDiscovery_; // indicates if discovery services are used, default is true
			xdata::Vector<xdata::String> settingsURLs_; // path pattern for configuration file
			xdata::Boolean useBroker_; // indicates if broker is used for publishing to ws-eventings
			xdata::String brokerGroup_; // indicates the group the broker is running in
			xdata::String brokerProfile_; // indicates the profile to use for retrieving the services from the broker
			
			xmas::sensor::FlashListMonitorRegistry flashListMonitorRegistry_;
			xmas::sensor::MetricsScheduler scheduler_;
			
			// Support for discovery service
			
			// List how many ws-eventing services were found per group to which we belong
			std::map<std::string, size_t> discoveredWSEventingServices_;
			
			std::list<xdaq::ApplicationDescriptor*> wsEventingServices_; // temporary
			xdaq::ContextTable discoveredContexts_; // temporary
			toolbox::BSem discoveryLock_;
			
			class Routing
			{
				public:
				
				void registerFields(xdata::Bag<Routing>* bag)
				{
					bag->addField ("tag", &tag);
					bag->addField ("group", &group);
				}
				
				xdata::String tag;
				xdata::String group;
			};
			
			xdata::Vector< xdata::Bag<Routing> > collectRouting_;
			xdata::Vector< xdata::Bag<Routing> > publishRouting_;
			xdata::Boolean autoConfigure_;
			xdata::String autoConfSearchPath_;
			xdata::String subscriptionTag_;
			toolbox::task::AsynchronousEventDispatcher dispatcher_;

			bool verbose_; // print out info message if not WS-Eventing service found
			
			
			xdata::UnsignedInteger64T incomingReportCounter_ ;    
  			xdata::UnsignedInteger64T outgoingReportCounter_ ;    
  			xdata::UnsignedInteger64T incomingReportLostCounter_ ;
  			xdata::UnsignedInteger64T outgoingReportLostCounter_ ;
  			xdata::UnsignedInteger64T incomingPulseCounter_ ;     
  			xdata::UnsignedInteger64T pulseLostCounter_;	
			
			// cgi
			std::string selectedInfoSpace_; // remember last selected InfoSpace in combo box
			std::vector<std::string> monitorableSearchModes_; // the possible search modes (startsWith, endsWith, contains)
			std::string selectedFlashList_; // remember last selected FlashList in combo box
			std::string selectedMonitorableSearchMode_; // last selected search mode
			std::string  selectedMonitorableSearchString_;
			xdata::UnsignedInteger32  lossReportCounter_; // only print send errors every (msg % lossReportCounter) = 1		
			bool queryBroker_; // flag set if the WS-Broker needs to be queried remotely
			
			xplore::utils::DescriptorsCache descriptorsCache_;
			ws::utils::WSEventingProxy wsEventingProxy_;
			bool discoveryActive_;
			xdata::exdr::Serializer serializer_;
            		xmas::sensor::soap::MonitorReportSerializer monitorSerializer_;

			ws::broker::utils::BrokerCache brokerCache_;
			toolbox::BSem queryBrokerMutex_; // protects variable queryBroker_
		};
	}
}
#endif
