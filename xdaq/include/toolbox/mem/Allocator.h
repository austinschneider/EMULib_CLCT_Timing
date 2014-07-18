// $Id: Allocator.h,v 1.8 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Allocator_h_
#define _toolbox_mem_Allocator_h_

#include <iostream>
#include <string>

#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"

namespace toolbox 
{
namespace mem
{

class Pool;
class Buffer;

//! Interface for all memory allocator classes
class Allocator 
{
	public:
	
	//! Empty virtual destructor. Provided to allow proper direct destruction of sub-classes
	//
	virtual ~Allocator() {}
	
	//! Allocate a block of memory according to a given size in bytes
	//
	virtual Buffer * alloc(size_t size, toolbox::mem::Pool * pool) 
		throw (toolbox::mem::exception::FailedAllocation) = 0;	
	
	//! Release a buffer, implementation dependend for different buffers
	//
	virtual void free(Buffer * buffer ) 
 		throw (toolbox::mem::exception::FailedDispose) = 0;
	
	//! Return a string that identifies the type of allocator
	//
	virtual std::string type() = 0;
	
	//! Return true, if the allocator supports committed memory areas (space limited areas)
	//
	virtual bool isCommittedSizeSupported() = 0;
	
	//! Return the committed memory size for this allocator in bytes, if supported. 0 Otherwise
	//
	virtual size_t getCommittedSize() = 0;	
	
	//! Retrieve the number of byte currently used
	//
	virtual size_t getUsed() = 0;	
};

}}

#endif
