// $Id: HeapAllocator.h,v 1.7 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_HeapAllocator_h_
#define _toolbox_mem_HeapAllocator_h_

#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"

namespace toolbox 
{
	namespace mem
	{
		class HeapAllocator: public toolbox::mem::Allocator 
		{
			public:
			HeapAllocator();
			
			//! Allocate a buffer from conventional memory of a given size
			Buffer * alloc(size_t size, toolbox::mem::Pool * pool) throw (toolbox::mem::exception::FailedAllocation);

			//! Call delete on the Buffer
			/*! This calls delete on the Buffer */
			void free ( Buffer * buffer ) throw (toolbox::mem::exception::FailedDispose);
			
			std::string type();
			
			bool isCommittedSizeSupported();
	
			size_t getCommittedSize();
			
			size_t getUsed();
			
			private:
			
			size_t used_;	
		};
	}
}

#endif
