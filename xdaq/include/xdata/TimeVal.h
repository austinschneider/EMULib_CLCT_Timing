// $Id: TimeVal.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_TimeVal_h
#define _xdata_TimeVal_h

#include <string>
#include <limits>
#include "xdata/SimpleType.h"
#include "toolbox/TimeVal.h"

namespace xdata 
{
	template <class T>
	class TimeValType: public xdata::SimpleType<T> 
	{	
		public:
			//! Initialize with a number
			//
			TimeValType(T value);

			//! Uninitialized representing NaN
			//
			TimeValType();
			
			//! CTOR from string containing value
			//
			TimeValType (const std::string & value) throw (xdata::exception::Exception);
			
			virtual ~TimeValType();

			std::string type() const;

			std::string toString () 
				throw (xdata::exception::Exception);

			void  fromString (const std::string & value) 
				throw (xdata::exception::Exception);
	};

	typedef  TimeValType<toolbox::TimeVal> TimeVal;
	typedef  TimeValType<toolbox::TimeVal&> TimeValRef;
	typedef  toolbox::TimeVal TimeValT;
} // end namespace xdata

namespace std {
template<>
struct numeric_limits<xdata::TimeVal>
{
	static const bool is_specialized = true;

	static xdata::TimeVal min() throw()
	{ 
		return xdata::TimeVal(toolbox::TimeVal());
	}

	static xdata::TimeVal max() throw()
	{ 
		time_t max_sec = std::numeric_limits<time_t>::max();
		suseconds_t max_susec = std::numeric_limits<suseconds_t>::max();
		return xdata::TimeVal(toolbox::TimeVal(max_sec, max_susec));
	}

	static const int digits = 
		std::numeric_limits<time_t>::digits + 
		std::numeric_limits<suseconds_t>::digits;
		
	static const int digits10 = 
		std::numeric_limits<time_t>::digits10 +
		std::numeric_limits<suseconds_t>::digits10;
		
	static const bool is_signed = false;
	static const bool is_integer = true;
	static const bool is_exact = true;
	static const int radix = 2;
	static xdata::TimeVal epsilon() throw()
	{ 
		return xdata::TimeVal(toolbox::TimeVal()); 
	}
	static xdata::TimeVal round_error() throw()
	{ 
		return xdata::TimeVal(toolbox::TimeVal());
	}

	static const int min_exponent = 0;
	static const int min_exponent10 = 0;
	static const int max_exponent = 0;
	static const int max_exponent10 = 0;

	static const bool has_infinity = false;
	static const bool has_quiet_NaN = true;
	static const bool has_signaling_NaN = false;
	static const float_denorm_style has_denorm = denorm_absent;
	static const bool has_denorm_loss = false;

	static xdata::TimeVal infinity() throw()
	{ 
		return xdata::TimeVal(toolbox::TimeVal());
	}
	static xdata::TimeVal quiet_NaN() throw()
	{ 
		return xdata::TimeVal(); 
	}

	static xdata::TimeVal signaling_NaN() throw()
	{ 
		return xdata::TimeVal(); 
	}

	static xdata::TimeVal denorm_min() throw()
	{ 
		return xdata::TimeVal(); 
	}

	static const bool is_iec559 = false;
	static const bool is_bounded = true;
	static const bool is_modulo = true;

	// Don't know exactly what to do there
	static const bool traps = std::numeric_limits<time_t>::traps;
	static const bool tinyness_before = false;
	static const float_round_style round_style = round_toward_zero;
};
} // end of namespace std

#include "xdata/TimeVal.i"

#endif
