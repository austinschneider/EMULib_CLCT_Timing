// $Id: InstantiateApplicationEvent.h,v 1.3 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_InstantiateApplicationEvent_h_
#define _xdaq_InstantiateApplicationEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"
#include "xdaq/ApplicationDescriptor.h"

namespace xdaq 
{

class InstantiateApplicationEvent: public toolbox::Event
{
	public:
	
	// typedef toolbox::mem::CountingPtr<InstantiateApplicationEvent, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	InstantiateApplicationEvent(xdaq::ApplicationDescriptor* d)
		: toolbox::Event("urn:xdaq-event:InstantiateApplication", 0)
	{
		descriptor_ = d;
	}
	
	InstantiateApplicationEvent(xdaq::ApplicationDescriptor* d, void* originator)
		: toolbox::Event("urn:xdaq-event:InstantiateApplication", originator)
	{
		descriptor_ = d;
	}
	
	xdaq::ApplicationDescriptor* getApplicationDescriptor()
	{
		return descriptor_;
	}
		
	protected:
	
	xdaq::ApplicationDescriptor* descriptor_;
	
};

}

#endif
