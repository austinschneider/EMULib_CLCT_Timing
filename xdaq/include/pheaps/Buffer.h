// $Id: Buffer.h,v 1.4 2006/09/20 16:24:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pheaps_Buffer_h_
#define _pheaps_Buffer_h_

// for getting PAGE_SIZE
#include<sys/types.h>
#include<sys/user.h>

#include "toolbox/mem/Buffer.h"
#include "toolbox/mem/Pool.h"

namespace pheaps 
{
	const size_t MemoryPageSize = PAGE_SIZE;
	
	class Buffer: public toolbox::mem::Buffer 
	{	
		public:

		//! Create a physical memory buffer wrapper to externally allocated chunk of memory
		/*! Upon deletion of a HeapBuffer object, the externally allocated
		    memory block will also be deleted. This is responsibility of the Allocator
		*/
		Buffer(toolbox::mem::Pool * pool, size_t size, void* address, void * physicalAddress, void * kernelAddress);

		void * getPhysicalAddress();
		void * getKernelAddress();


		protected:

		// For the time being, forbid the copy constructor
		Buffer (const Buffer& c) : toolbox::mem::Buffer(c)
		{}
		
		private:
		
		void * physicalAddress_;
 		void * kernelAddress_;
	};
	
	
}

#endif
