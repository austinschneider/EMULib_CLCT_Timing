// $Id: SubscribeResponse.h,v 1.9 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_SubscribeResponse_h_
#define _ws_eventing_SubscribeResponse_h_

#include "xoap/SOAPName.h"
#include "xoap/SOAPBody.h"
#include "xoap/SOAPElement.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "ws/eventing/SubscribeRequest.h"
#include "ws/addressing/Headers.h"
#include "ws/eventing/SubscriptionManager.h"
#include "ws/eventing/Expires.h"

namespace ws
{
namespace eventing
{
	class SubscribeResponse
	{
		public:		
		
		SubscribeResponse(SubscriptionManager& manager, ws::eventing::SubscribeRequest& request);
		
		ws::addressing::Headers getAddressingHeaders();
		
		SubscriptionManager& getSubscriptionManager();

		void setSubscriptionManager(SubscriptionManager& value);

		Expires& getExpires();

		void setExpires (Expires& value);
		
		xoap::MessageReference toSOAP();
		
		protected:
		
		ws::addressing::Headers aheaders_;
		
		SubscriptionManager manager_;
		Expires expires_;
		
	};
}
}
#endif
