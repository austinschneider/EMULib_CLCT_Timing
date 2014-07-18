// $Id: WebApplication.h,v 1.4 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_WebApplication_h_
#define _xdaq_WebApplication_h_

#include <string>

#include "xdaq/Application.h"

#include "xgi/Input.h"
#include "xgi/Output.h"
#include "xgi/exception/Exception.h"

namespace xdaq
{

class WebApplication: public xdaq::Application
{
	public:
	
	WebApplication(xdaq::ApplicationStub * c) throw (xdaq::exception::Exception);
	
	virtual ~WebApplication();

	// Interface to exported parameters
	virtual void ParameterGet (xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
	virtual void ParameterSet (xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
	virtual void ParameterQuery (xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);
	virtual void Default (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	virtual void Empty (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
};

}

#endif


