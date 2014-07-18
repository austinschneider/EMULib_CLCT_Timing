// $Id: Dispatcher.h,v 1.3 2008/07/18 15:26:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_nub_Dispatcher_h_
#define _b2in_nub_Dispatcher_h_

#include <string>
#include <sstream>
#include "b2in/nub/Listener.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationRegistry.h"
#include "toolbox/mem/Reference.h"
#include "log4cplus/logger.h"
#include "pt/exception/Exception.h"
#include "xdata/Properties.h"

namespace b2in 
{

namespace nub
{

class Dispatcher : public b2in::nub::Listener 
{
	public:
	
	Dispatcher(xdaq::ApplicationContext* context, log4cplus::Logger & logger);
	virtual ~Dispatcher();
	
	void processIncomingMessage (toolbox::mem::Reference* msg, xdata::Properties& plist) 
		throw (b2in::nub::exception::Exception);
	
	protected:
	
	Logger  logger_;
	xdaq::ApplicationRegistry* registry_;
	xdaq::ApplicationContext* context_; // for access to frameFree function
};

}}

#endif
