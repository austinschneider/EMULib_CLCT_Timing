// $Id: Integer.h,v 1.11 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Integer_h_
#define _xdata_Integer_h_

#include <string>
#include <errno.h>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class IntegerType: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		IntegerType(T value);
		
		//! Uninitialized representing NaN
		//
		IntegerType();
		
		//! CTOR from string containing value
		//
		IntegerType (const std::string & value) throw (xdata::exception::Exception);

		virtual ~IntegerType();
		
		//! Prefix ++
		T& operator++();
		
		//! Prefix --
		T& operator--();

		//! Postfix ++
		T operator++(int);

		//! Postfix --
		T operator--(int);
		
		std::string type() const;

		std::string toString () throw (xdata::exception::Exception);

		void  fromString (const std::string & value) throw (xdata::exception::Exception);
			
};


typedef  IntegerType<int> Integer;
typedef  IntegerType<int&> IntegerRef;
typedef  int IntegerT;

} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::Integer>
{
	static const bool is_specialized = true;

	static xdata::Integer min() throw()
	{ 
		return xdata::Integer(std::numeric_limits<xdata::IntegerT>::min());
	}

	static xdata::Integer max() throw()
	{ 
		return xdata::Integer(std::numeric_limits<xdata::IntegerT>::max());

	}

	static const int digits = std::numeric_limits<xdata::IntegerT>::digits;
	static const int digits10 = std::numeric_limits<xdata::IntegerT>::digits10;
	static const bool is_signed = true;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	static xdata::Integer epsilon() throw()
	{ 
		return xdata::Integer(0); 
	}
	static xdata::Integer round_error() throw()
	{ 
		return xdata::Integer(0);
	}

	static const int min_exponent = 0;
	static const int min_exponent10 = 0;
	static const int max_exponent = 0;
	static const int max_exponent10 = 0;

	static const bool has_infinity = true;
	static const bool has_quiet_NaN = true;
	static const bool has_signaling_NaN = false;
	static const float_denorm_style has_denorm = denorm_absent;
	static const bool has_denorm_loss = false;

	static xdata::Integer infinity() throw()
	{ 
		xdata::Integer i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::Integer quiet_NaN() throw()
	{ 
		return xdata::Integer(); 
	}

	static xdata::Integer signaling_NaN() throw()
	{ 
		return xdata::Integer(0); 
	}

	static xdata::Integer denorm_min() throw()
	{ 
		return xdata::Integer(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::IntegerT>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/Integer.i"

#endif
