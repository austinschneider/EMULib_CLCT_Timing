// $Id: XPathMessageFilter.h,v 1.7 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_XPathMessageFilter_h_
#define _ws_eventing_XPathMessageFilter_h_

#include "toolbox/string.h"
#include "xoap/MessageReference.h"
#include "xoap/SOAPElement.h"
#include "ws/eventing/exception/Exception.h"


namespace ws
{
namespace eventing
{
    class XPathMessageFilter
    {      
      	public:
	XPathMessageFilter();
	
	XPathMessageFilter(const std::string& filter);
	
     	XPathMessageFilter( xoap::SOAPElement& element);
	
	std::string getXPath();
	     
        protected:
      
   	std::string filter_;
    };
}
}

#endif
