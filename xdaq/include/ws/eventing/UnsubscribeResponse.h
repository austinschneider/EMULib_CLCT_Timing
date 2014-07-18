// $Id: UnsubscribeResponse.h,v 1.5 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_UnsubscribeResponse_h_
#define _ws_eventing_UnsubscribeResponse_h_

#include "ws/eventing/WSEventing.h"
#include "ws/eventing/SubscriptionManager.h"
#include "ws/eventing/UnsubscribeRequest.h"
#include "ws/addressing/Headers.h"
#include "xoap/MessageReference.h"

namespace ws
{
	namespace eventing
	{
		class UnsubscribeResponse
		{
        		public:

			UnsubscribeResponse
			(
				UnsubscribeRequest& request
			);

			xoap::MessageReference toSOAP();
			
			protected:
		
			ws::addressing::Headers aheaders_;
		};
	}
}

#endif


