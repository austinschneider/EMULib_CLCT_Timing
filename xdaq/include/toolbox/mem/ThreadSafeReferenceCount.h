// $Id: ThreadSafeReferenceCount.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_ThreadSafeReferenceCount_h_
#define _toolbox_mem_ThreadSafeReferenceCount_h_

namespace toolbox {
namespace mem {

class ThreadSafeReferenceCount 
{
  private:
    size_t* counter;    // the allocated counter
    
  public:
  
    ThreadSafeReferenceCount () 
    {
        counter = 0;
    }

    // default copy constructor and copy-assignment operator
    // are fine in that they just copy the shared counter

  public:
    // allocate the counter and initialize its value to one:
    template<typename T> void init (T*) 
    {
        counter = new size_t;
        *counter = 1;
    }

    // dispose of the counter:
    template<typename T> void dispose (T*) 
    {
        delete counter;
    }

    // increment by one:
    template<typename T> void increment (T*) 
    {
        ++*counter;
    }
    
    //! Decrement the counter and return true if it is 0. This function is atomic.
    //
    template<typename T> bool decrement_and_is_zero(T*)
    {
    	bool value = false;
	--*counter;
	if (*counter == 0) value = true;
	return value;
    }
};

}
}
#endif
