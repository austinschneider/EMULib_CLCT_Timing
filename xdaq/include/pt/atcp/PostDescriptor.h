// $Id: PostDescriptor.h,v 1.1 2007/03/31 14:23:36 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_PostDescriptor_h_
#define _atcp_PostDescriptor_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include "toolbox/mem/Reference.h"
#include "pt/atcp/Channel.h"
#include "toolbox/exception/Handler.h"

namespace pt {
namespace atcp {
	
	
	struct PostDescriptor {
		toolbox::mem::Reference * ref;
		pt::atcp::Channel * channel;
		toolbox::exception::HandlerSignature * handler;
		void * context;
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
