// $Id: NotificationManager.h,v 1.5 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_NotificationManager_h_
#define _ws_eventing_NotificationManager_h_

#include <string>
#include "toolbox/net/URL.h"
#include "xoap/MessageReference.h"

namespace ws
{
	namespace eventing
	{

	    class NotificationManager
	    {
	    	public:
		virtual ~NotificationManager()
		{
		}

        	//
        	virtual bool fireSubscription 
		(
			xoap::MessageReference & message, size_t maxRetry, size_t waitRetry
		) = 0;

        	/*
        	virtual void cancelSubscription 
		(
			toolbox::net::URL & code, 
			const std::string & reason, 
			const std::string & culturename
		) = 0;
		*/
	    };
	}
}

#endif


