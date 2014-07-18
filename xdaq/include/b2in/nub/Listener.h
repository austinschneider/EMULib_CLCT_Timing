// $Id: Listener.h,v 1.4 2008/07/18 15:26:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_nub_Listener_h_
#define _b2in_nub_Listener_h_

#include <string>
#include <exception>
#include <stdint.h>
#include "pt/Address.h"
#include "pt/Listener.h"
#include "b2in/nub/exception/Exception.h"
#include "toolbox/mem/Reference.h"
#include "xdata/Properties.h"

namespace b2in
{

namespace nub {

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
		return "b2in";
	}
	
	//! User provides an implementation for processing the incoming message
	//
	virtual void processIncomingMessage (toolbox::mem::Reference* msg, xdata::Properties & plist)
 		throw (b2in::nub::exception::Exception) = 0;
	
	
};

}}

#endif
