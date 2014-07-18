// $Id: Application.h,v 1.14 2008/07/18 15:28:23 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las_Application_h_
#define _xmas_las_Application_h_

#include <string>
#include <map>

#include "toolbox/ActionListener.h"
#include "toolbox/TimeVal.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Table.h"
#include "xdata/ActionListener.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"
#include "xdata/UnsignedInteger64.h"

#include "ws/addressing/EndpointReference.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "xmas/exception/Exception.h"

#include "xdaq/ContextTable.h"

// Identical copy to sensor objects, just change scope. They could be re-used in both if put in to a utils library
#include "xmas/las/SubscriptionRegistry.h"
#include "xmas/las/Settings.h"


namespace xmas 
{
	namespace las 
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
			
			//! Get the catalog of all flashlist in format fmt=[html|plain|csv]
			//
			void retrieveCatalog(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
			
			//! Get a single table of a flashlist flash=name&fmt=[html|plain|csv|exdr]
			//
			void retrieveCollection(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			
			//void displayMetricsToHTML( xgi::Output * out,  xmas::las::MonitorReport * report ) 
			//	throw (xmas::las::exception::Exception);			

			/*! Reset one or all accumulated flashlist data */
			//
			void reset(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);

			//
			// SOAP interface
			//
			
			//! Receive metrics from a sensor
			xoap::MessageReference report (xoap::MessageReference msg) throw (xoap::exception::Exception);
				
			protected:
			
			// External CGI interfaces for getting information about flashlists
			void displayFlashListCatalogToHTML(xgi::Output* out) throw (xmas::las::exception::Exception);
			void displayFlashListCatalogToXML(xgi::Output* out) throw (xmas::las::exception::Exception);
			void displayFlashListCatalogToCSV(xgi::Output* out) throw (xmas::las::exception::Exception);
			void displayFlashListCatalogToJSON(xgi::Output* out) throw (xmas::las::exception::Exception);
			
			//! Displays a table as a single HTML table with the first line describing the values
			//
			void displayTableToHTML
				(
					xgi::Output * out,
					xdata::Table::Reference& t,
					std::map<std::string, std::string>& filter
				) 
				throw (xmas::las::exception::Exception);
			//! Displays a table as a single HTML table with the first line describing the values
			//	
			void displayTableToJSON
				(
					xgi::Output * out,
					const std::string & name,
					xdata::Serializable * s,
					std::map<std::string, std::string>& filter,
					const std::string & tablename
				) 
				throw (xmas::las::exception::Exception);
			//! Displays a map of tables with timestamps as a single comma separated list with the first line describing the values
			void displayTableToCSV( xgi::Output * out, xdata::Table::Reference& t, std::map<std::string, std::string>& filter) 
				throw (xmas::las::exception::Exception);

			//! Displays a map of tables with collection timestamps in EXDR binary form
			void displayTableToEXDR( xgi::Output * out, xdata::Table::Reference& t, std::map<std::string, std::string>& filter ) 
				throw (xmas::las::exception::Exception);
				
			// -- Temporary functions for discovery services integration --
			//		
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);
							
			// Returns a subscription id in UUID format as a string
			//
			std::string subscribeToWSEventing( xdaq::ApplicationDescriptor* d )
				throw (xmas::las::exception::Exception);
				
			void renewSubscriptionToWSEventing(xdaq::ApplicationDescriptor * d, const std::string & uuid) 
				throw (xmas::las::exception::Exception);
				
			
			void refreshSubscriptionsToWSEventing() throw (xmas::las::exception::Exception);

			//
			// -- Temporary functions for discovery services integration --
			
			std::list<xdaq::ApplicationDescriptorImpl> getWSEventingServices(std::set<std::string>& groups);
			
			
			private:
			
			void applySettings(const std::string & path);
			
			bool match (xdata::Table * table, size_t row, std::map<std::string, std::string>& filter);
			bool match (xdata::Table::Reference & table, size_t row, std::map<std::string, std::string>& filter);

			std::map<std::string, xdata::Table::Reference> reports_; // data for a given flashlist
			std::map<std::string, toolbox::TimeVal> lastUpdate_; // per flashlist
			std::map<std::string, std::string> version_; // per flashlist
			std::map<std::string, std::string> tags_; // per flashlist
			std::map<std::string, std::string> lastOriginator_; // per flashlist
			
			xdata::Boolean useDiscovery_; // indicates if discovery services are used, default is true
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for monitoring
			xdata::String tag_; 		// one or more comma separated tags used to filter data incoming from ws-eventing services
			xdata::String settings_;	// settings file or path
			
			// Support for discovery service
			std::list<xdaq::ApplicationDescriptor*> wsEventingServices_; // temporary
			xdaq::ContextTable discoveredContexts_; // temporary
			xmas::las::SubscriptionRegistry subscriptions_;
			toolbox::BSem discoveryLock_;
			toolbox::BSem repositoryLock_;
			
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			xdata::UnsignedInteger64T reportLostCounter_;
						
			std::map<std::string, xmas::las::Settings*> flashSettings_; // indexed by flashlist name
			toolbox::TimeVal lastRetrieveTime_;
			double minDeltaBetweenRetrieve_; // minimum time between 2 retrieveCollection allowed to rate limit
			
			toolbox::BSem statisticsLock_;
			std::map<std::string, toolbox::Properties> statistics_;
		};
	}
}
#endif
