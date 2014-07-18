// $Id: Vector.h,v 1.15 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Vector_h_
#define _xdata_Vector_h_

#include <vector>

#include "xdata/AbstractVector.h"
#include "xdata/Serializable.h" 


namespace xdata {

template <class T>
class Vector : public xdata::AbstractVector, public virtual std::vector<T>, public xdata::Serializable
{
	public:
	
	size_t elements();
	xdata::Serializable * elementAt(size_t i);
	void setSize(size_t s);
	
	Serializable & operator=(const Serializable & s);
	
	std::string type() const;
	
	virtual ~Vector();
	Vector();
	
	int operator==(const Vector<T> & b)
	{
		for (size_t i = 0; i < this->size(); i++ )
		{
			if (  !( (this->elementAt(i))->equals(b[i]) ) )
				return false;
		
		}
		return true;
	}
	
	int operator!=(const Vector<T> & b)
	{
		return !( *this == b );
	}
	
	int equals(const xdata::Serializable & s)
	{
		// return (*this == dynamic_cast<const Vector<T>&>(s) );
		//
		// apply to this the function "==" with the parameter "const Bag<T>&"
		// inverting the two elements will cause C++ to call another "==" operator.
		//
		return this->operator==(dynamic_cast<const Vector<T>&>(s) );
	}
	
	void setValue(const xdata::Serializable & s) throw (xdata::exception::Exception)
	{
		this->operator=(dynamic_cast<const Vector<T> &>(s));
	}
	
	
	
	std::string toString () throw (xdata::exception::Exception);

	void fromString(const std::string& value) throw (xdata::exception::Exception);
	
	void clear()
	{
		std::vector<T>::clear();
	}
	
	void erase(size_t i)
	{
		typename std::vector<T>::iterator vi = std::vector<T>::begin() + i;
		std::vector<T>::erase(vi);
	}
	
	std::string getElementType()
	{
		return prototype_.type();
	}
	
	private:
	
	T prototype_;
};


} // end namespace xdata

#include "xdata/Vector.i"


#endif



