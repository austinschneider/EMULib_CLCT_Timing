// $Id: PushPublisher.h,v 1.3 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_adapter_PushPublisher_h_
#define _ws_eventing_adapter_PushPublisher_h_

#include "ws/eventing/PublisherBase.h"
#include "ws/eventing/PeerTransportService.h"

namespace ws
{
	namespace eventing
	{
		namespace adapter
		{
			class PushPublisher: public ws::eventing::PublisherBase
			{
				public:
				virtual ~PushPublisher();

				PushPublisher(ws::eventing::PeerTransportService * pts);
				
				void deliverMessage (xoap::MessageReference& msg, ws::eventing::Subscription& subscription)
					throw (ws::eventing::exception::InternalError);
					
					
				ws::eventing::PeerTransportService * pts_;	
					
			};


		}

	}

}

#endif


