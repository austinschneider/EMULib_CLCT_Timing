// $Id: SmartAllocator.h,v 1.5 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_SmartAllocator_h_
#define _toolbox_mem_SmartAllocator_h_

#include <iostream>
#include "toolbox/rlist.h"
#include "toolbox/mem/exception/MemoryOverflow.h"

namespace toolbox {
namespace mem
{

template <class Type>	
class SmartAllocator
{
	public:
	 
	SmartAllocator(size_t  numEntries) {
		//cout << "SmartAllocator() " << endl;
		free_.resize(numEntries+1);
		remember_.resize(numEntries+1);
		created_ = 0;
		numEntries_ = numEntries;

	}
	
	~SmartAllocator() {
	 	
		while ( ! remember_.empty() ) {
			Type * tmp = remember_.front();
			remember_.pop_front();
			delete tmp;	
		}
		
	}
	
	inline Type * alloc()
	{
		if ( ! free_.empty()) {
			Type * tmp = free_.front();
			free_.pop_front();
			return tmp;
			
		}
		else {
			if ( created_ == numEntries_) {
				//cout << "*** Fatal Error: Smart Allocator out of memory" << created_ << " " << numEntries_ << endl;
				return (Type*)0;
			
			}
			
			

			Type * tmp = new Type;
			
			//cout << "allocate new Type of size:" << blockSize_ <<  " created_" << created_ << "prt:" << hex << (int)tmp << dec << endl;
			remember_.push_back(tmp);
			created_++;
			
			return tmp;
		
		}
	}
	
	inline void free( Type * block ) throw (toolbox::mem::exception::MemoryOverflow)
	{
		try
		{
			free_.push_back(block);
		} 
		catch (toolbox::exception::RingListFull& e)
		{
			XCEPT_RAISE (toolbox::mem::exception::MemoryOverflow, e.what());
		}
	
	}
	
	
	protected:
	
	
	toolbox::rlist<Type*> free_;
	toolbox::rlist<Type*> remember_;
	size_t created_;
	size_t numEntries_;
};

}}

#endif
