/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _state_dashboard_SubscriptionRegistry_h_
#define _state_dashboard_SubscriptionRegistry_h_

#include <string>
#include <map>
#include "xdaq/ApplicationDescriptor.h"
#include "state/dashboard/exception/Exception.h"

namespace state
{
	namespace dashboard
	{
		class SubscriptionRegistry 
		{
			public:
			
			bool hasSubscription( const std::string& name, xdaq::ApplicationDescriptor* descriptor);
			
			std::string getSubscription( 
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor ) 
					throw (state::dashboard::exception::Exception );
			
			void addSubscription(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor,
				const std::string & suscriptionUUID )
					throw (state::dashboard::exception::Exception );
			
			
			void removeSubscription(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor )
					throw (state::dashboard::exception::Exception );
			
			std::map<xdaq::ApplicationDescriptor*, std::string>&
			getSubscriptions (const std::string& name)
				throw (state::dashboard::exception::Exception );
			
			bool empty();
			
			protected:
			
			// <flashlist, < destination UUID , subscription uuid > >
			std::map<std::string, std::map<xdaq::ApplicationDescriptor*, std::string> > subscriptions_;
		
		};
	
	}
}

#endif

