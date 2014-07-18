// $Id: Bag.h,v 1.10 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Bag_h_
#define _xdata_Bag_h_

#include <map>

#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/AbstractBag.h"

namespace xdata {

template<class T>
class Bag:  
	public std::map< std::string, xdata::Serializable*, std::less<std::string> >, 
	public xdata::Serializable, 
	public xdata::AbstractBag
{
	public:
	
	Bag() throw (xdata::exception::Exception)
	{
		bag.registerFields(this);
	}
	
	virtual ~Bag()
	{
	}
	
	Bag(const Bag<T> & b) throw (xdata::exception::Exception)
	{
		bag.registerFields(this);
		*this = b;
	}
	
	Bag<T> & operator=(const Bag<T> & b) throw (xdata::exception::Exception)
	{ 
		// Bag<T>::const_iterator i = b.begin(); 
		std::map< std::string, xdata::Serializable*, std::less<std::string> >::const_iterator i = b.begin(); 
		while ( i != b.end() )
		{
			xdata::Serializable *s = this->getField((*i).first);
			if ( s != 0 ) 
			{
				s->setValue(*((*i).second));
			}
			else
			{
				std::string msg = "Missing field in assigned bag '";
				msg += (*i).first;
				msg += "'";
				XCEPT_RAISE(xdata::exception::Exception, msg);
			}
			i++;
		}
		return *this;
	}
	
	
	// Comparison operators
	
	int operator==(const Bag<T> & b)
	{
		// Bag<T>::const_iterator i = b.begin();
		std::map< std::string, xdata::Serializable*, std::less<std::string> >::const_iterator i = b.begin(); 

		while ( i != b.end() )
		{
			// name comparison
			xdata::Serializable * s = this->getField( (*i).first );
			if (s == 0)
			{
				return false; // not equal
			} 
			else 
			{
				// value comparison
				if (!s->equals(*((*i).second)))
				{
					return false;
				}
			}			
			i++;
		}
		return true;
	}

	int operator!=(const Bag<T> & b)
	{
		return !( *this == b );
	}	
	
	int equals(const xdata::Serializable & s)
	{
		// apply to this the function "==" with the parameter "const Bag<T>&"
		// inverting the two elements will cause C++ to call another "==" operator.
		//
		return this->operator==(dynamic_cast<const Bag<T>&>(s) );
	}
	

	void setValue(const xdata::Serializable & s) throw (xdata::exception::Exception)
	{
		this->operator=(dynamic_cast<const Bag<T> &>(s));
	}
	
	
	
	xdata::Serializable * getField(const std::string& name)
	{
		// Bag<T>::const_iterator i = this->find(name);
		std::map< std::string, xdata::Serializable*, std::less<std::string> >::const_iterator i = this->find(name);
		if ( i != this->end() )
		{
			return (*i).second;
		}
		return 0;
	}
	
	std::string type() const
	{
		return "bag";
	}
	
	
	void addField(const std::string& name, xdata::Serializable* s) throw (xdata::exception::Exception)
	{
		// Bag<T>::const_iterator i = this->find(name);
		std::map< std::string, xdata::Serializable*, std::less<std::string> >::const_iterator i = this->find(name);
		if ( i == this->end() )
		{
			(*this)[name] = s;
		}
		else
		{
			std::string msg = "Field name already existing '";
			msg += name;
			msg += "'";
			XCEPT_RAISE (xdata::exception::Exception, msg);
		}
	}
	
	std::string toString() throw (xdata::exception::Exception)
	{
		XCEPT_RAISE (xdata::exception::Exception, "toString of xdata::Bag not supported");
		return "";
	}
	
	void fromString(const std::string& value) throw (xdata::exception::Exception)
	{
		XCEPT_RAISE (xdata::exception::Exception, "fromString of xdata::Bag not supported");
	}
	
	public:
		
	T bag;
};

} // end namescape xdata

#endif



