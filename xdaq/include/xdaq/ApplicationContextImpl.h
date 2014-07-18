// $Id: ApplicationContextImpl.h,v 1.40 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationContextImpl_h_
#define _xdaq_ApplicationContextImpl_h_

#include "xercesc/dom/DOM.hpp"
#include "toolbox/Properties.h"
#include "toolbox/EventDispatcher.h"
#include "xoap/MessageReference.h"
#include "toolbox/mem/Reference.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

// old includes end

#include <map>
#include <vector>

#include "xdaq/ServicesMap.h"
#include "xdaq/NetGroup.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/ApplicationDescriptorFactory.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationRegistry.h"
#include "xdaq/SharedObjectRegistry.h"
#include "xdaq/RoutingTable.h"
#include "xdaq/MessengerCache.h"
#include "xdaq/ContextTable.h"
#include "xdaq/ContextDescriptor.h"
#include "xdaq/soap/MessengerCache.h"
#include "xdaq/exception/DuplicateZone.h"


namespace xdaq
{
	
	
	class ApplicationContextImpl: public ApplicationContext
	{
		public:
		
		ApplicationContextImpl(Logger& logger): logger_(logger), applicationRegistry_(this), messengerCache_(this)
		{
		}
		
		virtual ~ApplicationContextImpl()
		{
		}
		
		//! Initialize run-time system
		void init(int argc, char* argv[]) throw (xdaq::exception::Exception);
		
		//! Return the context identifier of this context object
		xdaq::ContextDescriptor* getContextDescriptor();
		
		//! Retrieve a pointer to the NetGroup that provides access to the network configuration
		//
		xdaq::NetGroup*  getNetGroup();
		
		xdaq::SharedObjectRegistry*  getSharedObjectRegistry();

		xdaq::ApplicationRegistry *  getApplicationRegistry();
		
		xdaq::RoutingTable* getRoutingTable();
		
		xdaq::ContextTable*  getContextTable();
		
		//! Set the rootLogger log level
		//
		void setLogLevel(const std::string& level) throw (xdaq::exception::Exception);
		
		//! Get the rootLogger log level as a string
		//
		std::string getLogLevel();
		
		//! Set a logging appender destination
		/*! Throw if the URL is malformed or the URL cannot be resolved or 
		 *  no appender implementation for the URL type can be found
		 */
		void setAppender (const std::string& logUrl, const std::string& hostname) throw (xdaq::exception::Exception);

		//! Overlay the currently runnig xdaq process with a new one
		//
		void reset() throw (xdaq::exception::Exception);
		
		//! Return a pointer to the first application found that matches the \param className
		//
		xdaq::Application* getFirstApplication (const std::string& className) 
			throw (xdaq::exception::Exception);
			
		//! load a dynamically loadable module
		//
		void loadModule(const std::string& pathname) 
			throw (xdaq::exception::Exception);
		
		void setSessionId(const std::string& id);
		
		std::string getSessionId();
		
		void fireEvent ( toolbox::Event & e );
		
		int argc		();
		char** argv		();

		protected:
		
		/*!
			This function sends a SOAP message to the \param destination.
		*/
		xoap::MessageReference postSOAP 
		( 
			xoap::MessageReference& message, 
			xdaq::ApplicationDescriptor& originator, 
			xdaq::ApplicationDescriptor& destination
		) 
		throw (xdaq::exception::Exception);
			
		/*!
			This function sends a XML structure to the
			target enclosed into a SOAP envelope to the specified target.
			e.g. <Envelope> ... <Body><UtilParamsSet targetAddr="number"></Body>...
		*/
		xoap::MessageReference postSOAP 
		( 
			xoap::MessageReference message, 
			xdaq::ApplicationDescriptor* destination, 
			std::string network = ""
		) 
		throw (xdaq::exception::Exception);
								
		//! Send a binary frame that contains an I2O message 
		//
		void postFrame 
		(
			toolbox::mem::Reference * ref, 
			xdaq::ApplicationDescriptor* originator, 
			xdaq::ApplicationDescriptor* destination
		) 
		throw (xdaq::exception::Exception);
		
		
		//! Send a binary frame that contains an I2O message. Specify a handler for asynchronous exceptions and a context
		//
		void postFrame (
			toolbox::mem::Reference * ref, 
			xdaq::ApplicationDescriptor* originator, 
			xdaq::ApplicationDescriptor* destination,
			toolbox::exception::HandlerSignature* handler, 
			void* context
		) 
		throw (xdaq::exception::Exception);		
		
		std::string getPath	();
		std::string getCommand	();

		
		//! get current executive active logger
		//
		Logger getLogger();
		
		//! Read a profile file and apply the contained configuration to the local context
		//
		void applyProfile(const std::string& filename) throw (xdaq::exception::Exception);
		
		void addActionListener( toolbox::ActionListener * l );

 		void removeActionListener( toolbox::ActionListener * l ) throw (xdaq::exception::Exception);
 		 		
 		std::string getDefaultZoneName();
 		
 		xdaq::Zone* getDefaultZone();
 		
		std::set<std::string> getZoneNames ();

 		xdaq::Zone* getZone(const std::string & name) throw ( xdaq::exception::InvalidZone);
 			
		//! \returns a reference to a properties object storing resources
		/*!
			The following resources are available
			
			xdaq.uri.netpath ..... path prefix to be used when loading external resources
			xdaq.resource.root .. path to resources directory
		*/
		toolbox::Properties& getResources();
		
		// The following two functions will in the future move to a Configuration class
		// ----------------------------------------------------------------------------

		
			
		//! Helper to load DOM from pathname (will expand pathname with environment variable names like ${XDAQ_ROOT}
		//
		DOMDocument* loadDOM (const std::string& pathname) 
			throw (xdaq::exception::Exception);
		
		protected:
					
		std::string			path_;
		//Appender*			defaultAppender_;		// log appender
		SharedAppenderPtr               defaultAppender_;
		Logger				logger_;		
		std::string			lastLogLevel_;	
		std::string			sessionId_;	
		//std::string			contextPath_;	
		
		xdaq::NetGroup			netGroup_;
		xdaq::ApplicationRegistry	applicationRegistry_;
		xdaq::SharedObjectRegistry 	sharedObjectRegistry_;		
		xdaq::RoutingTable		routingTable_;
		xdaq::MessengerCache		messengerCache_;
		xdaq::soap::MessengerCache	soapMessengerCache_;
		xdaq::ContextTable		contextTable_;
		xdaq::ContextDescriptor*	context_;
		char** argv_;
		int argc_;
		
		toolbox::EventDispatcher dispatcher_;
		std::string defaultZoneName_;
		xdaq::Zone * defaultZone_;
		
		toolbox::Properties resources_;
		xdaq::ServicesMap servicesMap_;
	};	
}

#endif
