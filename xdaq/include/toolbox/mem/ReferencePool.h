// $Id: ReferencePool.h,v 1.6 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_ReferencePool_h_
#define _toolbox_mem_ReferencePool_h_

#include "assert.h"
#include "toolbox/BSem.h"
#include "toolbox/mem/SmartAllocator.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"

namespace toolbox 
{
	namespace mem
	{
		class Reference;
	
		//! A pool of buffer references
		class ReferencePool 
		{
			public:

			//! Constructor, \param num sets the maximum buffer references allowed in this pool
			ReferencePool(size_t num)
				throw (toolbox::mem::exception::FailedCreation);

			//! Destructor
			~ReferencePool();

			//! Provide mutual exclusive access to the pool to allocation/de-allocation purposes
    			void lock();

			//! Provide mutual exclusive access to the pool to allocation/de-allocation purposes
			void  unlock();

			//! Return a buffer reference to this pool
			void free(toolbox::mem::Reference * ref) 
				throw (toolbox::mem::exception::FailedDispose);

			//! Retrieve a buffer reference from this pool
			Reference * alloc() 
				throw (toolbox::mem::exception::FailedAllocation);

			protected:

			// Internal function to detect duplicate references	
			void checkDuplicates();

			private:

			toolbox::mem::SmartAllocator<toolbox::mem::Reference> references_;
			toolbox::BSem mutex_;

		};
	}
}

#endif
