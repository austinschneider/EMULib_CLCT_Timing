// $Id: SyncQueue.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_SyncQueue_h
#define _toolbox_SyncQueue_h


#include <limits.h>
#include <list>
#include <string>
#include <iostream>
#include "BSem.h"
#include "Condition.h"
#include "toolbox/exception/QueueFull.h"
#include "toolbox/exception/Timeout.h"

//! A thread safe, synchronized queue
/*! This class provides a queue abstraction to be
    used for producer/consumer problems amongst two
    or more threads. Note that, if multiple threads act
    as receivers, an element in the queue is consumed by
    at most one thread.
    There exists currently no blocking write, that means,
    if an upper limit for the queue size has been set and
    the queue is full, an exception will be raised.
   */
   
namespace toolbox {   
   
template <class T>
class SyncQueue
{
	public:
	
		//! Creates an unbounded synchronized queue
		SyncQueue () : sema_(BSem::FULL)
		{
			maxElements_ = UINT_MAX;
		}
		
		//! Creates a synchronized queue with maxElements
		SyncQueue (unsigned int maxElements) : sema_(BSem::FULL)
		{
			maxElements_ = maxElements;
		}
		
		//! Limits the number of maximum elements in the queue
		void setMaxElements (unsigned int maxElements)
		{
			maxElements_ = maxElements;
		}
		
		//! push an element into the queue. Throw is queue is full
		void push (const T element) throw (toolbox::exception::QueueFull)
		{
			sema_.take();
			unsigned int size = queue_.size();
			if ( size < maxElements_ )
			{
				queue_.push_back (element);
				// If the queue was empty before
				// signal a potential waiting thread
				// that data have arrived.
				if (size == 0) cond_.signal();
				sema_.give();
			} 
			else 
			{
				sema_.give();
				XCEPT_RAISE( toolbox::exception::QueueFull,"synchronized queue full");
			}
		}
		
		//! pop an element from the queue. Block if queue is empty.
		T pop ()
		{
			for (;;)
			{
				sema_.take();
				if (queue_.size() > 0)
				{
					T value = queue_.front();
					queue_.pop_front();
					sema_.give();
					return value;
				} 
				else 
				{
					sema_.give();
				}	cond_.wait();
			}
		}
		
		//! pop an element from the queue. Block until timeout.
                T pop (time_t sec, suseconds_t usec) throw (toolbox::exception::Timeout)
                {
                        for (;;)
                        {                          
                                sema_.take();
                               
                                if (queue_.size() > 0)
                                {
                                        T value = queue_.front();
                                        queue_.pop_front();
                                        sema_.give();
                                        return value;
                                } 
				else 
				{
                                        sema_.give();
					// w.b. : going to wait with timeout :
					try 
					{
						cond_.timedwait(sec,usec);
					} 
					catch (toolbox::exception::Timeout& e) 
					{
						XCEPT_RETHROW(toolbox::exception::Timeout, "synchronized queue timeout", e);
					}
                                }                                
                        }
                }
		
		unsigned int size ()
		{
			unsigned int retVal = 0;
			sema_.take();
			retVal = queue_.size();
			sema_.give();
			return retVal;
		}
		
	protected:
	
	std::list<T> queue_;
	BSem 	sema_;
	Condition cond_;
	unsigned int maxElements_;
};

}


#endif
