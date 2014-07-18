// $Id: Pool.h,v 1.12 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Pool_h_
#define _toolbox_mem_Pool_h_

#include "toolbox/ActionListener.h"
#include "toolbox/mem/exception/FailedDispose.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/InvalidThreshold.h"
#include "toolbox/mem/Usage.h"

namespace toolbox 
{
	namespace mem
	{
		class Buffer;
		class Allocator;

		class Pool
		{
			public:

			virtual ~Pool() {} // make compiler happy

			/*! Return a buffer of a given \param size in Bytes or 0 if none is available.
				A buffer with of the length that matches closest the \param size parameter
				using a log2 calculation is returned if the system provides enough
				free memory (e.g. alloc(1000) returns a buffer of 1024 Bytes).
			*/
			virtual mem::Buffer * alloc (size_t size) 
				throw (toolbox::mem::exception::FailedAllocation) = 0;

			//! Return a \param buffer to the pool
			//
			virtual void free (mem::Buffer* buffer) 
				throw (toolbox::mem::exception::FailedDispose) = 0;

			//! Perform thread safe locking to the pool
			//
 			virtual void lock () = 0;

			//! Unlock the previously locked pool
			//
			virtual void unlock () = 0;

			//! Returns the usage threshold value of this memory pool in bytes
			//
			virtual size_t getHighThreshold () = 0;
			virtual size_t getLowThreshold () = 0;

			//! Set the threshold of this memory pool to the given nbytes memory
			//
			virtual void setHighThreshold ( size_t nbytes ) throw (toolbox::mem::exception::InvalidThreshold) = 0;
			virtual void setLowThreshold ( size_t nbytes ) throw (toolbox::mem::exception::InvalidThreshold) = 0;
			
			//! Gets the current used memory in bytes
			//
			//virtual size_t getUsed() = 0;
			
			//Gets the current memory usage record
			virtual toolbox::mem::Usage & getMemoryUsage() = 0;

			//! Test if the memory usage of this memory pool reaches or exceeds its usage threshold value
			//
			virtual bool isHighThresholdExceeded () = 0;
			virtual bool isLowThresholdExceeded () = 0;

			//! additional methods for memory handling
			//
			virtual Allocator * getAllocator() = 0;

			//! Recycle all cached memory blocks into the commited memory area 
			//
			virtual void invalidate() 
				throw (toolbox::mem::exception::FailedDispose) = 0;

			//! Recycle all cached memory of the block size closest to the given size into the commited memory area 
			//
			virtual void invalidate(size_t size) 
				throw (toolbox::mem::exception::FailedDispose) = 0;
				
			//! Add a listener to the pool for threshold events
			//
			virtual void addActionListener (toolbox::ActionListener* listener) = 0;
			
			//! Remove a pool listener
			//
			virtual void removeActionListener (toolbox::ActionListener* listener) throw (toolbox::exception::Exception) = 0;


		};
	}
}

#endif
