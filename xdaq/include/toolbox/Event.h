// $Id: Event.h,v 1.5 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Event_h_
#define _toolbox_Event_h_

#include <string>
#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace toolbox 
{

class Event
{
	public:
	
	typedef toolbox::mem::CountingPtr<Event, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	Event(const std::string & type, void* originator = 0);
	virtual ~Event();
	
	virtual std::string type();
	
	virtual void* originator();
		
	protected:
	
		std::string type_;
		void* originator_;
};

}

#endif
