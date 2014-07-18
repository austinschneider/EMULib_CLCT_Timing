// $Id: Dispatcher.h,v 1.4 2008/07/18 15:26:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_utils_Dispatcher_h_
#define _i2o_utils_Dispatcher_h_

#include <string>
#include <sstream>
#include "i2o/Listener.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationRegistry.h"
#include "toolbox/mem/Reference.h"
#include "log4cplus/logger.h"
#include "i2o/utils/AddressMap.h"
#include "pt/exception/Exception.h"

namespace i2o 
{

namespace utils
{

class Dispatcher : public i2o::Listener 
{
	public:
	
	Dispatcher(xdaq::ApplicationContext* context, log4cplus::Logger & logger);
	virtual ~Dispatcher();
	
	void processIncomingMessage (toolbox::mem::Reference* msg) throw (pt::exception::Exception);	
	
	protected:
	
	Logger  logger_;
	xdaq::ApplicationRegistry* registry_;
	xdaq::ApplicationContext* context_; // for access to frameFree function
	i2o::utils::AddressMap * addressMap_;
};

}}

#endif
