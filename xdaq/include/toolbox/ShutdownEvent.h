// $Id: ShutdownEvent.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_ShutdownEvent_h_
#define _toolbox_ShutdownEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace toolbox 
{

class ShutdownEvent: public toolbox::Event
{
	public:
	
	//typedef toolbox::mem::CountingPtr<ShutdownEvent, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	ShutdownEvent(): toolbox::Event("Shutdown",0)
	{
	
	}
	
	ShutdownEvent(void* originator): toolbox::Event("Shutdown",originator)
	{
	
	}
	
		
	protected:
};

}

#endif
