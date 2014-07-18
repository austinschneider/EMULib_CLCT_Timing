// $Id: PublishJobEvent.h,v 1.2 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_PublishJopEvent_h_
#define _xplore_PublishJobEvent_h_

#include <string>
#include <map>
#include "toolbox/Event.h"
#include "xplore/Advertisement.h"

namespace xplore
{
	
	class PublishJobEvent: public toolbox::Event
	{
		public:

		PublishJobEvent(xplore::Advertisement::Reference adv);

		~PublishJobEvent();

		xplore::Advertisement::Reference adv_;

	};
	
}
#endif
