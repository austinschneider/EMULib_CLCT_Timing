// $Id: Allocator.h,v 1.6 2007/06/08 08:30:57 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pheaps_memphys_Allocator_h_
#define _pheaps_memphys_Allocator_h_


#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/MemoryPartition.h"
#include "toolbox/mem/exception/OutOfMemory.h"
#include "toolbox/mem/exception/FailedCreation.h"

namespace pheaps 
{

	namespace memphys
	{
		class Allocator: public toolbox::mem::Allocator 
		{
			public:

			Allocator(size_t committedSize) 
				throw (toolbox::mem::exception::OutOfMemory, toolbox::mem::exception::FailedCreation);

			virtual ~Allocator();

			//! Allocate a buffer from conventional memory of a given size
			toolbox::mem::Buffer * alloc(size_t size, toolbox::mem::Pool * pool) 
				throw (toolbox::mem::exception::FailedAllocation);

			//! Call delete on the Buffer
			/*! This calls delete on the Buffer */
			void free ( toolbox::mem::Buffer * buffer )
				throw (toolbox::mem::exception::FailedDispose);

			std::string type();

			bool isCommittedSizeSupported();

			size_t getCommittedSize();	

			/*! Retrieve the number of byte currently used
				*/
			size_t getUsed();

			private:

			size_t committedSize_;
			size_t numberOfChunks_;
			size_t chunkSize_;
			toolbox::mem::MemoryPartition memPartition_;
			struct alloc_info ai_; // rembember what has been allocated
			int fd_; // file descriptor of physical memory device
		};
	}
}

#endif
