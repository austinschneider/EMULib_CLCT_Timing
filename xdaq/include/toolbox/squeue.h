// $Id: squeue.h,v 1.10 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_squeue_h_
#define _toolbox_squeue_h_

#include "toolbox/rlist.h"
#include "toolbox/exception/QueueFull.h"
#include "toolbox/exception/OverThreshold.h"
#include "toolbox/BSem.h"

namespace toolbox 
{

	template <class T>
	class squeue 
	{
		public:

		enum 
		{
			DefaultNumberOfEntries = 1024
		} SQueueLimits;

		squeue(size_t size, double threshold  ): sync_(BSem::EMPTY), mutex_(BSem::FULL)
		{
			size_ = size;
			queue_.resize(size);
			queue_.setName((char*)"squeue");	
			pending_ = 0;
			threshold_ = (size_t)(size * threshold); // e.g 0.1 means 10%
			deadBand_ = false;
		}
		
		squeue(): sync_(BSem::EMPTY), mutex_(BSem::FULL)
		{
			size_ = DefaultNumberOfEntries;
			queue_.resize(DefaultNumberOfEntries);
			queue_.setName((char*)"squeue");	
			pending_ = 0;
			threshold_ = DefaultNumberOfEntries; //always disabled deadband
			deadBand_ = false;

		}
		
		squeue(size_t size): sync_(BSem::EMPTY), mutex_(BSem::FULL)
		{
			size_ = size;
			queue_.resize(size);
			queue_.setName((char*)"squeue");	
			pending_ = 0;
			threshold_ = size; // always disabled deadband
			deadBand_ = false;

		}
		
		/*! Return the current number of elements in the queue.
		    Do not use for instant calculations, only for statistical usage over
		    a sufficient amount of time and debugging.
		*/
		inline size_t elements() 
		{
			return queue_.elements();
		}

		inline void push(T & element) 
			throw (toolbox::exception::QueueFull, toolbox::exception::OverThreshold)
		{
			mutex_.take();

			if ( queue_.elements() < threshold_ ) 
			{
				if ( deadBand_ ) 
				{ // I am crossing the threshold and I was in the dead zone, now I can push data again
					
					deadBand_ = false;
				}	
			}
			else 
			{
				if ( deadBand_ )  // I am in dead zone so I discard the data
				{
					
					mutex_.give();
					XCEPT_RAISE (toolbox::exception::OverThreshold, "element discarded (in dead band)");			
					
				}	
				
			}	

			try 
			{
				queue_.push_back(element);
			}
			catch (toolbox::exception::RingListFull & rlf)
			{
				if ( threshold_ == size_ )
				{
					deadBand_ = false;
				}
				else
				{
					deadBand_ = true;
				}
				mutex_.give();
				XCEPT_RETHROW(toolbox::exception::QueueFull,"overflow, squeue is full",rlf);
			}

			if ( pending_ > 0) 
			{
				pending_--;
				sync_.give();
				mutex_.give();
				return;
			}	

			mutex_.give();

		}

		inline bool empty()
		{
			return queue_.empty();
		}

		//! pop an element from the queue, if queue is empty waits until an element is pushed
		inline T pop()
		{
			for (;;) 
			{
				mutex_.take();
				if ( ! queue_.empty() ) 
				{
					T element = queue_.front();
					queue_.pop_front();
					mutex_.give();
					return element;
				}
				else 
				{ // go to wait
					pending_++;
					mutex_.give();
					sync_.take(); // wait Not empty condition
				}
			}
		}
		
		inline void resize(size_t size) throw (toolbox::exception::RingListNotEmpty)
		{
			size_ = size;
			mutex_.take();
			queue_.resize(size);
			mutex_.give();
		}

		private:

		BSem  sync_;
		BSem  mutex_;
		toolbox::rlist<T> queue_;
		size_t pending_;
		// dead band algorithm
		size_t threshold_;
		size_t size_;
		bool deadBand_;
	};
}
#endif
