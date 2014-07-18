// $Id: UnsignedLong.h,v 1.12 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_UnsignedLong_h_
#define _xdata_UnsignedLong_h_

#include <string>
#include <errno.h>
#include <stdint.h>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class UnsignedLongType: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		UnsignedLongType(T value);
		
		//! Uninitialized representing NaN
		//
		UnsignedLongType();
		
		//! CTOR from string containing value
		//
		UnsignedLongType (const std::string & value)
			throw (xdata::exception::Exception);

		virtual ~UnsignedLongType();
		
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

typedef  UnsignedLongType<uint64_t> UnsignedLong;
typedef  UnsignedLongType<uint64_t &> UnsignedLongRef;
typedef  uint64_t UnsignedLongT;
} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::UnsignedLong>
{
	static const bool is_specialized = true;

	static xdata::UnsignedLong min() throw()
	{ 
		return xdata::UnsignedLong(std::numeric_limits<xdata::UnsignedLongT>::min());
	}

	static xdata::UnsignedLong max() throw()
	{ 
		return xdata::UnsignedLong(std::numeric_limits<xdata::UnsignedLongT>::max());

	}

	static const int digits = std::numeric_limits<xdata::UnsignedLongT>::digits;
	static const int digits10 = std::numeric_limits<xdata::UnsignedLongT>::digits10;
	static const bool is_signed = false;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	static xdata::UnsignedLong epsilon() throw()
	{ 
		return xdata::UnsignedLong(0); 
	}
	static xdata::UnsignedLong round_error() throw()
	{ 
		return xdata::UnsignedLong(0);
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

	static xdata::UnsignedLong infinity() throw()
	{ 
		xdata::UnsignedLong i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::UnsignedLong quiet_NaN() throw()
	{ 
		return xdata::UnsignedLong(); 
	}

	static xdata::UnsignedLong signaling_NaN() throw()
	{ 
		return xdata::UnsignedLong(0); 
	}

	static xdata::UnsignedLong denorm_min() throw()
	{ 
		return xdata::UnsignedLong(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::UnsignedLongT>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/UnsignedLong.i"


#endif
