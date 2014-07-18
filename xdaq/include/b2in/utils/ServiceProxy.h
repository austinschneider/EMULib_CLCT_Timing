//$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_ServiceProxy_h_
#define _b2in_utils_ServiceProxy_h_

#include <vector>
#include <map>
#include <string>
#include "xdaq/ApplicationContext.h"
#include "xdaq/NetGroup.h"
#include "xdaq/Network.h"
#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "b2in/utils/exception/Exception.h"
#include "b2in/utils/MessengerCache.h"
#include "b2in/utils/MessengerCacheListener.h"

#include "xdaq/Object.h"
#include "xdaq/Application.h"

#include "toolbox/BSem.h"

namespace b2in 
{
	namespace utils
	{
		//! This class maintains a cache of messenger pointers for fast access to 
		//! the messenger by giving a source and destination tid.
		//
		class ServiceProxy: public xdaq::Object

		{
			public:

			/*! Discover services in the provided list of groups. 
			    For each discovered service a messenger is created and put
			    into the messenger cache
			*/
			ServiceProxy 
			(
				xdaq::Application * owner,
				const std::string& servicename,
				const std::string& group,
				b2in::utils::MessengerCacheListener * listener
			) 
				throw(b2in::utils::exception::Exception);

			//!
			//
			bool scan()
				throw (b2in::utils::exception::Exception);
				
			b2in::utils::MessengerCache* getMessengerCache()
				throw (b2in::utils::exception::Exception);				

			void addURL(const std::string & url)
				throw (b2in::utils::exception::Exception);

			protected:

			b2in::utils::MessengerCache* messengerCache_;
			std::string applicationFilter_;
			std::string servicename_;
			std::string group_;
			b2in::utils::MessengerCacheListener * listener_;

		};
	}
}

#endif







