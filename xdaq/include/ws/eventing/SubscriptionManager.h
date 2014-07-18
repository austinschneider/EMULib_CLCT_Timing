// $Id: SubscriptionManager.h,v 1.8 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_SubscriptionManager_h_
#define _ws_eventing_SubscriptionManager_h_

#include <vector>
#include "toolbox/net/URL.h"
#include "ws/eventing/Identifier.h"
#include "ws/addressing/EndpointReference.h"

namespace ws
{

	namespace eventing
	{

	    class SubscriptionManager 
	    {
   		public:

        	SubscriptionManager(toolbox::net::URL & address, Identifier & id) throw (ws::addressing::exception::Exception);
		
        	//SubscriptionManager(toolbox::net::URL & url, std::vector<AddressHeader> & headers);

		ws::addressing::EndpointReference& getEndpointReference();

		ws::addressing::EndpointReference& setEndpointReference ( ws::addressing::EndpointReference & epa );

        	Identifier& getIdentifier();
		
		void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope);

		protected:

		ws::addressing::EndpointReference epa_;
		ws::eventing::Identifier id_;
	    };   
	}

}



#endif


