// $Id: Messenger.h,v 1.2 2008/07/18 15:26:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_Messenger_h_
#define _i2o_Messenger_h_

#include <string>
#include "pt/BinaryMessenger.h"

namespace i2o
{

//! This class is used to send a message over a Peer Transport
//
class Messenger: public pt::BinaryMessenger
{
	public:
	
	//! A concrete messenger inherits from the interface and implements send functions
	std::string getService()
	{
		return "i2o";
	}
	
	
};

} 

#endif
