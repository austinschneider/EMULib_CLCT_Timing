// $Id: NotificationManagerService.h,v 1.9 2008/07/18 15:27:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_NotificationManagerService_h_
#define _ws_service_NotificationManagerService_h_

#include <string>
#include "toolbox/lang/Class.h"
#include "ws/eventing/ServiceAdapterBase.h"
#include "ws/eventing/NotificationManager.h"
#include "ws/eventing/PeerTransportService.h"
#include "ws/eventing/PublisherBase.h"
#include "xoap/MessageReference.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "toolbox/ActionListener.h"
#include "xdaq/Object.h"
#include "xdata/UnsignedInteger64.h"

#include "ws/service/Statistics.h"

namespace ws
{
	namespace service
	{
		class NotificationManagerService: 
			public xdaq::Object,
			public ws::eventing::ServiceAdapterBase, 
			public ws::eventing::NotificationManager, 
			public toolbox::lang::Class, 
			public toolbox::ActionListener
		{     
      			public:
				virtual ~NotificationManagerService(){}

				NotificationManagerService
				(
					xdaq::Application* owner,
					ws::eventing::StorageAdapter * sa, 
					ws::eventing::PeerTransportService * pts,
					ws::service::Statistics * statistics
				);

                /*! Forward an incoming SOAP \param message to all subscribers.
                    If the deadband algorithm requires a high QoS message to wait
                    for availability of the internal queue, allow for a maximum
                    number of retries (\param maxRetry), for each retry wait
                    \param waitRetry milliseconds.
                    By default maxRetry is 5 and the wait time is 1000 milliseconds
                 */ 
				bool fireSubscription
				(
					xoap::MessageReference & message,
					size_t maxRetry,
					size_t waitRetry
				);

				/*void cancelSubscription 
				(
					toolbox::net::URL & code, 
					const std::string & reason, 
					const std::string & culturename
				);*/
				void actionPerformed (toolbox::Event & event);
				
				// Tolerance on congestion need to be monitored somehow, but this at the moment is for
				// testing purposes
				void resetCounters();
				
				xdata::UnsignedInteger64T & getIncomingMessagesLossCounter();
				xdata::UnsignedInteger64T & getOutgoingMessagesLossCounter();
				xdata::UnsignedInteger64T & getIncomingMessagesCounter();
				xdata::UnsignedInteger64T & getOutgoingMessagesCounter();
				
				xdata::UnsignedInteger64T getMessageRate();


			protected:
			
				// Publisher objects, ordered by "delivery mode"
				//
				std::map<std::string, ws::eventing::PublisherBase*> publishers_;
				toolbox::task::AsynchronousEventDispatcher dispatcher_;	
				
				xdata::UnsignedInteger64T incomingMessagesLossCounter_;	
				xdata::UnsignedInteger64T outgoingMessagesLossCounter_;	
				xdata::UnsignedInteger64T incomingMessagesCounter_;	
				xdata::UnsignedInteger64T outgoingMessagesCounter_;
				
				xdata::UnsignedInteger64T lastIncomingMessagesCounter_;	
				xdata::UnsignedInteger64T lastMeasuredTime_;	

				ws::service::Statistics * statistics_;
		};
	}
}

#endif


