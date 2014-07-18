// $Id: Subscription.h,v 1.2 2008/07/18 15:26:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini and G. Lo Presti			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_eventing_Subscription_h_
#define _b2in_eventing_Subscription_h_

#include <string>
#include "toolbox/TimeVal.h"

namespace b2in
{
	namespace eventing
	{
		typedef struct {
			toolbox::TimeVal expires;
			std::string url;
			std::string topic;
			std::string uuid;
			std::string service;
		} Subscription;
	}
}
#endif
