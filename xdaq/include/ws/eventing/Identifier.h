// $Id: Identifier.h,v 1.4 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_Identifier_h_
#define _ws_eventing_Identifier_h_

#include <string>
#include "toolbox/net/UUID.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/addressing/EndpointReference.h"

namespace ws
{
namespace eventing
{
	class Identifier: public toolbox::net::UUID
	{ 
		public:
	
 		Identifier()
			throw (ws::eventing::exception::Exception);

        	Identifier(toolbox::net::UUID& id)
			throw (ws::eventing::exception::Exception);

        	Identifier(const std::string & id)
			throw (ws::eventing::exception::Exception);

		/*
        	Identifier(const Identifier & id)
			throw (ws::eventing::exception::Exception);
		*/

        	Identifier(ws::addressing::EndpointReference & epa)
			throw (ws::eventing::exception::Exception);

        	// toolbox::net::UDDI getValue();

		// void setValue( toolbox::net::UDDI & uid )
		//	throw (ws::eventing::exception::Exception);
		
       		/* AddressHeader getAddressHeader()
       		 {		
            		get { return AddressHeader.CreateAddressHeader(WSEventing.ElementNames.Identifier, WSEventing.NamespaceUri, Value.ToString()); }        
		}
		*/
    };
}
}
#endif


