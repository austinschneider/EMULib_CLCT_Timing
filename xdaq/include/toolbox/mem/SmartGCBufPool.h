// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R.Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_SmartGCBufPool_h_
#define _toolbox_mem_SmartGCBufPool_h_

#include <iostream>

#include "toolbox/mem/SmartBufPool.h"

namespace toolbox 
{

namespace mem
{

//! Encapsulation of a pool of buffers that are pre allocated
//
class SmartGCBufPool: public toolbox::mem::SmartBufPool
{
	public:
	
	//! Create a smart buffer pool and pass an \param allocator that is used to allocate the memory blocks
	//
	SmartGCBufPool(Allocator * allocator)
		throw (toolbox::mem::exception::FailedCreation);
	
	//! Destructor
	//
	virtual ~SmartGCBufPool();

	/*! Return a buffer of a given \param size in Bytes or 0 if none is available.
		A buffer with of the length that matches closest the \param size parameter
		using a log2 calculation is returned if the system provides enough
		free memory (e.g. alloc(1000) returns a buffer of 1024 Bytes).
	*/
	Buffer * alloc(size_t size) 
		throw (toolbox::mem::exception::FailedAllocation);
	
	private:
	
	friend class UsageImpl;
};

}}

#endif

