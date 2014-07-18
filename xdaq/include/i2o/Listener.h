// $Id: Listener.h,v 1.3 2008/07/18 15:26:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_Listener_h_
#define _i2o_Listener_h_

#include <string>
#include <exception>
#include "pt/BinaryListener.h"
#include "pt/exception/Exception.h"
#include "toolbox/mem/Reference.h"

namespace i2o
{

//! A concrete Listener inherits from this class and implements a callback
//! corresponding to the service type
//
class Listener: public pt::BinaryListener
{
	public:
	virtual ~Listener()
	{
	}

	//! Return the type of listener according the service for which it is implemented
	//
	std::string getService()
	{
		return "i2o";
	}
	
	//! User provides an implementation for processing the incoming SOAP message
	//
	virtual void processIncomingMessage (toolbox::mem::Reference* msg) throw (pt::exception::Exception) = 0;
	
	
};

}

#endif
