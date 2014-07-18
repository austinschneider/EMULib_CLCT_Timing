// $Id: GetStatusRequest.h,v 1.8 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_GetStatusRequest_h_
#define _ws_eventing_GetStatusRequest_h_

#include "ws/eventing/Identifier.h"
#include "ws/addressing/Headers.h"
#include "xoap/MessageReference.h"
#include "ws/eventing/exception/Exception.h"

namespace ws
{
namespace eventing
{
    class GetStatusRequest 
    {
    	public:
	GetStatusRequest();
	
      	GetStatusRequest(xoap::MessageReference& msg) 
		throw (ws::eventing::exception::Exception);
	
        GetStatusRequest(ws::eventing::Identifier& id);
        	
	GetStatusRequest& operator= (const GetStatusRequest & request);
	
	ws::addressing::Headers & getAddressingHeaders();

        ws::eventing::Identifier& getIdentifier();
	
	void setIdentifier(ws::eventing::Identifier& value);

	xoap::MessageReference toSOAP();
	      
	protected:
	
	ws::addressing::Headers aheaders_;

        ws::eventing::Identifier identifier_;
    };
}
}
#endif


