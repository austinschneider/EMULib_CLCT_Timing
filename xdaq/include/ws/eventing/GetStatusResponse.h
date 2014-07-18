// $Id: GetStatusResponse.h,v 1.5 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_GetStatusResponse_h_
#define _ws_eventing_GetStatusResponse_h_

#include "ws/addressing/Headers.h"
#include "ws/eventing/Expires.h"
#include "ws/eventing/SubscriptionManager.h"
#include "ws/eventing/GetStatusRequest.h"
#include "xoap/MessageReference.h"

namespace ws
{
namespace eventing
{
	class GetStatusResponse
	{
		public:
		
		GetStatusResponse(const GetStatusResponse& response);
		
		GetStatusResponse(Expires& expires);
		
		GetStatusResponse
		(
			SubscriptionManager& manager,
			GetStatusRequest& request
		);
		
		Expires& getExpires();

		void setExpires (Expires& value);
		
		xoap::MessageReference toSOAP();
		
		protected:
		
		ws::addressing::Headers aheaders_;
		Expires expires_;
    };
}
}
#endif


