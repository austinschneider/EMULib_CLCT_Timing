// $Id: UnsignedInteger32.h,v 1.6 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_UnsignedInteger32_h_
#define _xdata_UnsignedInteger32_h_

#include <string>
#include <errno.h>
#include <stdint.h>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class UnsignedInteger32Type: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		UnsignedInteger32Type(T value);
		
		//! Uninitialized representing NaN
		//
		UnsignedInteger32Type();
		
		//! CTOR from string containing value
		//
		UnsignedInteger32Type (const std::string & value) 
			throw (xdata::exception::Exception);

		virtual ~UnsignedInteger32Type();
		
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

		void  fromString (const std::string & value) 
			throw (xdata::exception::Exception);
			
};

typedef  UnsignedInteger32Type<uint32_t> UnsignedInteger32;
typedef  UnsignedInteger32Type<uint32_t &> UnsignedInteger32Ref;
typedef  uint32_t UnsignedInteger32T;

} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::UnsignedInteger32>
{
	static const bool is_specialized = true;

	static xdata::UnsignedInteger32 min() throw()
	{ 
		return xdata::UnsignedInteger32(std::numeric_limits<xdata::UnsignedInteger32T>::min());
	}

	static xdata::UnsignedInteger32 max() throw()
	{ 
		return xdata::UnsignedInteger32(std::numeric_limits<xdata::UnsignedInteger32T>::max());

	}

	static const int digits = std::numeric_limits<xdata::UnsignedInteger32T>::digits;
	static const int digits10 = std::numeric_limits<xdata::UnsignedInteger32T>::digits10;
	static const bool is_signed = false;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	static xdata::UnsignedInteger32 epsilon() throw()
	{ 
		return xdata::UnsignedInteger32(0); 
	}
	static xdata::UnsignedInteger32 round_error() throw()
	{ 
		return xdata::UnsignedInteger32(0);
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

	static xdata::UnsignedInteger32 infinity() throw()
	{ 
		xdata::UnsignedInteger32 i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::UnsignedInteger32 quiet_NaN() throw()
	{ 
		return xdata::UnsignedInteger32(); 
	}

	static xdata::UnsignedInteger32 signaling_NaN() throw()
	{ 
		return xdata::UnsignedInteger32(0); 
	}

	static xdata::UnsignedInteger32 denorm_min() throw()
	{ 
		return xdata::UnsignedInteger32(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::UnsignedInteger32T>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/UnsignedInteger32.i"


#endif
