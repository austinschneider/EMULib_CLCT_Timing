// $Id: MemoryPartition.h,v 1.9 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_MemoryPartition_h
#define _toolbox_mem_MemoryPartition_h

#include <map>

#include "toolbox/mem/exception/Corruption.h"
#include "toolbox/mem/exception/InvalidAddress.h"
#include "toolbox/mem/exception/MemoryOverflow.h"
#include "toolbox/mem/exception/FailedAllocation.h"
#include "toolbox/mem/exception/FailedCreation.h"
#include "toolbox/mem/exception/FailedDispose.h"

typedef ssize_t BufferSizeType;
		

// Buffer allocation size quantum: all buffers allocated are a multiple of this size.  
// This MUST be a power of two. 		
#define SizeQuant   8		    
	      
// Define this symbol to enable the bpoolv() function for validating
// a buffer pool.		
#define BufValid    1		     
      	
// Define this symbol to enable the bstats() function which calculates the 
// total free space in the buffer pool, the largest available
// buffer, and the total space currently allocated. 
#define BufStats    1		     				

// Wipe free buffers to a guaranteed pattern of garbage to trip up 
//miscreants who attempt to use pointers into released buffers. 
//#define FreeWipe    1 

// Use a best fit algorithm when searching for space for an
// allocation request.  This uses memory more efficiently, but
// allocation will be much slower.			
#define BestFit     1		      

// Define this symbol to enable the bectl() function for automatic 
// pool space control.
// #define BECtl	    1


//! Header in allocated and free buffers
//
struct bhead {
	BufferSizeType prevfree;   // Relative link back to previous free buffer in memory or 0 if previous buffer is allocated.
	BufferSizeType bsize;		// Buffer size: positive if free, negative if allocated.
};
		
//! Header in directly allocated buffers (by acqfcn) 
//
struct bdhead {
	BufferSizeType tsize;		//Total size, including overhead 
	struct bhead bh;	// Common header
};
	
//!  Queue links
//
struct qlinks {
	struct bfhead *flink;	      // Forward link 
	struct bfhead *blink;	      // Backward link
};
	
//! Header in free buffers 
//
struct bfhead {
	struct bhead bh;	// Common allocated/free header
	struct qlinks ql;   	// Links on free list
};
	
						
namespace toolbox {
namespace mem {
						
class MemoryPartition 
{
	public:
	
		
	//! Create a buffer pool of <len> bytes, using the storage starting at
	//! <pool>.	You  can  call	addToPool()  subsequently  to   contribute
	//! additional storage to the overall buffer pool.
	//! Buffer allocation size quantum (alignement): all buffers allocated are a
	//! multiple of this size.  This MUST be a power of two (e.g. 2, 4, 8 etc.)
	
	MemoryPartition ();
	
	//! contribute additional storage to the overall buffer pool.
	//
	void addToPool (void * physAddr, void * kernelAddr, void * userAddr, BufferSizeType poolSize)
		throw (toolbox::mem::exception::Corruption, toolbox::mem::exception::InvalidAddress, toolbox::mem::exception::MemoryOverflow);
	
	void * alignedAlloc (BufferSizeType nBytes, BufferSizeType alignment);
	
	//! Gets \param nBytes from the partition
	//
	void * alloc (BufferSizeType nBytes)
		throw (toolbox::mem::exception::FailedAllocation);
	
	//! Gets zero-initialized memory of \param nBytes 
	//
	void * allocz(BufferSizeType nBytes)
		throw (toolbox::mem::exception::FailedAllocation);
	
	//! Return a previously allocated block to the partition
	//
	void free (char *pBlock) 
		throw (toolbox::mem::exception::InvalidAddress, toolbox::mem::exception::Corruption);
	
	void * realloc (char *pBlock, BufferSizeType nBytes)
		throw (toolbox::mem::exception::FailedAllocation, toolbox::mem::exception::Corruption);

