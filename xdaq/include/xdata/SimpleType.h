// $Id: SimpleType.h,v 1.14 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_SimpleType_h_
#define _xdata_SimpleType_h_


#include <string>
#include <stdio.h>
#include <bitset>
#include <limits.h>

#include "xdata/exception/Exception.h"
#include "xdata/Serializable.h"

namespace xdata {

	enum Limits 
	{
		Infinity = 0,
		NaN = 1,
		NumberOfLimits = 2
	};

template<class T>
class SimpleType : public xdata::Serializable
{
	public:	
		
		SimpleType (T value );
		SimpleType ();
		// SimpleType (const std::string & value) throw (xdata::exception::Exception);
		                
		virtual ~SimpleType();
		
		bool isInf() const
		{
			return limits_.test(xdata::Infinity);
		}

		bool isNaN() const
		{
			return limits_.test(xdata::NaN);
		}

		bool isFinite() const
		{
			return ! (limits_.test(xdata::Infinity) || limits_.test(xdata::NaN) );
		}
		
		/*
		T* operator &() 
		{ 
			return &value_; 
		}
		*/
		
		
		//! Type cast operator returns the real value
		operator T ();
	
	
//		T & operator * ();
		
		//! Assignment operator
		SimpleType<T>& operator=(const T & value);
		
		void setValue(const xdata::Serializable & s);
	
		// Comparison operators for simple type
	
		int operator==(const SimpleType<T> & b);
				
		int operator!=(const SimpleType<T> & b);
		
		int operator<(const SimpleType<T> & b);
		
		int operator<=(const SimpleType<T> & b);
		
		int operator>(const SimpleType<T> & b);
		
		int operator>=(const SimpleType<T> & b);
		
	
		// Comparison operators for primitive value types
	
		int operator==(const T & b);
		
		int operator!=(const T & b);
		
		int operator!();
		
		int operator<(const T & b);
		
		int operator<=(const T & b);
		
		int operator>(const T & b);
		
		int operator>=(const T & b);
				
		// Mathematical operators for primitive value types
	
		//! Prefix ++
		//T& operator++();
		
		//! Prefix --
		//T& operator--();

		//! Postfix ++
		//T operator++(int);

		//! Postfix --
		//T operator--(int);
		
		// Comparison operators inherited from Serializable
		int equals(const xdata::Serializable & s);
		
		virtual std::string toString () throw (xdata::exception::Exception) = 0;

		virtual void  fromString (const std::string & value) throw (xdata::exception::Exception) = 0;
					
	
		T value_;
		std::bitset<NumberOfLimits> limits_;
};


} // end namespace xdata

#include "xdata/SimpleType.i"

#endif
