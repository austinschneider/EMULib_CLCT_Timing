// $Id: SOAPMessenger.h,v 1.3 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_SOAPMessenger_h_
#define _pt_SOAPMessenger_h_

#include <string>

#include "pt/Messenger.h"
#include "pt/exception/Exception.h"
#include "pt/Address.h"
#include "xoap/MessageReference.h"

namespace pt
{

//! This class is used to send a message over a Peer Transport
//
class SOAPMessenger: public pt::Messenger
{
	public:
	
	virtual ~SOAPMessenger() {};

	
	//! A concrete messenger inherits from the interface and implements send functions
	std::string getService()
	{
		return "soap";
	}
	
	//! A Peer Transport must implement this send function by inheriting from this class
	//
	virtual xoap::MessageReference send (xoap::MessageReference message) throw (pt::exception::Exception) = 0;
	
	virtual pt::Address::Reference getLocalAddress() = 0;
	virtual pt::Address::Reference getDestinationAddress() = 0;
};

} 

#endif
