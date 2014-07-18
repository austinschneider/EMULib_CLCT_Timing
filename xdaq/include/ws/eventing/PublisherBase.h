// $Id: PublisherBase.h,v 1.3 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_PublisherBase_h_
#define _ws_eventing_PublisherBase_h_

#include "ws/eventing/Subscription.h"
#include "ws/eventing/exception/InternalError.h"
#include "xoap/MessageReference.h"

namespace ws
{
namespace eventing
{
	class PublisherBase
	{
		public:
		virtual ~PublisherBase()
		{
		}

		virtual
		void deliverMessage (xoap::MessageReference& msg, ws::eventing::Subscription& subscription)
			throw (ws::eventing::exception::InternalError) = 0;
	};


}

}

#endif


