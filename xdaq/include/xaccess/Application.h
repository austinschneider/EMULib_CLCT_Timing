// $Id: Application.h,v 1.2 2008/07/18 15:27:56 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xaccess_Application_h_
#define _xaccess_Application_h_

#include <map>

#include "xdaq/Application.h"
#include "xdata/String.h"
#include "xdata/ActionListener.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPResponseHeader.h"
#include "cgicc/HTMLDoctype.h"

#include "pt/SecurityPolicy.h"

namespace xaccess {

class Application: public xdaq::Application, public xdata::ActionListener
{	
	public:
		
	XDAQ_INSTANTIATOR();
	
	Application(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
	
	//! Default web page displayed when showing the application
	//
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	//! Implementation of interface from xdata::ActionListener
	//
	void actionPerformed(xdata::Event& e);
	
	protected:
	
	xdata::String htaccess_;	
};
}
#endif
