// $Id: Integer32.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Integer32_h_
#define _xdata_Integer32_h_

#include <string>
#include <errno.h>
#include <stdint.h>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class Integer32Type: public xdata::SimpleType<T> 
{
	public:
		//! Initialize with a number
		//
		Integer32Type(T value);
		
		//! Uninitialized representing NaN
		//
		Integer32Type();
		
		//! CTOR from string containing value
		//
		Integer32Type (const std::string & value) throw (xdata::exception::Exception);

		virtual ~Integer32Type();
		
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

		void fromString (const std::string & value) throw (xdata::exception::Exception);			
};

typedef  Integer32Type<int32_t> Integer32;
typedef  Integer32Type<int32_t &> Integer32Ref;
typedef  int32_t Integer32T;
 
} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::Integer32>
{
	static const bool is_specialized = true;

	static xdata::Integer32 min() throw()
	{ 
		return xdata::Integer32(std::numeric_limits<xdata::Integer32T>::min());
	}

	static xdata::Integer32 max() throw()
	{ 
		return xdata::Integer32(std::numeric_limits<xdata::Integer32T>::max());

	}

	static const int digits = std::numeric_limits<xdata::Integer32T>::digits;
	static const int digits10 = std::numeric_limits<xdata::Integer32T>::digits10;
	static const bool is_signed = true;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	
	static xdata::Integer32 epsilon() throw()
	{ 
		return xdata::Integer32(0); 
	}
	
	static xdata::Integer32 round_error() throw()
	{ 
		return xdata::Integer32(0);
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

	static xdata::Integer32 infinity() throw()
	{ 
		xdata::Integer32 i(0);
		i.limits_.set(xdata::Infinity);
		return i; 
	}
	static xdata::Integer32 quiet_NaN() throw()
	{ 
		return xdata::Integer32(); 
	}

	static xdata::Integer32 signaling_NaN() throw()
	{ 
		return xdata::Integer32(0); 
	}

	static xdata::Integer32 denorm_min() throw()
	{ 
		return xdata::Integer32(0); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	static const bool traps = std::numeric_limits<xdata::Integer32T>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/Integer32.i"


#endif
