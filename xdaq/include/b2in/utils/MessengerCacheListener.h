// $Id: MessengerCacheListener.h,v 1.2 2008/07/18 15:26:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_MessengerCacheListener_h_
#define _b2in_utils_MessengerCacheListener_h_

#include <vector>
#include <map>
#include <string>
#include "xcept/Exception.h"


namespace b2in 
{
	namespace utils
	{
		//! This class maintains a cache of messenger pointers for fast access to 
		//! the messenger by giving a source and destination tid.
		//
		class MessengerCacheListener 
		{
			public:

			virtual ~MessengerCacheListener()
			{
			}

			virtual void asynchronousExceptionNotification(xcept::Exception& e) = 0;
		};
	}
}

#endif







