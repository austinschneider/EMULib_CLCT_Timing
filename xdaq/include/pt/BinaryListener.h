// $Id: BinaryListener.h,v 1.2 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_BinaryListener_h_
#define _pt_BinaryListener_h_

#include <string>
#include <exception>
#include "pt/Listener.h"
#include "toolbox/mem/Reference.h"
#include "pt/exception/Exception.h"

namespace pt
{

//! A concrete Listener inherits from this class and implements a callback
//! corresponding to the service type
//
class BinaryListener: public pt::Listener
{
	public:
	virtual ~BinaryListener()
	{
	}
	
	//! User provides an implementation for processing the incoming SOAP message
	//
	virtual void processIncomingMessage (toolbox::mem::Reference* msg) throw (pt::exception::Exception) = 0;
	
	
};

}

#endif
