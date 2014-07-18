// $Id: Reference.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Reference_h_
#define _toolbox_mem_Reference_h_

#include "toolbox/mem/Buffer.h"
#include "toolbox/mem/ReferencePool.h"

namespace toolbox 
{

namespace mem
{

class Reference 
{
	public:
	
	// Empty CTOR
	Reference();

	void setReferencePool(toolbox::mem::ReferencePool * refPool);

	//! Retrieve the pool associated with this reference
	//
	toolbox::mem::Buffer* getBuffer();    

	//! Retrieve a pointer to the user data block (start of buffer plus offset)
	//
	void* getDataLocation();

	void setDataOffset ( size_t offset );

	void setDataSize ( size_t offset );
		
	//! Retrieve the offset to the beginning of the data
	//
	size_t getDataOffset();
		
	//! Returns the amount of data in the buffer (may be smaller than the block size of the buffer)
	//
	size_t getDataSize();

	//! Chain the \param ref buffer reference to this reference
	//
	void setNextReference ( Reference * ref );

	/*! 	If this reference is chained to another one, return a pointer
		to the next reference. Return 0 otherwise.
	*/
	Reference* getNextReference();


	/*! Associate this buffer reference with a buffer, and a free function.
	    Context parameters will be documented shortly.
	*/
	void setBuffer ( toolbox::mem::Buffer * buffer);

	toolbox::mem::Reference * duplicate();
	
	//! Give the reference and the contained buffer back to the pool to which they belong
	//
	void release();
	
	private:
	
		toolbox::mem::Buffer	* buffer_;
		toolbox::mem::Reference	* nextReference_;
		size_t		offset_;
		size_t		dataSize_;
		toolbox::mem::ReferencePool * refPool_;
};

}}

#endif
