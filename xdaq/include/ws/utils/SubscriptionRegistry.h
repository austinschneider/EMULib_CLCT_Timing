// $Id: SubscriptionRegistry.h,v 1.2 2008/07/18 15:27:54 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_utils_SubscriptionRegistry_h_
#define _ws_utils_SubscriptionRegistry_h_

#include <string>
#include <map>
#include "xdaq/ApplicationDescriptor.h"
#include "ws/utils/exception/Exception.h"

namespace ws
{
	namespace utils
	{
		class SubscriptionRegistry 
		{
			public:
			
			bool hasSubscription
			(
				const std::string& name,
				xdaq::ApplicationDescriptor* descriptor
			);
			
			std::string getSubscription
			( 
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor
			) 
			throw (ws::utils::exception::Exception);
			
			void addSubscription
			(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor,
				const std::string & suscriptionUUID
			)
			throw (ws::utils::exception::Exception );
						
			void removeSubscription
			(
				const std::string& name, 
				xdaq::ApplicationDescriptor* descriptor
			)
			throw (ws::utils::exception::Exception );
			
			std::map<xdaq::ApplicationDescriptor*, std::string>& getSubscriptions
			(
				const std::string& name
			)
				throw (ws::utils::exception::Exception );
			
			bool empty();
			
			protected:
			
			// <identifier, < destination UUID , subscription uuid > >
			std::map<std::string, std::map<xdaq::ApplicationDescriptor*, std::string> > subscriptions_;		
		};	
	}
}	

#endif
