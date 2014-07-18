// $Id: RenewResponse.h,v 1.4 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_RenewResponse_h_
#define _ws_eventing_RenewResponse_h_

#include "xoap/SOAPName.h"
#include "xoap/SOAPBody.h"
#include "xoap/SOAPElement.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"

#include "ws/eventing/SubscriptionManager.h"
#include "ws/eventing/RenewRequest.h"


namespace ws
{
namespace eventing
{
	class RenewResponse 
	{
		public:
		
		RenewResponse(const RenewResponse& response);
		
		RenewResponse(SubscriptionManager& manager, ws::eventing::RenewRequest& request);
		
		ws::addressing::Headers getAddressingHeaders();
		
		xoap::MessageReference toSOAP();
		
		Expires& getExpires();

		void setExpires (Expires& value);
		
		protected:
		
		ws::addressing::Headers aheaders_;
		
		Expires expires_;
		SubscriptionManager manager_;
	};
}
}
#endif


