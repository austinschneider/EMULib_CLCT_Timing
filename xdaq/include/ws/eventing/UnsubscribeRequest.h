// $Id: UnsubscribeRequest.h,v 1.5 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_UnsubscribeRequest_h_
#define _ws_eventing_UnsubscribeRequest_h_

#include <string>
#include "toolbox/net/exception/Exception.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/eventing/Identifier.h"
#include "ws/addressing/Headers.h"
#include "xoap/MessageReference.h"

namespace ws
{

namespace eventing
{

	class UnsubscribeRequest 
	{
		public:
		
		UnsubscribeRequest(xoap::MessageReference& msg) 
			throw (ws::eventing::exception::Exception);
        
		UnsubscribeRequest(const UnsubscribeRequest & request);
	
		UnsubscribeRequest& operator= (const UnsubscribeRequest & request);
		
		UnsubscribeRequest(ws::eventing::Identifier& identifier);
	
		ws::addressing::Headers getAddressingHeaders();	
	
		void setIdentifier (ws::eventing::Identifier& identifier);
		
		ws::eventing::Identifier& getIdentifier();

		private:
		
		ws::addressing::Headers aheaders_;

		ws::eventing::Identifier identifier_;
	};
}
}
#endif


