// $Id: PostDescriptor.h,v 1.3 2008/07/18 15:27:14 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_fifo_PostDescriptor_h_
#define _pt_fifo_PostDescriptor_h_

#include "toolbox/mem/Reference.h"
#include "toolbox/exception/Handler.h"

namespace pt
{
	namespace fifo
	{
		struct PostDescriptor 
		{
			toolbox::mem::Reference * ref;
			toolbox::exception::HandlerSignature * handler;
			void * context;
			uint32_t signature;
		}; 
	}
}
#endif
