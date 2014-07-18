// $Id: Buffer.h,v 1.5 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Buffer_h_
#define _toolbox_mem_Buffer_h_

#include "toolbox/mem/Pool.h"

namespace toolbox 
{
	namespace mem
	{
		class Buffer 
		{
			public:
			
			Buffer(toolbox::mem::Pool* pool, size_t size, void* address);
			
			//! Retrieve a pointer to the memory, usable in applications
			void * getAddress();

			//! Retrieve the size of the encapsulated data block in bytes
			size_t getSize();
			
			toolbox::mem::Pool* getPool();

			//! DTOR must be implemented by classes that implement the Buffer interface	
			virtual ~Buffer() {};
			
			
			// ----------------------------
			// Reference counting functions
			// ----------------------------
			
			//! Increment the reference counter of this buffer reference.
			void incrementRefCounter();

			//! Decrement the reference counter of this buffer reference.
			void decrementRefCounter();

			//! Retrieve the current value of the reference counter for this buffer reference.
			unsigned int getRefCounter();
			
			protected:
			
			// For the time being, forbid the copy constructor
			Buffer (const Buffer& c)
			{}
			
			unsigned int refCounter_; // reference counter
			size_t size_; // size of the encapsulated data block
			
			toolbox::mem::Pool* pool_; // pointer to pool from which the buffer was allocated
			void* address_;
						
		};
	}
}

#endif
