// $Id: Integer64.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Integer64_h_
#define _xdata_Integer64_h_

#include <stdint.h>
#include <string>
#include <errno.h>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class Integer64Type: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		Integer64Type(T value);
		
		//! Uninitialized representing NaN
		//
		Integer64Type();
		
		//! CTOR from string containing value
		//
		Integer64Type (const std::string & value) 
			throw (xdata::exception::Exception);

		virtual ~Integer64Type();
		
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

typedef  Integer64Type<int64_t> Integer64;
typedef  Integer64Type<int64_t &> Integer64Ref;
typedef  int64_t Integer64T;
 
} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::Integer64>
{
	static const bool is_specialized = true;

	static xdata::Integer64 min() throw()
	{ 
		return xdata::Integer64(std::numeric_limits<xdata::Integer64T>::min());
	}

	static xdata::Integer64 max() throw()
	{ 
		return xdata::Integer64(std::numeric_limits<xdata::Integer64T>::max());

	}

	static const int digits = std::numeric_limits<xdata::Integer64T>::digits;
	static const int digits10 = std::numeric_limits<xdata::Integer64T>::digits10;
	static const bool is_signed = true;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	
	static xdata::Integer64 epsilon() throw()
	{ 
		return xdata::Integer64(0); 
	}
	
	static xdata::Integer64 round_error() throw()
	{ 
		return xdata::Integer64(0);
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

	static xdata::Integer64 infinity() throw()
	{ 
		xdata::Integer64 i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::Integer64 quiet_NaN() throw()
	{ 
		return xdata::Integer64(); 
	}

	static xdata::Integer64 signaling_NaN() throw()
	{ 
		return xdata::Integer64(0); 
	}

	static xdata::Integer64 denorm_min() throw()
	{ 
		return xdata::Integer64(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::Integer64T>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/Integer64.i"


#endif
