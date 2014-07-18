// $Id: ThreadSafeReferenceCount.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_ThreadSafeReferenceCount_h_
#define _xoap_ThreadSafeReferenceCount_h_

#include "xercesc/util/Mutexes.hpp"

XERCES_CPP_NAMESPACE_USE

namespace xoap
{

class ThreadSafeReferenceCount 
{
  private:
    unsigned int* counter;    // the allocated counter
    XMLMutex* mutex; // a mutex to make increment and decrement thread safe
    
  public:
  
    ThreadSafeReferenceCount () 
    {
        counter = 0;
	mutex = 0;
    }

    // default copy constructor and copy-assignment operator
    // are fine in that they just copy the shared counter

  public:
    // allocate the counter and initialize its value to one:
    template<typename T> void init (T*) 
    {
        counter = new unsigned int;
        *counter = 1;
	mutex = new XMLMutex();
    }

    // dispose of the counter:
    template<typename T> void dispose (T*) 
    {
        delete counter;
	delete mutex;
    }

    // increment by one:
    template<typename T> void increment (T*) 
    {
    	mutex->lock();
        ++*counter;
	mutex->unlock();
    }
    
    // decrement by one:
    /*
    template<typename T> void decrement (T*) 
    {
    	mutex->lock();
        --*counter;
	mutex->unlock();
    }

    // test for zero: not thread safe
    template<typename T> bool is_zero (T*) 
    {
        return *counter == 0;
    }
    */
    //! Decrement the counter and return true if it is 0. This function is atomic.
    //
    template<typename T> bool decrement_and_is_zero(T*)
    {
    	bool value = false;
    	mutex->lock();
	--*counter;
	if (*counter == 0) value = true;
	mutex->unlock();
	return value;
    }
};

}
#endif
