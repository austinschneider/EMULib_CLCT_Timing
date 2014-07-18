// $Id: BufPoolEntry.h,v 1.10 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_BufPoolEntry_h_
#define _toolbox_mem_BufPoolEntry_h_

#include <iostream>
#include <set>
#include "toolbox/BSem.h"
#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/Buffer.h"
#include "toolbox/mem/SmartBufPool.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"


namespace toolbox 
{

	namespace mem
	{
		//! Encapsulates a pool of buffers for a given size
		//	
		class BufPoolEntry
		{
			public:

			BufPoolEntry (size_t blockSize, toolbox::mem::Allocator * allocator)
				throw (toolbox::mem::exception::FailedCreation);

			~BufPoolEntry();

			Buffer * alloc (toolbox::mem::Pool* pool)
				throw (toolbox::mem::exception::FailedAllocation);

			void free( toolbox::mem::Buffer * block )
				throw (toolbox::mem::exception::FailedDispose);

			//! Returns the allocated blocks to the allocator
			//! 
			void invalidate()
				throw (toolbox::mem::exception::FailedDispose);

			size_t blockLen();

			void show();
			
			size_t getNumberOfAllocatedBlocks();
			size_t getNumberOfCachedBlocks();
			size_t getNumberOfCreatedBlocks();
			
			private:

				size_t blockSize_;
				toolbox::mem::Allocator * allocator_;
				toolbox::mem::Buffer ** free_;
				std::set<toolbox::mem::Buffer*> remember_;

				size_t first_;
				size_t last_;
				size_t num_;
				size_t log2size_;
				size_t created_;
		};

	}
}

#endif
