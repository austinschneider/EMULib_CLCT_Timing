
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _pt_JxtaListener_h_
#define _pt_JxtaListener_h_

#include <string>
#include <exception>
#include "pt/Listener.h"

namespace pt
{

//! A concrete Listener inherits from this class and implements a callback
//! corresponding to the service type
//
class JxtaListener: public pt::Listener
{
	public:
	
	//! Return the type of listener according the service for which it is implemented
	//
	std::string getService()
	{
		return "Pipe";
	}
	
	//! User provides an implementation for processing the incoming Jxta message
	//
	virtual void processIncomingMessage (std::string msg) throw (std::exception) = 0;

	
};

}

#endif
