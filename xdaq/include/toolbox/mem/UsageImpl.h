// $Id: UsageImpl.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_UsageImpl_h_
#define _toolbox_mem_UsageImpl_h_

#include "toolbox/mem/Usage.h"

namespace toolbox {

namespace mem {

	class SmartBufPool;
	
	class UsageImpl: public toolbox::mem::Usage 
	{
		public:
		
		UsageImpl(toolbox::mem::SmartBufPool * pool);
		
		virtual ~UsageImpl();
		
		// Returns the amount of memory in bytes that is committed for the pool to use.
		size_t getCommitted();
		
		// Returns the amount of used memory in bytes
		size_t getUsed();
		
		// Returns the maximum amount of memory in bytes that can be used for memory management
		size_t getMax();
		
		// Return the number of blocks allocated and currently in used for a given size
		size_t getAllocatedBlocks(size_t size);
		
		// Return the number of blocks that are ready to be allocated
		size_t getCachedBlocks(size_t size);
		
		// Return the sizes of cached/allocated blocks
		std::vector<size_t> getBlockSizes();
		
		// Return the number of blocks allocated and currently in used for all used size, key is the size
		// and the value is the number of blocks
		std::map<size_t, size_t, std::less<size_t> >& getAllocatedBlocks();
		
		// Return the number of blocks that are  ready to be allocated for all used sizes, key is the size
		// and the value is the number of blocks
		std::map<size_t, size_t, std::less<size_t> >& getCachedBlocks();
		
		// Return the number of blocks that have been created for all used sizes, key is the size
		// and the value is the number of blocks (this gives the amount of romatted memory)
		std::map<size_t, size_t, std::less<size_t> >& getCreatedBlocks();
		
		private:
		
		toolbox::mem::SmartBufPool * pool_;
		std::map<size_t, size_t, std::less<size_t> > allocatedBlocksMap_;
		std::map<size_t, size_t, std::less<size_t> > cachedBlocksMap_;
		std::map<size_t, size_t, std::less<size_t> > createdBlocksMap_;
	};
}}

#endif
