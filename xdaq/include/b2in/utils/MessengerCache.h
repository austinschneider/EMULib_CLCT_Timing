// $Id: MessengerCache.h,v 1.7 2008/07/18 15:26:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_MessengerCache_h_
#define _b2in_utils_MessengerCache_h_

#include <vector>
#include <map>
#include <string>
#include "xdaq/ApplicationContext.h"
#include "xdaq/NetGroup.h"
#include "xdaq/Network.h"
#include "xdata/Properties.h"
#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "b2in/utils/exception/Exception.h"
#include "b2in/utils/MessengerCacheListener.h"

#include "toolbox/BSem.h"
#include "toolbox/lang/Class.h"
#include "toolbox/exception/Handler.h"
#include "b2in/nub/exception/InternalError.h"
#include "b2in/nub/exception/QueueFull.h"
#include "b2in/nub/exception/OverThreshold.h"

namespace b2in 
{
	namespace utils
	{
		//! This class maintains a cache of messenger pointers for fast access to 
		//! the messenger by giving a source and destination tid.
		//
		class MessengerCache : public toolbox::lang::Class
		{
			xdaq::ApplicationContext* context_;

			public:

			MessengerCache (xdaq::ApplicationContext* context, const std::string & networkName, MessengerCacheListener * listener ) 
				throw(b2in::utils::exception::Exception);

			//!
			//
			void invalidate 
			(
				const std::string& url
			)
			throw (b2in::utils::exception::Exception);
		
			//!
			//
					
			void createMessenger
			(
				const std::string& url
			) 
			throw (b2in::utils::exception::Exception);


			std::list<std::string> getDestinations();
	
			void send (const std::string & url, toolbox::mem::Reference* msg, xdata::Properties & plist) 
				throw (b2in::nub::exception::InternalError, b2in::nub::exception::QueueFull, b2in::nub::exception::OverThreshold);
				
			bool hasMessenger (const std::string & url);

			pt::Address::Reference getLocalAddress();

			protected:
			
			bool subscribeFailed(xcept::Exception& e, void * context);
			
			
			pt::Messenger* getMessenger
			(
				const std::string& url
			) 
			throw (b2in::utils::exception::Exception);


			std::vector<pt::Messenger::Reference> messengerReferences_;
			std::map<std::string, pt::Messenger*> messengers_;	
			toolbox::BSem lock_;
			pt::Address::Reference localAddress_;
			
			toolbox::exception::HandlerSignature  * subscribeFailedHandler_;
			MessengerCacheListener * listener_;

		};
	}
}

#endif







