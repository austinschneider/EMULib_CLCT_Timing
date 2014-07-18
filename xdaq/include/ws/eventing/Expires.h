// $Id: Expires.h,v 1.7 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_Expires_h_
#define _ws_eventing_Expires_h_

#include <string>
#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"
#include "xoap/SOAPElement.h"
#include "xoap/SOAPEnvelope.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/eventing/exception/fault/InvalidExpirationType.h"
#include "ws/eventing/exception/fault/UnsupportedExpirationType.h"
namespace ws
{
namespace eventing
{
    class Expires 
    {     
      	public:
	
	//! Empty constructor sets expires to no timeout
	//
 	Expires(toolbox::TimeVal & value);
    
        Expires(toolbox::TimeInterval & value);

	Expires();
	
      	Expires(xoap::SOAPElement e );
		
        toolbox::TimeVal calculateAbsoluteExpiratonTime() throw (ws::eventing::exception::fault::InvalidExpirationType);
	
 	void setExpires(toolbox::TimeVal & value);
    
        void setExpires(toolbox::TimeInterval & value);
	
        bool isValidTime(bool throwex) throw (ws::eventing::exception::fault::InvalidExpirationType);
	
        bool isDurationTime(bool throwex) throw (ws::eventing::exception::fault::UnsupportedExpirationType);
	
	void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope);
	
	protected:
	
	std::string expires_ ;
    };
}
}
#endif


