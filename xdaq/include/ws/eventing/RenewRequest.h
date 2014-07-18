// $Id: RenewRequest.h,v 1.5 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_RenewRequest_h_
#define _ws_eventing_RenewRequest_h_

#include <string>
#include "toolbox/net/exception/Exception.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/eventing/Identifier.h"
#include "ws/eventing/Expires.h"
#include "xoap/MessageReference.h"
#include "ws/addressing/Headers.h"


namespace ws
{
namespace eventing
{
	class RenewRequest
	{
		public:
		
		RenewRequest(xoap::MessageReference& msg) 
			throw (ws::eventing::exception::Exception);
        
		RenewRequest(const RenewRequest & request);
		
		RenewRequest(ws::eventing::Identifier& identifier, ws::eventing::Expires& expires);
	
		RenewRequest& operator= (const RenewRequest & request);
		
		virtual ~RenewRequest();
		
		ws::addressing::Headers & getAddressingHeaders();

		void setIdentifier (ws::eventing::Identifier& identifier);
		
		ws::eventing::Identifier& getIdentifier();

		Expires& getExpires() const;
	
		void setExpires ( Expires& value );
		
		bool hasExpires();
		
		xoap::MessageReference toSOAP();
		
		private:
		
		ws::addressing::Headers aheaders_;
		ws::eventing::Identifier identifier_;
		ws::eventing::Expires* expires_;

	};
}

}

#endif


