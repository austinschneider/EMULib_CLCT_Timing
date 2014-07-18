// $Id: UnsignedShort.h,v 1.11 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_UnsignedShort_h_
#define _xdata_UnsignedShort_h_

#include <string>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class UnsignedShortType: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		UnsignedShortType(T value);
		
		//! Uninitialized representing NaN
		//
		UnsignedShortType();
		
		//! CTOR from string containing value
		//
		UnsignedShortType (const std::string & value) 
			throw (xdata::exception::Exception);

		virtual ~UnsignedShortType();
		
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

typedef  UnsignedShortType<unsigned short> UnsignedShort;
typedef  UnsignedShortType<unsigned short&> UnsignedShortRef;
typedef  unsigned short UnsignedShortT;
} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::UnsignedShort>
{
	static const bool is_specialized = true;

	static xdata::UnsignedShort min() throw()
	{ 
		return xdata::UnsignedShort(std::numeric_limits<xdata::UnsignedShortT>::min());
	}

	static xdata::UnsignedShort max() throw()
	{ 
		return xdata::UnsignedShort(std::numeric_limits<xdata::UnsignedShortT>::max());

	}

	static const int digits = std::numeric_limits<xdata::UnsignedShortT>::digits;
	static const int digits10 = std::numeric_limits<xdata::UnsignedShortT>::digits10;
	static const bool is_signed = false;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	static xdata::UnsignedShort epsilon() throw()
	{ 
		return xdata::UnsignedShort(0); 
	}
	static xdata::UnsignedShort round_error() throw()
	{ 
		return xdata::UnsignedShort(0);
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

	static xdata::UnsignedShort infinity() throw()
	{ 
		xdata::UnsignedShort i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::UnsignedShort quiet_NaN() throw()
	{ 
		return xdata::UnsignedShort(); 
	}

	static xdata::UnsignedShort signaling_NaN() throw()
	{ 
		return xdata::UnsignedShort(0); 
	}

	static xdata::UnsignedShort denorm_min() throw()
	{ 
		return xdata::UnsignedShort(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::UnsignedShortT>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/UnsignedShort.i"

#endif
