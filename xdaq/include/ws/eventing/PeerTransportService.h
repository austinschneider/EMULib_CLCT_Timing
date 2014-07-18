// $Id: PeerTransportService.h,v 1.3 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_PeerTransportService_h_
#define _ws_eventing_PeerTransportService_h_

#include "xoap/MessageReference.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/addressing/EndpointReference.h"
#include <string>

namespace ws
{    
namespace eventing
{    
	class PeerTransportService 
	{
	      public:
		virtual ~PeerTransportService()
		{
		}

	      	//! Implemented for each Web server using server specific technology for sending SOAP
		/* Do not forget to set the SOAPAction field using getMIMEHeaders on the request
	         */
		virtual xoap::MessageReference post(ws::addressing::EndpointReference& epa, xoap::MessageReference & request)
			throw (ws::eventing::exception::Exception) = 0;
	};
}

}

#endif 
