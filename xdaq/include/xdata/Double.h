// $Id: Double.h,v 1.10 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Double_h_
#define _xdata_Double_h_

#include <limits>
#include <stdlib.h>
#include <errno.h>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class DoubleType: public xdata::SimpleType<T> 
{
	public:
		DoubleType(T value);
		
		// uninitialized variable
		DoubleType();
		DoubleType (const std::string & value) throw (xdata::exception::Exception);

		virtual ~DoubleType();
		
		std::string type() const;

		std::string toString () throw (xdata::exception::Exception);

		void  fromString (const std::string & value) throw (xdata::exception::Exception);
};


typedef  DoubleType<double> Double;
typedef  DoubleType<double&> DoubleRef;
typedef  double DoubleT;
} // end name space

namespace std {

 template<>
    struct numeric_limits<xdata::Double>
    {
      static const bool is_specialized = true;

      static xdata::Double min() throw()
      { 
      	return xdata::Double(std::numeric_limits<xdata::DoubleT>::min()); 
      }
      static xdata::Double max() throw()
      { 
      	return xdata::Double(std::numeric_limits<xdata::DoubleT>::max()); 
      }

      static const int digits = std::numeric_limits<xdata::DoubleT>::digits;
      static const int digits10 = std::numeric_limits<xdata::DoubleT>::digits10;
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = std::numeric_limits<xdata::DoubleT>::radix;
      static xdata::Double epsilon() throw()
      { 
      	return xdata::Double(std::numeric_limits<xdata::DoubleT>::epsilon()); 
      }
      static xdata::Double round_error() throw()
      { 
      	return xdata::Double(std::numeric_limits<xdata::DoubleT>::round_error());
      }

      static const int min_exponent = std::numeric_limits<xdata::DoubleT>::min_exponent;
      static const int min_exponent10 = std::numeric_limits<xdata::DoubleT>::min_exponent10;
      static const int max_exponent = std::numeric_limits<xdata::DoubleT>::max_exponent;
      static const int max_exponent10 = std::numeric_limits<xdata::DoubleT>::max_exponent10;

      static const bool has_infinity = std::numeric_limits<xdata::DoubleT>::has_infinity;
      static const bool has_quiet_NaN = std::numeric_limits<xdata::DoubleT>::has_quiet_NaN;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm = std::numeric_limits<xdata::DoubleT>::has_denorm;
      static const bool has_denorm_loss = std::numeric_limits<xdata::DoubleT>::has_denorm_loss;

      static xdata::Double infinity() throw()
      { 
      	xdata::Double d (std::numeric_limits<xdata::DoubleT>::infinity());
	d.limits_.set(xdata::Infinity);
      	return d;   
      }
      static xdata::Double quiet_NaN() throw()
      { 
      	xdata::Double d (std::numeric_limits<xdata::DoubleT>::quiet_NaN());
	d.limits_.set(xdata::NaN);
      	return d;  
      }
      static xdata::Double signaling_NaN() throw()
      { 
      	xdata::Double d (std::numeric_limits<xdata::DoubleT>::signaling_NaN());
	d.limits_.set(xdata::NaN);
      	return d; 
      }
      static xdata::Double denorm_min() throw()
      { 
	return xdata::Double(std::numeric_limits<xdata::DoubleT>::denorm_min());
      }

      static const bool is_iec559
	= has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = std::numeric_limits<xdata::DoubleT>::traps;
      static const bool tinyness_before = std::numeric_limits<xdata::DoubleT>::tinyness_before;
      static const float_round_style round_style = round_to_nearest;
    };
}

#include "xdata/Double.i"

#endif
