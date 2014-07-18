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

#ifndef _sentinel_spotlight2g_Application_h_
#define _sentinel_spotlight2g_Application_h_

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
#include "xdata/Properties.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/ServiceProxy.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/Output.h"
#include "xgi/exception/Exception.h"
#include "sentinel/exception/Exception.h"

#include "ws/utils/WSEventingProxy.h"
#include "xplore/utils/DescriptorsCache.h"

#include "sentinel/spotlight2g/Repository.h"

namespace sentinel 
{
	namespace spotlight2g 
	{
		class Application :public xdaq::Application, 
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
			// B2IN interface
			//
		        void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);

			void asynchronousExceptionNotification(xcept::Exception& e);

			void rearm(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

			protected:
			
                       void refreshSubscriptionsToEventing() throw (sentinel::exception::Exception);

			void loadJEL(const std::string & fname);
			bool applyJEL( xcept::Exception & e);
			bool match ( xcept::Exception & e, std::map<std::string, std::string>& filter);
			std::string mapToAttributeName(const std::string & name);

			void mainPage ( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

			void HotspotTabPage(xgi::Output * out) throw (xgi::exception::Exception);
			void StatisticsTabPage(xgi::Output * out) throw (xgi::exception::Exception);

			
			private:
			
			toolbox::task::AsynchronousEventDispatcher dispatcher_;
			Repository* repository_;							
			xdata::UnsignedInteger64T exceptionsLostCounter_;
			xdata::String topic_;

			xdata::String maintenanceInterval_; // interval at which the database switchover happens (> 1 minute)
			xdata::String repositoryPath_; // folder in which to store the spotlight database files (/var/run/spotlight)
			xdata::String subscribeGroup_; // one or more comma separated groups hosting a ws-eventing service for exceptions
			xdata::String exceptionsTimeWindow_;
			xdata::String archiveWindow_; // determine the name of the file for storing archived exceptions (default 1H )
			xdata::String jelFileName_; // xml file containing junk exception filter rules 


 			b2in::utils::ServiceProxy* b2inEventingProxy_;
                        xdata::String  scanPeriod_;
                        xdata::String  subscribeExpiration_;

			std::map<std::string, xdata::Properties> subscriptions_; // indexed by topic

			std::list<xdata::Properties> jel_;
			std::map<std::string,std::map<std::string,size_t> > jec_;
		};
	}
}
#endif
