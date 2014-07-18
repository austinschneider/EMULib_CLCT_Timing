// $Id: IncomingDataEvent.h,v 1.2 2008/07/18 15:28:17 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_IncomingDataEvent_h_
#define _xmas_collector2g_IncomingDataEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "xdata/Properties.h"
#include "toolbox/mem/Reference.h"
#include "xmas/exception/Exception.h"

namespace xmas
{
	namespace collector2g
	{
		// forward declaration
		class Application;
		
		class IncomingDataEvent:  public toolbox::Event
		{
			public:
			
			IncomingDataEvent
			(
				toolbox::mem::Reference* ref,
				xdata::Properties& plist,
				Application* collector
			);
			
			~IncomingDataEvent();
			
			std::string name_;
			toolbox::mem::Reference* ref_;
			xdata::Properties plist_;	
			Application* collector_;	
		};
	}
}
#endif
