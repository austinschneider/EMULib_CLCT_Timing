// $Id: XgiDispatcher.h,v 1.2 2008/07/18 15:26:47 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _executive_XgiDispatcher_h_
#define _executive_XgiDispatcher_h_


#include <string>
#include "xgi/Listener.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationRegistry.h"
#include "xdaq/ApplicationGroup.h"
#include "log4cplus/logger.h"
#include "pt/exception/Exception.h"
namespace executive
{

class XgiDispatcher: public xgi::Listener
{
	
	public:
	
	XgiDispatcher(xdaq::ApplicationContext* context, log4cplus::Logger & logger);
	virtual ~XgiDispatcher();
	
	void processIncomingMessage (xgi::Input * in, xgi::Output *out) 
		throw (pt::exception::Exception);
	
	protected:
	
	xdaq::ApplicationContext*	context_;
	xdaq::ApplicationRegistry* 	registry_;
	Logger  			logger_;
};

}

#endif
