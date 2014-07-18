// $Id: PostDescriptor.h,v 1.5 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_PostDescriptor_h_
#define _pt_tcp_PostDescriptor_h_

#include "toolbox/mem/Reference.h"
#include "pt/tcp/Channel.h"
#include "toolbox/exception/Handler.h"
#include "xdata/Properties.h"

namespace pt {
namespace tcp {
	
	enum ConnectionType
        {
                Unknown                 = 0,
                KeepAlive               = 1,
                Close                   = 2

        };

	
	struct PostDescriptor {
		toolbox::mem::Reference * ref;
		tcp::Channel * channel;
		toolbox::exception::HandlerSignature * handler;
		void * context;
		uint32_t signature;
		ConnectionType connection; // "keep-alive" or "close"
			/*
		bool operator == (const PostDescriptor & object)
		{
			if ((ref == object.ref) && (channel == object.channel ))
				return true;
			else 
				return false;
		}
		*/
	}; 
	
	
}
}
#endif
