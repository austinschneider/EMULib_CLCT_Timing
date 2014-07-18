// $Id: Listener.h,v 1.3 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Listener_h_
#define _xgi_Listener_h_

#include <string>
#include <exception>

#include "pt/Listener.h"
#include "xgi/Input.h"
#include "xgi/Output.h"
#include "pt/exception/Exception.h"


namespace xgi
{

//! A concrete Listener inherits from this class and implements a callback
//! corresponding to the service type
//
class Listener: public pt::Listener
{
	public:
	virtual ~Listener()
	{
	}

	//! Return the type of listener according the service for which it is implemented
	//
	std::string getService()
	{
		return "cgi";
	}
	
	//! User provides an implementation for processing the incoming SOAP message
	//
	virtual void processIncomingMessage (xgi::Input* in, xgi::Output * out ) throw (pt::exception::Exception) = 0;
	
	
};

}

#endif

