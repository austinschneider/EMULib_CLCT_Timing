// $Id: rlist.h,v 1.10 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_rlist_h__
#define _toolbox_rlist_h__

#include <string.h>
#include <string>
#include <sstream>

#include "toolbox/exception/RingListFull.h"
#include "toolbox/exception/RingListEmpty.h"
#include "toolbox/exception/RingListNotEmpty.h"
#include "toolbox/exception/Exception.h"
#include "toolbox/string.h"

namespace toolbox 
{

template <class Type>
class rlist {
	
	public:
        

	
	rlist() 
	{
		size_ = 1024+1;
		first_ = 0;
		last_ = 0;
		v_ = new Type [1024 +1];
		name_="undefined";
	}
	
	~rlist() 
	{
		delete [] v_;
	}
	
	void setName(std::string name ) 
	{
		name_ = name;	
	}
	
	//! gives the number of element contained in the rlist
	inline size_t elements() 
	{
		/*
		ssize_t first = first;
		ssize_t last = last_;
		ssize_t size = last-first;
		if (size < 0) size =  ( size_ - first ) + last;
		*/
		
		if ( first_ <= last_ )			
			return (last_ - first_);
		else
			return 	(( size_ - first_ ) + last_);
	}
	
	//! Reinitializes the rlist
	void clear()
	{
		while (!empty()) pop_front();
	}
	
	//! set the max number of element the rlist can contain
	inline void resize(size_t size) throw (toolbox::exception::RingListNotEmpty)
	{
		// Add a check. If the rlist if currently
		// not empty, throw an exception
		if (!empty())
		{
			XCEPT_RAISE(toolbox::exception::RingListNotEmpty, "rlist cannot be resized, contains elements.");
		}
	
		Type * v = new Type [size +1];
		
		if ( size >= size_ ) 
		{
			// copy all existing elements
			memcpy((char*)&v[0],(char*)&v_[0],size_ * sizeof(Type));
		}	
		else 
		{
			// copy only element up to the new size
			memcpy((char*)&v[0],(char*)&v_[0],(size +1)* sizeof(Type));
		}
		
		// new size
		size_ = size+1;
	
		delete [] v_; //delete old
		v_ = v;	
		return;
	}
	
	inline bool empty() 
	{
		if ( first_ == last_ ) 
		{
			return(true);
		}
		return(false);		
	}
	
	inline void pop_front() throw (toolbox::exception::RingListEmpty) 
	{
		if ( first_ != last_ ) {
			first_ = (first_ +1 ) % size_;
			return;
		}
		else
		{
			std::string msg = toolbox::toString("empty rlist %s", name_.c_str());
			XCEPT_RAISE(toolbox::exception::RingListEmpty, "no element available in rlist");
		}
	}
	
	inline Type front() 
	{
		return(v_[first_]);
	}
	
	inline void push_back(Type i) throw (toolbox::exception::RingListFull) 
	{
		if ((( last_ + 1) % size_ ) != first_ ) 
		{
			v_[last_] = i;
			last_ = (last_ + 1) % size_;
			return;
		}
		else
		{			
			std::string msg = "rlist overflow: ";
			msg += name_;
			//msg += ", duplicates: ";
			//msg += this->checkDuplicates();
			XCEPT_RAISE(toolbox::exception::RingListFull, msg);
		}
	
	}
	
/*	std::string checkDuplicates()
	{
		std::stringstream duplicates;
		
		for (int i = 0; i < size_; i++)
		{
			Type r = v_[i];
			for (int j = (i+1); j < size_; j++)
			{
				if (r == v_[j])
				{					
					duplicates << "<" << i << "," << j << ">=<" << std::hex << (int) r << std::dec << "; ";
				}
			}
		}
		
		return duplicates.str();
	}
*/	
	protected:
	
	rlist(const rlist<Type> & l) 
	{
		XCEPT_RAISE (toolbox::exception::Exception, "rlist Copy CTOR not implemented");
	}
	
	size_t size_;
	size_t first_;
	size_t last_;
	Type * v_;
	std::string  name_;
};

}

#endif
