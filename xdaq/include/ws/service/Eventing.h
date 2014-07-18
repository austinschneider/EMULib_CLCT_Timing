// $Id: Eventing.h,v 1.12 2008/07/18 15:27:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_Eventing_h_
#define _ws_Service_Eventing_h_

#include <string>

#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

#include "xdata/Boolean.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/ActionListener.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "ws/eventing/MemoryStorageAdapter.h"
#include "ws/service/SubscriptionManagerService.h"
#include "ws/service/NotificationManagerService.h"
#include "ws/eventing/PeerTransportService.h"
#include "ws/service/MessengerCache.h"
#include "ws/service/Statistics.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

namespace ws 
{
	namespace service 
	{
		class Eventing: public xdaq::Application,  public xdata::ActionListener, public ws::eventing::PeerTransportService
		{
			public:

			XDAQ_INSTANTIATOR();

			Eventing(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Eventing();

			void actionPerformed (xdata::Event& e) ;

			//
			// SOAP Callback to reset the state machine
			//
			xoap::MessageReference onMessage (xoap::MessageReference msg) throw (xoap::exception::Exception);

			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);



			// Implementation for PeerTransportServices
			xoap::MessageReference post(ws::addressing::EndpointReference& epa, xoap::MessageReference & request) 
				 throw (ws::eventing::exception::Exception );

			protected:

			ws::eventing::MemoryStorageAdapter* storageAdapter_;
			ws::service::SubscriptionManagerService* subscriptionManagerService_;
			ws::service::NotificationManagerService* notificationManager_;
			ws::service::MessengerCache messengerCache_;
			ws::addressing::EndpointReference from_;
            xdata::UnsignedInteger32 maxRetries_;
            xdata::UnsignedInteger32 waitRetry_;
			xdata::Boolean createStatistics_;
			ws::service::Statistics* statistics_;
		};
	}
}

#endif
