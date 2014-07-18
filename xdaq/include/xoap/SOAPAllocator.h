// $Id: SOAPAllocator.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPAllocator_h
#define xoap_SOAPAllocator_h

#include <stdlib.h>
#include <stddef.h>
#include <iostream>

namespace xoap
{
/*! Tests the XOAP library for memory leakage. In addition to the member
function \e testMemoryLeakage, it contains the member functions \e allocate
and \e dispose. These two member functions replace the \e new and \e delete
member functions in the XOAP library if the \e _DEBUG flag is set. In addition
to allocate and deallocate memory, a counter keeps track of the number of times
memory is allocated and deallocated, respectively.
 */
class SOAPAllocator 
{
public:
	/*! Allocate dynamic memory.
	    In addition, it increases
	    a counter by one. This member function is intended
            to be used when testing for memory leaks.
	 */
	static void * allocate(size_t);
	/*! Deallocate dynamic memory.
            In addition, it decreases
            a counter by one. This member function is intended
            to be used when testing for memory leaks.
	 */
	static void dispose(void*);
	/*! A member function which writes a message to the screen regarding whether a
            memory leakage test has passed or not (the test is passed if there is an equal
            number of allocations and deallocations).
	 */
	static void testMemoryLeakage();
};

}
#endif
