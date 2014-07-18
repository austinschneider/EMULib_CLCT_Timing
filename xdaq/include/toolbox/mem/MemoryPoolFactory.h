// $Id: MemoryPoolFactory.h,v 1.8 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_MemoryPoolFactory_h_
#define _toolbox_mem_MemoryPoolFactory_h_

#include "toolbox/mem/Pool.h"
#include <string>
#include <map>

#include "toolbox/mem/exception/DuplicateMemoryPool.h"
#include "toolbox/mem/exception/MemoryPoolNotFound.h"
#include "toolbox/mem/exception/AllocatorNotFound.h"
#include "toolbox/mem/exception/FailedCreation.h"

#include "toolbox/mem/Pool.h"
#include "toolbox/mem/ReferencePool.h"
#include "toolbox/mem/Allocator.h"

#include "toolbox/EventDispatcher.h"
#include "toolbox/ActionListener.h"

#include "toolbox/net/URN.h"


namespace toolbox 
{
	namespace mem
	{
		class MemoryPoolFactory
		{
			public:
			
			//! Retrieve a pointer to the toolbox::mem::MemoryPoolFactory singleton
			//
			static MemoryPoolFactory* getInstance();
			
			//! Destroy the manager and destroy all pools.
			//
			static void destroyInstance();

			//! Add a listener to the pool manager for events that announce that a pool is made available or revoked
			//
			void addActionListener (toolbox::ActionListener* listener);
			
			void removeActionListener (toolbox::ActionListener* listener) throw (toolbox::exception::Exception);

			//! Retrieves a list of all memory pool names that are managed by this factory.
			//
			std::vector<std::string> getMemoryPoolNames();

			//! Create a pool from an allocator configuration. The pool is available until removePool() is called.
			//
			toolbox::mem::Pool* createPool(toolbox::net::URN& urn, toolbox::mem::Allocator * allocator)
				throw (toolbox::mem::exception::DuplicateMemoryPool,
					toolbox::mem::exception::AllocatorNotFound,
					toolbox::mem::exception::FailedCreation);
					
			toolbox::mem::Pool* createPool(const std::string & name, toolbox::mem::Allocator * allocator)
				throw (toolbox::mem::exception::DuplicateMemoryPool,
					toolbox::mem::exception::AllocatorNotFound,
					toolbox::mem::exception::FailedCreation);
			//! Find a pool that has been created.
			//
			toolbox::mem::Pool* findPool(toolbox::net::URN& urn) 
				throw (toolbox::mem::exception::MemoryPoolNotFound);

			//! Make a pool unaccessible to users of the MemoryPoolFactory.
			/*! The pool is not destroyed, but made unaccessible to the user. Subsequent find
			    operations will not anymore reveal the pool. The pool is finally destroyed and
			    removed from the manager, when the cleanup() function is called.
			    */
			void removePool(toolbox::net::URN& urn) 
				throw (toolbox::mem::exception::MemoryPoolNotFound);
				
			//! Destroy a pool (remove pool and delete the pool object)
			/*! The pool is really destroyed and removed from the manager.
			    */
			void destroyPool(toolbox::net::URN& urn) 
				throw (toolbox::mem::exception::MemoryPoolNotFound);
											
			//! Allocate a buffer from the given pool, get a reference, associate the two and return the filled reference
			//
			toolbox::mem::Reference* getFrame (toolbox::mem::Pool* pool, size_t size)
				throw (toolbox::mem::exception::Exception);
				
			//! Remove unused memory pools from the manager.
			/*! Call this function only if sure that buffers of unused pools are no longer in
			    use by some application.
			*/
			void cleanup();

			private:
			
			// Forbid the empty constructor to avoid that someone instantiates this class
			MemoryPoolFactory();
			~MemoryPoolFactory();

			std::map<std::string, toolbox::mem::Pool *, std::less<std::string> > pools_;
			std::list<toolbox::mem::Pool*> unusedPools_;
			static MemoryPoolFactory* instance_;
			
			toolbox::EventDispatcher dispatcher_;
			toolbox::mem::ReferencePool referencePool_;
		};
		
		MemoryPoolFactory* getMemoryPoolFactory();

	}
}


#endif

