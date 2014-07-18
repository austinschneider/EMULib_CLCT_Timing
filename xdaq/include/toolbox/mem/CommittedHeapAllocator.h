// $Id: CommittedHeapAllocator.h,v 1.8 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_CommittedHeapAllocator_h_
#define _toolbox_mem_CommittedHeapAllocator_h_

#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/MemoryPartition.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"

namespace toolbox 
{
	namespace mem
	{
		class CommittedHeapAllocator: public toolbox::mem::Allocator 
		{
			public:
			
			CommittedHeapAllocator(size_t committedSize) 
				throw (toolbox::mem::exception::FailedCreation);

			virtual ~CommittedHeapAllocator();

			//! Allocate a buffer from conventional memory of a given size
			Buffer * alloc(size_t size, toolbox::mem::Pool * pool) 
				throw (toolbox::mem::exception::FailedAllocation);

			//! Call delete on the Buffer
			/*! This calls delete on the Buffer */
			void free ( Buffer * buffer )
				throw (toolbox::mem::exception::FailedDispose);
			
			std::string type();
			
			bool isCommittedSizeSupported();
	
			size_t getCommittedSize();	
			
			/*! Retrieve the number of byte currently used
			*/
			size_t getUsed();
			
			private:
			
			size_t committedSize_;
			char* buffer_;
			toolbox::mem::MemoryPartition memPartition_;
		};
	}
}

#endif
