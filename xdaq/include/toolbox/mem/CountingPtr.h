// $Id: CountingPtr.h,v 1.2 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_CountingPtr_h_
#define _toolbox_mem_CountingPtr_h_

#include "toolbox/mem/SimpleReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"
#include "toolbox/BSem.h"

#include <assert.h>

namespace toolbox {
namespace mem {

extern toolbox::BSem * _s_mutex_ptr_;
 
template<typename T,
         typename CounterPolicy = SimpleReferenceCount,
         typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr : private CounterPolicy, private ObjectPolicy 
{
  private:

    // shortcuts:
    typedef CounterPolicy CP;
    typedef ObjectPolicy  OP;

    T* object_pointed_to;      // the object referred to (or NULL if none)

  public:
    // default constructor (no explicit initialization):
    CountingPtr() 
    {
        this->object_pointed_to = 0;
    }

    // a converting constructor (from a built-in pointer):
    explicit CountingPtr (T* p) 
    {
        this->init(p);         // init with ordinary pointer
    }

    // copy constructor:
    CountingPtr (CountingPtr<T,CP,OP> const& cp)
     : CP((CP const&)cp),      // copy policies
       OP((OP const&)cp) 
    {
	_s_mutex_ptr_->take();
        this->attach(cp);      // copy pointer and increment counter
	_s_mutex_ptr_->give();
    }

    // destructor:
    ~CountingPtr() 
    {
	_s_mutex_ptr_->take();
        this->detach();        // decrement counter
                               //  (and dispose counter if last owner)
	_s_mutex_ptr_->give();
    }

    // assignment of a built-in pointer
    CountingPtr<T,CP,OP>& operator= (T* p) 
    {
	_s_mutex_ptr_->take();
        // no counting pointer should point to *p yet:
	if ( p != this->object_pointed_to )
	{
        	//assert(p != this->object_pointed_to);
        	this->detach();        // decrement counter
                               	//  (and dispose counter if last owner)
        	this->init(p);         // init with ordinary pointer
	}
	_s_mutex_ptr_->give();
        return *this;
    }

    // copy assignment (beware of self-assignment):
    CountingPtr<T,CP,OP>&
    operator= (CountingPtr<T,CP,OP> const& cp) 
    {
	_s_mutex_ptr_->take();
        if (this->object_pointed_to != cp.object_pointed_to) 
	{
            this->detach();    // decrement counter
                               //  (and dispose counter if last owner)
            CP::operator=((CP const&)cp);  // assign policies
            OP::operator=((OP const&)cp);
            this->attach(cp);  // copy pointer and increment counter
        }
	_s_mutex_ptr_->give();
        return *this;
    }

    // the operators that make this a smart pointer:
    T* operator-> () const 
    {
        return this->object_pointed_to;
    }

    T& operator* () const 
    {
        return *this->object_pointed_to;
    }

    bool isNull() const
    {
	return (this->object_pointed_to == 0);
    }

    // additional interfaces will be added later
    //...

  private:
    // helpers:
    // - init with ordinary pointer (if any)
    void init (T* p) 
    {
        if (p != 0) 
	{
            CounterPolicy::init(p);
        }
        this->object_pointed_to = p;
    }

    // - copy pointer and increment counter (if any)
    void attach (CountingPtr<T,CP,OP> const& cp) 
    {
        this->object_pointed_to = cp.object_pointed_to;
        if (cp.object_pointed_to != 0) 
	{
            CounterPolicy::increment(cp.object_pointed_to);
        }
    }

    // - decrement counter (and dispose counter if last owner)
    void detach() 
    {
        if (this->object_pointed_to != 0) 
	{
            //CounterPolicy::decrement(this->object_pointed_to);
            //if (CounterPolicy::is_zero(this->object_pointed_to)) 
            if (CounterPolicy::decrement_and_is_zero(this->object_pointed_to)) 
	    {
                // dispose counter, if necessary:
                CounterPolicy::dispose(this->object_pointed_to);
                // use object policy to dispose the object pointed to:
                ObjectPolicy::dispose(this->object_pointed_to);
            }
        }
    }
};

}
}

#endif
