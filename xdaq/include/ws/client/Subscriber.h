// $Id: Subscriber.h,v 1.3 2008/07/18 15:27:47 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_Subscriber_h_
#define _ws_Service_Subscriber_h_

#include <string>

#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 

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
#include "ws/eventing/PeerTransportService.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

namespace ws 
{
	namespace client 
	{
		class Subscriber: public xdaq::Application,  public xdata::ActionListener
		{
			public:

			XDAQ_INSTANTIATOR();

			Subscriber(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Subscriber();

			void actionPerformed (xdata::Event& e) ;

			//
			// SOAP Callback to reset the state machine
			//
			xoap::MessageReference onMessage (xoap::MessageReference msg) throw (xoap::exception::Exception);

			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

			protected:
						
		};
	}
}

#endif
