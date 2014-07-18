// $Id: CommittedHeapBuffer.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_CommittedHeapBuffer_h_
#define _toolbox_mem_CommittedHeapBuffer_h_

#include "toolbox/mem/Buffer.h"
#include "toolbox/mem/Pool.h"

namespace toolbox 
{
	namespace mem
	{
		//! A class to wrap a block of allocated memory
		/*! This class shall be used within XDAQ to handle memory
		    blocks that have not been allocated using any of the
		    XDAQ methods, e.g. frameAlloc. It will release the contained
		    memory block at destruction time of the object. 
		    For the moment, no reference counting is implemented and
		    therefore the copy constructor is not supported.
		*/
		class CommittedHeapBuffer: public Buffer 
		{	
			public:

			//! Create a buffer from an externally allocated chunk of memory
			/*! Upon deletion of a HeapBuffer object, the externally allocated
			    memory block will also be deleted.
			*/
			CommittedHeapBuffer(toolbox::mem::Pool * pool, size_t size, void* address);

			protected:

			// For the time being, forbid the copy constructor
			CommittedHeapBuffer (const CommittedHeapBuffer& c) : Buffer(c)
			{}
		};
	}
}

#endif
