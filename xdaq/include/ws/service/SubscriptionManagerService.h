// $Id: SubscriptionManagerService.h,v 1.3 2008/07/18 15:27:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_SubscriptionManagerService_h_
#define _ws_service_SubscriptionManagerService_h_

#include <list>
#include <string>

#include "ws/eventing/exception/Exception.h"

#include "ws/eventing/ServiceAdapterBase.h"
#include "ws/eventing/StorageAdapter.h"
#include "ws/eventing/SubscribeRequest.h"
#include "ws/eventing/UnsubscribeRequest.h"
#include "ws/eventing/RenewRequest.h"
#include "ws/eventing/GetStatusRequest.h"
#include "ws/eventing/SubscribeResponse.h"
#include "ws/eventing/UnsubscribeResponse.h"
#include "ws/eventing/RenewResponse.h"
#include "ws/eventing/GetStatusResponse.h"

#include "toolbox/task/TimerListener.h"

#include "xdaq/Object.h"
#include "xdaq/Application.h"

namespace ws
{
	namespace service
	{

	    class SubscriptionManagerService: public ws::eventing::ServiceAdapterBase, public toolbox::task::TimerListener, public xdaq::Object
	    {
    		public:

     		SubscriptionManagerService(xdaq::Application* owner, ws::eventing::StorageAdapter * sa );
		
		virtual ~SubscriptionManagerService();

        	ws::eventing::SubscribeResponse subscribe(ws::eventing::SubscribeRequest & request) throw (ws::eventing::exception::Exception);

        	ws::eventing::UnsubscribeResponse unsubscribe(ws::eventing::UnsubscribeRequest & request) throw (ws::eventing::exception::Exception);

        	ws::eventing::RenewResponse renew(ws::eventing::RenewRequest& request) throw (ws::eventing::exception::Exception);

        	ws::eventing::GetStatusResponse getStatus(ws::eventing::GetStatusRequest& request)
			throw (ws::eventing::exception::Exception);
		
		void timeExpired(toolbox::task::TimerEvent& e);

		protected:

		std::list<std::string> delivering_;
        	std::list<std::string> filtering_;  
	    };
	}
}

#endif


