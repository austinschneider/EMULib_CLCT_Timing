// $Id: MessageFilter.h,v 1.1 2008/05/20 11:37:41 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_MessageFilter_h_
#define _ws_eventing_MessageFilter_h_

#include "toolbox/string.h"
#include "xoap/MessageReference.h"
#include "xoap/SOAPElement.h"


namespace ws
{
namespace eventing 
{
	class MessageFilter
	{      
	public:
		MessageFilter() { };
		virtual ~MessageFilter() { };
	
		virtual void fromSOAP( xoap::SOAPElement& element) = 0;

		virtual void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope) = 0;

		virtual MessageFilter* clone() const = 0;

		virtual const std::string& getFilterDialect() const = 0;

		virtual const std::string& toString() const = 0;

		virtual bool matches( xoap::MessageReference msg) = 0;
	};
}
}

#endif

