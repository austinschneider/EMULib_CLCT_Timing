// $Id: EventReference.h,v 1.2 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_EventReference_h_
#define _toolbox_task_EventReference_h_

#include "toolbox/Event.h"
#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace toolbox 
{
	namespace task 
	{
		typedef toolbox::mem::CountingPtr<toolbox::Event, toolbox::mem::ThreadSafeReferenceCount,toolbox::mem::StandardObjectPolicy> EventReference;
	}
}
#endif
