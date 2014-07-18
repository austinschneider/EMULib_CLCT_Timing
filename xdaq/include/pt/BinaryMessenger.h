// $Id: BinaryMessenger.h,v 1.5 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_BinaryMessenger_h_
#define _pt_BinaryMessenger_h_

#include <string>

#include "pt/PeerTransport.h"
#include "pt/Listener.h"
#include "pt/Messenger.h"
#include "pt/Address.h"
#include "toolbox/mem/Reference.h"
#include "toolbox/exception/Handler.h"
#include "pt/exception/Exception.h"

namespace pt
{

//! This class is used to send a message over a Peer Transport
//
class BinaryMessenger: public pt::Messenger
{
	public:

	virtual ~BinaryMessenger() {};

	//! A Peer Transport must implement this send function by inheriting from this class
	//
	virtual void send (toolbox::mem::Reference* msg, toolbox::exception::HandlerSignature * handler, void * context) throw (pt::exception::Exception ) = 0;
	virtual pt::Address::Reference getLocalAddress() = 0;
	virtual pt::Address::Reference getDestinationAddress() = 0;
};

} 

#endif
