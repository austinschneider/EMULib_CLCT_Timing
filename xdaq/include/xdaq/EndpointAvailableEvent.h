// $Id: EndpointAvailableEvent.h,v 1.2 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_EndpointAvailableEvent_h_
#define _xdaq_EndpointAvailableEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"
#include "xdaq/Endpoint.h"
#include "xdaq/Network.h"

namespace xdaq 
{

	class EndpointAvailableEvent: public toolbox::Event
	{
		public:

		// typedef toolbox::mem::CountingPtr<EndpointAvailableEvent, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;

		EndpointAvailableEvent(xdaq::Endpoint* endpoint, xdaq::Network* network)
			: toolbox::Event("xdaq::EndpointAvailableEvent", 0)
		{
			endpoint_ = endpoint;
			network_ = network;
		}

		EndpointAvailableEvent(xdaq::Endpoint* endpoint, xdaq::Network* network, void* originator)
			: toolbox::Event("xdaq::EndpointAvailableEvent", originator)
		{
			endpoint_ = endpoint;
			network_ = network;
		}

		xdaq::Endpoint* getEndpoint()
		{
			return endpoint_;
		}
		
		xdaq::Network* getNetwork()
		{
			return network_;
		}

		protected:

		xdaq::Endpoint* endpoint_;
		xdaq::Network* network_;

	};

}

#endif