	//! Dump a buffer pool.  The buffer headers are always listed.
	//! If DUMPALLOC is nonzero, the contents of allocated buffers
	//! are  dumped.   If  DUMPFREE  is  nonzero,  free blocks are
	//! dumped as well.  If FreeWipe  checking	is  enabled,  free
	//! blocks which  have  been clobbered will always be dumped. 
	void dumpPool(void * buf, int dumpalloc, int dumpfree) throw (toolbox::mem::exception::Corruption);

#ifdef BufStats	
	//! Return the number of bytes allocated (includes bookkeeping data)
	//
	BufferSizeType getUsed();

	//! Return buffer allocation free space statistics. Throws exception if pool is corrupted.
	//
	void stats( BufferSizeType *curalloc, BufferSizeType *totfree,BufferSizeType *maxfree, BufferSizeType *nget,BufferSizeType *nrel)
		throw (toolbox::mem::exception::Corruption);
#endif
	
	void * virtualToPhysical (void * userAddr) throw (toolbox::mem::exception::InvalidAddress);
	void * virtualToKernel (void * userAddr) throw (toolbox::mem::exception::InvalidAddress);
	void * physicalToVirtual (void * physAddr) throw (toolbox::mem::exception::InvalidAddress);
	
	protected:
		
	MemoryPartition (const MemoryPartition & aMemPart);
	MemoryPartition & operator = (const MemoryPartition & aMemPart);

	//! Dump the data in a buffer.  This is called with the  user
	//! data pointer, and backs up to the buffer header.  It will
	//! dump either a free block or an allocated one.
	void dumpBuffer(void *buf) throw (toolbox::mem::exception::Corruption);

#ifdef BufValid
	//! Validate a buffer pool.  If NDEBUG isn't defined,
	//! any error generates an assertion failure. 
	int validate(void * buf) throw (toolbox::mem::exception::Corruption);
#endif

#ifdef BECtl	
	//!  Establish automatic pool expansion control
	void autoExpansion( int (*compact) (BufferSizeType sizereq, int sequence),  void *(*acquire) (BufferSizeType size),
		   void (*release) (void *buf), BufferSizeType pool_incr);
#endif

#ifdef BufStats
#ifdef BECtl	
	//  Return extended statistics	   
	void estats( BufferSizeType *pool_incr, BufferSizeType *npool,BufferSizeType *npget, BufferSizeType*nprel, BufferSizeType*ndget,BufferSizeType *ndrel);	   
#endif
#endif	
	private:
	

	// start block list
	struct bfhead freelist_;
	
	
#ifdef BufStats

	BufferSizeType totalloc_ ;		// Total space currently allocated 
	BufferSizeType numget_, numrel_ ;		// Number of bget() and brel() calls
	
#ifdef BECtl

	BufferSizeType numpblk_;		 // Number of pool blocks 
	BufferSizeType numpget_, numprel_; // Number of block gets and rels 
	BufferSizeType numdget_, numdrel_; // Number of direct gets and rels
	
#endif // BECtl 
#endif // BufStats 
	
#ifdef BECtl
	
	// Automatic expansion block management functions 	
	int (*compfcn_) (BufferSizeType sizereq, int sequence) = NULL;
	void *(*acqfcn_) (BufferSizeType size) = NULL;
	void (*relfcn_) (void *buf) = NULL;
	
	 // Expansion block size 
	BufferSizeType exp_incr ;	     

	
	// 0: no bpool calls have been made
	//	-1: not all pool blocks are
	//	the same size
	//	>0: (common) block size for all
	//	bpool calls made so far
	BufferSizeType pool_len;	      

#endif
	struct MemoryChunk{
		BufferSizeType size;
		void * userAddress;
		void * kernelAddress;
	};
	// physical, virtual address mapping
	std::map<void *, struct MemoryChunk, std::less<void*> > memoryPoolMap_;
	
};

}}


#endif 
