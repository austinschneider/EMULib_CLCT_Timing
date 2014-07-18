
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _pt_JxtaMessenger_h_
#define _pt_JxtaMessenger_h_

#include <string>

#include "pt/Messenger.h"

namespace pt
{

//! This class is used to send a message over a Peer Transport
//
class JxtaMessenger: public pt::Messenger
{
	public:
	
	//! A concrete messenger inherits from the interface and implements send functions
	std::string getService()
	{
		return "pipe";
	}
	
	//! A Peer Transport must implement this send function by inheriting from this class
	//
	virtual void send (std::string message) = 0;
};

} 

#endif
