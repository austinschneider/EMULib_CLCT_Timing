// $Id: SOAPDispatcher.h,v 1.2 2008/07/18 15:26:47 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _executive_SOAPDispatcher_h_
#define _executive_SOAPDispatcher_h_


#include <string>
#include "pt/SOAPListener.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationRegistry.h"
#include "xdaq/ApplicationGroup.h"
#include "xoap/MessageReference.h"
#include "log4cplus/logger.h"
#include "pt/exception/Exception.h"

namespace executive
{

class SOAPDispatcher: public pt::SOAPListener
{
	
	public:
	
	SOAPDispatcher(xdaq::ApplicationContext* context, log4cplus::Logger & logger);
	virtual ~SOAPDispatcher();
	
	xoap::MessageReference processIncomingMessage (xoap::MessageReference msg) 
		throw (pt::exception::Exception);
	
	protected:
	
	xdaq::ApplicationContext*	context_;
	xdaq::ApplicationRegistry* 	registry_;
	Logger  			logger_;
};

}

#endif
