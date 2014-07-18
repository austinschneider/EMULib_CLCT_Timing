// $Id: Messenger.h,v 1.6 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_Messenger_h_
#define _pt_Messenger_h_

#include <string>

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace pt
{

//! This class is used to send a message over a Peer Transport
//
class Messenger
{
	public:
	
	virtual ~Messenger() {};
	
	typedef toolbox::mem::CountingPtr<Messenger, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	//! A concrete messenger inherits from the interface and implements send functions
	virtual std::string getService() = 0;
};

} 

#endif
