// $Id: PersistedObject.h,v 1.3 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_PersistedObject_h_
#define _ws_eventing_PersistedObject_h_

#include "xdata/Serializable.h"
#include "ws/eventing/ResourceDescriptor.h"

namespace ws
{
namespace eventing
{   
    class PersistedObject //: System.Timers.Timer
    {        
	public:
	
        PersistedObject(ResourceDescriptor& rd, xdata::Serializable* resource);
	
	ResourceDescriptor& getResourceDescriptor();
	
	void setResourceDescriptor(ResourceDescriptor& rd);
        
	xdata::Serializable* getResource();
	
	void setResource (xdata::Serializable* resource);
	
	protected:
	
	ResourceDescriptor rd_;
	xdata::Serializable* resource_;
    };
}
}

#endif


