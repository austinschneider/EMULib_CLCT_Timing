// $Id: ApplicationContext.h,v 1.24 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationContext_h_
#define _xdaq_ApplicationContext_h_

#include <string>
#include "toolbox/mem/Reference.h"
#include "toolbox/ActionListener.h"
#include "toolbox/Properties.h"
#include "xdaq/NetGroup.h"
#include "xdaq/SharedObjectRegistry.h"
#include "xdaq/RoutingTable.h"
#include "xdaq/ContextTable.h"
#include "xdaq/ContextDescriptor.h"
#include "xdaq/exception/Exception.h"
#include "toolbox/exception/Handler.h"
#include "xoap/MessageReference.h"
#include "xdaq/Zone.h"
#include "xdaq/exception/InvalidZone.h"

// log4cplus includes
//
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

// log4cplus namespace
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;


namespace xdaq
{
	
	class ApplicationGroup;
	class ApplicationRegistry;
	class Application;
	
	class ApplicationContext
	{
		public:
		virtual ~ApplicationContext()
		{
		}

		//! Retrieve the local host identifier
		virtual xdaq::ContextDescriptor* getContextDescriptor() = 0;
		
		//! Retrieve a pointer to the NetGroup that provides access to the network configuration
		//
		virtual  xdaq::NetGroup* getNetGroup() = 0;
		
		//! Retrieve a pointer to the shared object registry
		//
		virtual  xdaq::SharedObjectRegistry* getSharedObjectRegistry() = 0;
		
		//! Retrieve a pointer to the application registry
		//
		virtual  xdaq::ApplicationRegistry* getApplicationRegistry() = 0;
		
		//! Retrieve a pointer to the destination based routing table that has
		//! a network name for each destination tid.
		//
		virtual  xdaq::RoutingTable* getRoutingTable() = 0;
		
		//! Retrieve a pointer to the table of hosts that contains the HTTP addresses and host identifiers
		//
		virtual  xdaq::ContextTable* getContextTable() = 0;
		
		//! Set a logging appender destination
		virtual void setAppender (const std::string& logUrl, const std::string& hostname) = 0;
		
		//! Return a pointer to the first application found that matches the \param className
		//
		virtual xdaq::Application* getFirstApplication (const std::string& className) 
			throw (xdaq::exception::Exception) = 0;
		
		// -----------------------------------------------------------------------
		// Patch: Functions from ApplicationContextImpl here until a Configuration class is done.
		// -----------------------------------------------------------------------
		
		/*! This function sends a XML structure to the
	 	 * target enclosed into a SOAP envelope to the specified target.
		 * e.g. <Envelope> ... <Body><UtilParamsSet targetAddr="number"></Body>...
		 * The network parameter is optional and is ignored in version 3.0. It will
  		 * in the future allow the user to send SOAP messages over other transports than http.
		*/
		virtual xoap::MessageReference postSOAP 
		(
			xoap::MessageReference& message, 
			xdaq::ApplicationDescriptor& originator, 
			xdaq::ApplicationDescriptor& destination
		) 
		throw (xdaq::exception::Exception) = 0;
				
		/*! This function is deprecated and should not be used.
		    use postSOAP (message, originator, destination) instead
		*/
		virtual xoap::MessageReference postSOAP 
		(
			xoap::MessageReference message, 
			xdaq::ApplicationDescriptor* destination, 
			std::string network =""
		) 
		throw (xdaq::exception::Exception) = 0;
		
		//! Send a binary frame that contains an I2O message 
		//
		virtual void postFrame 
		(
			toolbox::mem::Reference * ref, 
			xdaq::ApplicationDescriptor* originator, 
			xdaq::ApplicationDescriptor* destination
		)			 
		throw (xdaq::exception::Exception) = 0;
		
		//! Send a binary frame that contains an I2O message. Specify a handler for asynchronous exceptions and a context
		//
		virtual void postFrame 
		(
			toolbox::mem::Reference * ref, 
			xdaq::ApplicationDescriptor* originator, 
			xdaq::ApplicationDescriptor* destination,
			toolbox::exception::HandlerSignature* handler, 
			void* context
		) 
		throw (xdaq::exception::Exception) = 0;

		//! get current executive active logger
		//
		virtual Logger getLogger() = 0;
		
		//! Set the rootLogger log level
		//
		virtual void setLogLevel(const std::string& level) throw (xdaq::exception::Exception) = 0;
		
		//! get the current session identifier
		//
		virtual std::string getSessionId() = 0;
		
		//! Retrieve the default zone object from which xdaq::ApplicationDescriptor objects can be retrieved
		//
		virtual xdaq::Zone* getDefaultZone() = 0;
 		
 		//! Retrieve the name of the default zone
 		//
 		virtual std::string getDefaultZoneName() = 0;
 		
		//!
		//
		virtual std::set<std::string> getZoneNames () = 0;
		
		//!
		//
 		virtual xdaq::Zone* getZone(const std::string & name) 
			throw (xdaq::exception::InvalidZone) = 0;
 		
		virtual toolbox::Properties& getResources() = 0;
		
		virtual void addActionListener( toolbox::ActionListener * l ) = 0;

		virtual void removeActionListener( toolbox::ActionListener * l ) throw (xdaq::exception::Exception) = 0;
		
	};	
}

#endif
