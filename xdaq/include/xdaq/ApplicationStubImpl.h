// $Id: ApplicationStubImpl.h,v 1.5 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationStubImpl_h_
#define _xdaq_ApplicationStubImpl_h_

#include <string>
#include "xdaq/ApplicationStub.h"
#include "xdata/String.h"
#include "xdata/UnsignedLong.h"
#include "xdata/Properties.h"
#include "xdaq/exception/Exception.h"

// log4cplus includes
//
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

// log4cplus namespace
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

namespace xdaq
{

class ApplicationStubImpl: public ApplicationStub, public xdata::Properties
{
	public:
	
	//! Creation an ApplicationStub. A logger object needs to be passed for the application. It must be created before this class is instantiated
	//
	ApplicationStubImpl(xdaq::ApplicationContext* c, xdaq::ApplicationDescriptor* d, Logger& logger)
		throw (xdaq::exception::Exception);	
	
	//! Return the context of the application
	//
	xdaq::ApplicationContext* getContext();
	
	//! Return the application descriptor
	//
	xdaq::ApplicationDescriptor* getDescriptor();
	
	//! Return a logger object thas has been instantiated for the application. This is to be used by the application.
	//
	Logger & getLogger();
	
	//! Return the InfoSpace that is associated with the application (it contains the exported parameters)
	//
	xdata::InfoSpace* getInfoSpace();
		
	protected:
	
	xdaq::ApplicationContext* context_;
	xdaq::ApplicationDescriptor* descriptor_;
	xdata::InfoSpace *infoSpace_; 
	Logger logger_;
};

}

#endif
