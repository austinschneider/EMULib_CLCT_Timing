// $Id: Usage.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Usage_h_
#define _toolbox_mem_Usage_h_

#include <map>
#include <vector>
#include <cstddef>


namespace toolbox {

namespace mem {
	
	class Usage {
	
		public:
		virtual ~Usage()
		{
		}

		// Returns the amount of memory in bytes that is committed for the pool to use.
		virtual size_t getCommitted() = 0;
		
		// Returns the amount of used memory in bytes
		virtual size_t getUsed() = 0;
		
		// Returns the maximum amount of memory in bytes that can be used for memory management
		virtual size_t getMax() = 0;
		
		// Return the number of blocks allocated and currently in used for a given size
		virtual size_t getAllocatedBlocks(size_t size) = 0;
		
		// Return the number of blocks that are ready to be allocated
		virtual size_t getCachedBlocks(size_t size) = 0;
		
		// Return the sizes of cached/allocated blocks
		virtual std::vector<size_t> getBlockSizes() = 0;
		
		// Return the number of blocks allocated and currently in used for all used size, key is the size
		// and the value is the number of blocks
		virtual std::map<size_t, size_t, std::less<size_t> > &getAllocatedBlocks() = 0;
		
		// Return the number of blocks that are  ready to be allocated for all used sizes, key is the size
		// and the value is the number of blocks
		virtual std::map<size_t, size_t, std::less<size_t> > &getCachedBlocks() = 0;
		
		// Return the number of blocks that have been created for all used sizes, key is the size
		// and the value is the number of blocks (this gives the amount of romatted memory)
		virtual std::map<size_t, size_t, std::less<size_t> >& getCreatedBlocks() = 0;
		
	};
}}

#endif
