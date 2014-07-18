// $Id: Allocator.h,v 1.4 2006/09/06 12:48:53 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pheaps_cmem_rcc_Allocator_h_
#define _pheaps_cmem_rcc_Allocator_h_

#include <list>

#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/MemoryPartition.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedDispose.h"
#include "cmem_rcc/cmem_rcc_common.h"


namespace pheaps 
{
	namespace cmem_rcc
	{
		class Allocator: public toolbox::mem::Allocator 
		{
			public:

			Allocator(size_t committedSize) 
				throw (toolbox::mem::exception::FailedCreation);

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
			toolbox::mem::MemoryPartition memPartition_;			
			int fd_; // file descriptor of physical memory device
			std::list<cmem_rcc_t> chunks_;
		};
	}
}

#endif
