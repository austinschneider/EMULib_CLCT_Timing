/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_SubscriptionRegistry_h_
#define _ws_broker_SubscriptionRegistry_h_

#include <string>
#include <map>
#include "xdaq/ApplicationDescriptor.h"
#include "ws/broker/exception/Exception.h"

namespace ws
{
	namespace broker
	{
		class SubscriptionRegistry 
		{
			public:
			
			bool hasSubscription( const std::string& name, xdaq::ApplicationDescriptor* descriptor);
			
			std::string getSubscription( 
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor ) 
					throw (ws::broker::exception::Exception );
			
			void addSubscription(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor,
				const std::string & suscriptionUUID )
					throw (ws::broker::exception::Exception );
			
			
			void removeSubscription(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor )
					throw (ws::broker::exception::Exception );
			
			std::map<xdaq::ApplicationDescriptor*, std::string>&
			getSubscriptions (const std::string& name)
				throw (ws::broker::exception::Exception );
			
			bool empty();
			
			protected:
			
			// <flashlist, < destination UUID , subscription uuid > >
			std::map<std::string, std::map<xdaq::ApplicationDescriptor*, std::string> > subscriptions_;
		
		};
	
	}
}	

#endif
