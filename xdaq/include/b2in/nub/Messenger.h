// $Id: Messenger.h,v 1.5 2008/07/18 15:26:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_nub_Messenger_h_
#define _b2in_nub_Messenger_h_

#include <string>
#include "pt/Messenger.h"
#include "pt/exception/Exception.h"
#include "pt/Address.h"
#include "xdata/Properties.h"
#include "toolbox/mem/Reference.h"
#include "xdata/Properties.h"
#include "toolbox/exception/Handler.h"
#include "b2in/nub/exception/InternalError.h"
#include "b2in/nub/exception/QueueFull.h"
#include "b2in/nub/exception/OverThreshold.h"

namespace b2in 
{

namespace nub 
{

//! This class is used to send a message over a Peer Transport
//
class Messenger: public pt::Messenger
{
	public:
	
	//! A concrete messenger inherits from the interface and implements send functions
	std::string getService()
	{
		return "b2in";
	}
	
	virtual void send (toolbox::mem::Reference* msg, xdata::Properties & plist, toolbox::exception::HandlerSignature* handler, void* context)
                        throw (b2in::nub::exception::InternalError, b2in::nub::exception::QueueFull, b2in::nub::exception::OverThreshold) = 0;
	virtual pt::Address::Reference getLocalAddress() = 0;
	virtual  pt::Address::Reference getDestinationAddress() = 0;

};

}}

#endif
