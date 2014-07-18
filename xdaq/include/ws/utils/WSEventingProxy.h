// $Id: WSEventingProxy.h,v 1.5 2008/07/18 15:27:54 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_utils_WSEventingProxy_h_
#define _ws_utils_WSEventingProxy_h_

#include <string>
#include <list>

#include "ws/eventing/WSEventing.h"
#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Object.h" 
#include "ws/utils/SubscriptionRegistry.h"
#include "ws/utils/exception/Exception.h"
#include "toolbox/BSem.h"

namespace ws 
{
	namespace utils 
	{
		class WSEventingProxy : public xdaq::Object
		{
			public:

			WSEventingProxy(xdaq::Application* owner);

			void refreshWSEventingSubscriptions
			(
				std::list<std::string> & filters,
				std::list<xdaq::ApplicationDescriptorImpl> & destinations,
				const std::string& dialect = ws::eventing::XPathDialect
			) 
			throw (ws::utils::exception::Exception);

			private:

			std::string subscribeToWSEventing
			(
				const std::string& filter,
				xdaq::ApplicationDescriptor* d,
				const std::string& dialect = ws::eventing::XPathDialect
			) 
			throw (ws::utils::exception::Exception);

			void renewSubscriptionToWSEventing
			(
				xdaq::ApplicationDescriptor * d,
				const std::string & uuid
			) 
			throw (ws::utils::exception::Exception);	

			SubscriptionRegistry subscriptions_;
			toolbox::BSem mutex_;
		};
	}
}

#endif
