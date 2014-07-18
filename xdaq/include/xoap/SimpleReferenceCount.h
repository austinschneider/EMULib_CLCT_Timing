// $Id: SimpleReferenceCount.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_SimpleReferenceCount_h_
#define _xoap_SimpleReferenceCount_h_

namespace xoap
{

class SimpleReferenceCount 
{
  private:
    unsigned int* counter;    // the allocated counter
  public:
  
    SimpleReferenceCount () 
    {
        counter = 0;
    }

    // default copy constructor and copy-assignment operator
    // are fine in that they just copy the shared counter

  public:
    // allocate the counter and initialize its value to one:
    template<typename T> void init (T*) 
    {
        counter = new unsigned int;
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
    
    // decrement by one:
    /*
    template<typename T> void decrement (T*) 
    {
        --*counter;
    }
    
    // test for zero:
    template<typename T> bool is_zero (T*) 
    {
        return *counter == 0;
    }
    */
    
    //! Decrement the counter and return true if it is 0. This function is not atomic.
    //
    template<typename T> bool decrement_and_is_zero (T*) 
    {
	--*counter;
        if (*counter == 0) return true;
	return false;
    }
};

}
#endif
