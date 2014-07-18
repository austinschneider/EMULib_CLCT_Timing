// $Id: Application.h,v 1.8 2008/09/02 07:16:46 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las2g_Application_h_
#define _xmas_las2g_Application_h_

#include <string>
#include <map>

#include "toolbox/ActionListener.h"
#include "toolbox/TimeVal.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "toolbox/exception/Handler.h"
#include "pt/PeerTransportAgent.h"
#include "pt/tcp/Address.h"

#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Table.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/FixedSizeInputStreamBuffer.h"
#include "xdata/exdr/FixedSizeOutputStreamBuffer.h"
#include "xdata/exdr/Serializer.h"
#include "xgi/Method.h"
#include "xgi/Utils.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/ServiceProxy.h"

#include "xgi/exception/Exception.h"
#include "xmas/exception/Exception.h"
#include "xdaq/ContextTable.h"

// Identical copy to sensor objects, just change scope. They could be re-used in both if put in to a utils library
#include "xmas/las2g/FlashlistData.h"
#include "b2in/utils/MessengerCacheListener.h"

namespace xmas 
{
	namespace las2g
	{
		class Application :
			public xdaq::Application, 
			public toolbox::ActionListener,
			public xdata::ActionListener,
			public toolbox::task::TimerListener,
			public b2in::utils::MessengerCacheListener
		{
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed(toolbox::Event& e);			
			
			void asynchronousExceptionNotification(xcept::Exception& e);

			//
			// B2IN Interface
			//
			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);

			//
			// XGI Interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			
			//! Get the catalog of all flashlist in format fmt=[html|plain|csv]
			//
			void retrieveCatalog(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
			
			//! Get a single table of a flashlist flash=name&fmt=[html|plain|csv|exdr]
			//
			void retrieveCollection(xgi::Input * in, xgi::Output * out ) 
				throw (xgi::exception::Exception);			


			protected:
			
			void timeExpired(toolbox::task::TimerEvent& event);
			
			
			void displayFlashListCatalogToHTML( xgi::Output * out ) throw (xmas::exception::Exception);
			void displayFlashListCatalogToXML( xgi::Output * out ) throw (xmas::exception::Exception);
			void displayFlashListCatalogToJSON( xgi::Output * out ) throw (xmas::exception::Exception);
			void displayFlashListCatalogToCSV( xgi::Output * out ) throw (xmas::exception::Exception);
				
			private:
			
			void discoverEndpoints() throw (xmas::exception::Exception);
			void refreshSubscriptionsToEventing() throw (xmas::exception::Exception);

			std::map<std::string, FlashlistData*> repository_; 
						
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for monitoring
			xdata::String topic_; 		// one or more comma separated tags used to filter data incoming from ws-eventing services
						
			xdata::UnsignedInteger64T reportLostCounter_;
									
			std::map<std::string, xdata::Properties> subscriptions_; // indexed by topic

			toolbox::TimeVal lastRetrieveTime_;
			double minDeltaBetweenRetrieve_; // minimum time between 2 retrieveCollection allowed to rate limit
			
			toolbox::BSem repositoryLock_;
			
			//std::map<std::string, toolbox::Properties> statistics_;
			xdata::exdr::Serializer serializer_;
			b2in::utils::ServiceProxy* b2inEventingProxy_;
			
			xdata::String  scanPeriod_;
			xdata::String  subscribeExpiration_;


			
		};
	}
}
#endif
