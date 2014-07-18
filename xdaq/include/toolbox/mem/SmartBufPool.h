// $Id: SmartBufPool.h,v 1.15 2008/09/19 08:38:27 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_SmartBufPool_h_
#define _toolbox_mem_SmartBufPool_h_

#include <iostream>
#include "toolbox/ActionListener.h"
#include "toolbox/EventDispatcher.h"

#include "toolbox/mem/Pool.h"
#include "toolbox/mem/Allocator.h"
#include "toolbox/mem/UsageImpl.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedDispose.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/BSem.h"


extern size_t log2_roundup (size_t n);

/* buffer defines */

#define BUF_LOG2_64			6	
#define BUFL_LOG2_128			7
#define BUF_LOG2_256			8
#define BUF_LOG2_512			9
#define BUF_LOG2_1024			10
#define BUF_LOG2_2048			11
#define BUF_LOG2_4096	 		12
#define BUF_LOG2_8192 			13
#define BUF_LOG2_16384			14
#define BUF_LOG2_32768			15
#define BUF_LOG2_65536			16
#define BUF_LOG2_131072			17
#define BUF_LOG2_262144			18
#define BUF_LOG2_524288			19
#define BUF_LOG2_1048576		20
#define BUF_LOG2_2097152		21
#define BUF_LOG2_4194304		22
#define BUF_LOG2_8388608		23
#define BUF_LOG2_16777216		24
#define BUF_LOG2_33554432               25

#define BUF_SIZE_64			64
#define BUF_SIZE_128			128
#define BUF_SIZE_256			256
#define BUF_SIZE_512			512
#define BUF_SIZE_1024			1024
#define BUF_SIZE_2048			2048
#define BUF_SIZE_4096			4096
#define BUF_SIZE_8192			8192
#define BUF_SIZE_16384			16384
#define BUF_SIZE_32768			32768
#define BUF_SIZE_65536			65536
#define BUF_SIZE_131072			131072
#define BUF_SIZE_262144			262144
#define BUF_SIZE_524288			524288
#define BUF_SIZE_1048576		1048576
#define BUF_SIZE_2097152		2097152
#define BUF_SIZE_4194304		4194304
#define BUF_SIZE_8388608		8388608
#define BUF_SIZE_16777216		16777216
#define BUF_SIZE_33554432               33554432 

#define BUF_LOG2_MIN			BUF_LOG2_64
//#define BUF_LOG2_MAX			BUF_LOG2_4194304
//#define BUF_LOG2_MAX			BUF_LOG2_8388608
#define BUF_LOG2_MAX			BUF_LOG2_33554432
#define BUF_SIZE_MAX			(1 << BUF_LOG2_MAX)
#define BUF_SIZE_MIN			(1 << BUF_LOG2_MIN)
//#define BUF_INDX_MIN			0
//#define BUF_INDX_MAX			(BUF_LOG2_MAX - BUF_LOG2_MIN)

// The table indexes directly all pool entries by log2 number, From 0 to the maximum number allowed BUF_LOG2_MAX
#define BUF_TBL_SIZE			((BUF_LOG2_MAX + 1) - (BUF_LOG2_MIN))

#define BUF_INDEX_TO_LOG2(x)			(BUF_LOG2_MIN + (x))
#define BUF_LOG2_TO_BUF_INDEX(x)		((x) - BUF_LOG2_MIN)
#define BUF_LOG2_TO_BUF_SIZE(x)			(1 << (x))
#define LMAX(x,y) (x>y?x:y)
#define BUF_SIZE_TO_LOG2(size)			(log2_roundup(LMAX(size,BUF_SIZE_MIN)))
#define BUF_SIZE_TO_BUF_INDEX(bufSize) 		(log2_roundup(LMAX(bufSize,BUF_SIZE_MIN)) - (BUF_LOG2_MIN))

//
// Maximum number of buffers that a BufPoolEntry can hold
//
#define MAX_ENTRIES_SIZE               65536

typedef struct 
{
	size_t low;
	size_t high;
} UNSIGNED64;


namespace toolbox 
{

namespace mem
{


class BufPoolEntry;

//! Encapsulation of a pool of buffers that can grow dynamically.
//
class SmartBufPool: public toolbox::mem::Pool
{
	public:
	
	//! Create a smart buffer pool and pass an \param allocator that is used to allocate the memory blocks
	//
	SmartBufPool(Allocator * allocator)
		throw (toolbox::mem::exception::FailedCreation);
	
	//! Destructor
	//
	virtual ~SmartBufPool();

	/*! Return a buffer of a given \param size in Bytes or 0 if none is available.
		A buffer with of the length that matches closest the \param size parameter
		using a log2 calculation is returned if the system provides enough
		free memory (e.g. alloc(1000) returns a buffer of 1024 Bytes).
	*/
	Buffer * alloc(size_t size) 
		throw (toolbox::mem::exception::FailedAllocation);
	
	//! Return a \param buffer to the pool
	//
	void free ( Buffer* buffer )
		throw (toolbox::mem::exception::FailedDispose);
	
	//! Perform thread safe locking to the pool
	//
 	void lock();
	
	//! Unlock the previously locked pool
	//
	void unlock();
	
	
	void show();
	
	//! Returns the usage threshold value of this memory pool in bytes
	size_t getHighThreshold ();
	size_t getLowThreshold ();
	
	//! Set the threshold of this memory pool to the given nbytes memory
	void setHighThreshold ( size_t nbytes) throw (toolbox::mem::exception::InvalidThreshold);
	void setLowThreshold ( size_t nbytes) throw (toolbox::mem::exception::InvalidThreshold);
	
	//! Gets the current used memory in bytes
	//size_t getUsed();
	
	//! Gets the current memory usage record
	toolbox::mem::Usage & getMemoryUsage();
	
	
	//! Test if the memory usage of this memory pool reaches or exceeds its usage threshold value
	bool isLowThresholdExceeded ();
	bool isHighThresholdExceeded ();
	
	//! additional methods for memory handling
	toolbox::mem::Allocator * getAllocator();
	
	//! Recycle all cached memory blocks into the commited memory area 
	void invalidate()
		throw (toolbox::mem::exception::FailedDispose);
	
	//! Recycle all cached memory of the block size closest to the given size into the commited memory area 
	void invalidate(size_t size)
		throw (toolbox::mem::exception::FailedDispose);
		
	//! Add a listener to the pool for threshold events
	//
	void addActionListener (toolbox::ActionListener* listener);

	//! Remove a pool listener
	//
	void removeActionListener (toolbox::ActionListener* listener) throw (toolbox::exception::Exception);
	
	protected:
	toolbox::BSem * mutex_;

	private:
	
	BufPoolEntry * bufPoolTable_[BUF_TBL_SIZE];
	toolbox::mem::Allocator * allocator_;
	size_t used_;
	size_t lowThreshold_;
	size_t highThreshold_;
	toolbox::mem::UsageImpl usage_;
	
	int location_; // indicates in which threshold section pool is: 1 = higher, 0 = normal, -1 = lower
	toolbox::EventDispatcher dispatcher_;
	
	friend class UsageImpl;
};

}}

#endif
