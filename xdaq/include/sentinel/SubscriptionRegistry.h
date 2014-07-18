// $Id: SubscriptionRegistry.h,v 1.2 2008/07/18 15:27:25 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_SubscriptionRegistry_h_
#define _sentinel_SubscriptionRegistry_h_

#include <string>
#include <map>
#include "xdaq/ApplicationDescriptor.h"
#include "sentinel/exception/Exception.h"

namespace sentinel
{
	class SubscriptionRegistry 
	{
		public:

		bool hasSubscription( const std::string& name, xdaq::ApplicationDescriptor* descriptor);

		std::string getSubscription( 
			const std::string& name, 
			xdaq::ApplicationDescriptor* descriptor ) 
				throw (sentinel::exception::Exception );

		void addSubscription(
			const std::string& name, 
			xdaq::ApplicationDescriptor* descriptor,
			const std::string & suscriptionUUID )
				throw (sentinel::exception::Exception );


		void removeSubscription(
			const std::string& name, 
			xdaq::ApplicationDescriptor* descriptor )
				throw (sentinel::exception::Exception );

		std::map<xdaq::ApplicationDescriptor*, std::string>&
		getSubscriptions (const std::string& name)
			throw (sentinel::exception::Exception );

		bool empty();

		protected:

		// <name, < destination UUID , subscription uuid > >
		std::map<std::string, std::map<xdaq::ApplicationDescriptor*, std::string> > subscriptions_;

	};

}


#endif
