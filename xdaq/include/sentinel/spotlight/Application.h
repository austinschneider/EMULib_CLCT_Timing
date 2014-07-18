// $Id: Application.h,v 1.12 2008/11/25 13:21:03 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight_Application_h_
#define _sentinel_spotlight_Application_h_

#include <string>
#include <map>

#include "toolbox/ActionListener.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
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
#include "xgi/Output.h"
#include "xgi/exception/Exception.h"
#include "sentinel/exception/Exception.h"

#include "ws/utils/WSEventingProxy.h"
#include "xplore/utils/DescriptorsCache.h"

#include "sentinel/spotlight/Repository.h"

namespace sentinel 
{
	namespace spotlight 
	{
		class Application :public xdaq::Application, 
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

			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			/*! Clear exception history
			 */
			void reset(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			/*! View a specific exception referenced by uuid
			 */
			void view(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			/*! list all available exceptions
			 */
			void catalog(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
			
			void events(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);		
				
			void lastStoredEvents(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);

			/*! generate a test exception
			 */
			void inject(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
			void generate(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			/*! Retrieve list of spotlight database files in the configured path */
			void files(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			/*! Retrieve list of open databases */
			void databases(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			/*! Attach to an additional database file in the configured directory
				parameters 'dbname' and 'filename' 
			*/
			void attach(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			/*! Detach from an attached database
				parameter 'dbname'
			*/
			void detach(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);
				
			//
			// SOAP interface
			//
			
			//! Receive error messages from WS-Eventing
			//
			xoap::MessageReference notify (xoap::MessageReference msg) throw (xoap::exception::Exception);
			xoap::MessageReference revoke (xoap::MessageReference msg) throw (xoap::exception::Exception);
			
			void rearm(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

			protected:
			
			void subscribeToDiscoveryServices() throw (xdaq::exception::Exception);

			
			private:
			
			xplore::utils::DescriptorsCache descriptorsCache_;
			ws::utils::WSEventingProxy wsEventingProxy_;
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			Repository* repository_;							
			xdata::UnsignedInteger64T exceptionsLostCounter_;

			xdata::String maintenanceInterval_; // interval at which the database switchover happens (> 1 minute)
			xdata::String repositoryPath_; // folder in which to store the spotlight database files (/var/run/spotlight)
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for exceptions
			xdata::String exceptionsTimeWindow_;
			xdata::String archiveWindow_; // determine the name of the file for storing archived exceptions (default 1H )
			

		};
	}
}
#endif
