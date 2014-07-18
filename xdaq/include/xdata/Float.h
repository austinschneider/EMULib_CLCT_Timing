// $Id: Float.h,v 1.10 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Float_h_
#define _xdata_Float_h_

#include <stdlib.h>
#include <errno.h>
#include <limits>
#include "xdata/SimpleType.h"


//! Float data type representation
/*! Data type that encapsulates a float number.
	This template class is to be used with
	the C++ float type only. It implements the
	required conversion routines.
*/

namespace xdata {

template <class T>
class FloatType: public xdata::SimpleType<T> 
{
	public:
	
		//! Constructor from float value
		FloatType(T value);
		
		//! uninitialized variable
		FloatType();
		
		//! CTOR from string containing value
		FloatType (const std::string & value) throw (xdata::exception::Exception);

		virtual ~FloatType();
		
		//! Return "float" data type
		std::string type() const;

		//! Put number into a string
		std::string toString () throw (xdata::exception::Exception);

		//! Create number from a string
		void  fromString (const std::string & value) throw (xdata::exception::Exception);
};



//! XTUPLE float data type to be used in applications
typedef  FloatType<float> Float;

//! A reference type to a XTUPLE float
typedef  FloatType<float&> FloatRef;
typedef float FloatT;

} // end namespace xdata

namespace std {
 template<>
    struct numeric_limits<xdata::Float>
    {
      static const bool is_specialized = true;

      static xdata::Float min() throw()
      { 	return xdata::Float(std::numeric_limits<xdata::FloatT>::min()); }
      static xdata::Float max() throw()
      { 	return xdata::Float(std::numeric_limits<xdata::FloatT>::max()); }

      static const int digits = std::numeric_limits<xdata::FloatT>::digits;
      static const int digits10 = std::numeric_limits<xdata::FloatT>::digits10;
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = std::numeric_limits<xdata::FloatT>::radix;
      static xdata::Float epsilon() throw()
      {  
      	return xdata::Float(std::numeric_limits<xdata::FloatT>::epsilon());  
      }
      static xdata::Float round_error() throw()
      { 
      	return xdata::Float(std::numeric_limits<xdata::FloatT>::round_error()); 
      }

      static const int min_exponent = std::numeric_limits<xdata::FloatT>::min_exponent;
      static const int min_exponent10 = std::numeric_limits<xdata::FloatT>::min_exponent10;
      static const int max_exponent = std::numeric_limits<xdata::FloatT>::max_exponent;
      static const int max_exponent10 = std::numeric_limits<xdata::FloatT>::max_exponent10;

      static const bool has_infinity = std::numeric_limits<xdata::FloatT>::has_infinity;
      static const bool has_quiet_NaN = std::numeric_limits<xdata::FloatT>::has_quiet_NaN;
      static const bool has_signaling_NaN = has_quiet_NaN;
      static const float_denorm_style has_denorm = std::numeric_limits<xdata::FloatT>::has_denorm;
      static const bool has_denorm_loss = std::numeric_limits<xdata::FloatT>::has_denorm_loss;

      static xdata::Float infinity() throw()
      { 
        xdata::Float d (std::numeric_limits<xdata::FloatT>::infinity());
	d.limits_.set(xdata::Infinity);
      	return d;   
      }
      static xdata::Float quiet_NaN() throw()
      { 
         xdata::Float f (std::numeric_limits<xdata::FloatT>::quiet_NaN());
	 f.limits_.set(xdata::NaN);
      	 return f;   
      }
      static xdata::Float signaling_NaN() throw()
      {  
        xdata::Float f (std::numeric_limits<xdata::FloatT>::signaling_NaN());
	f.limits_.set(xdata::NaN);
      	return f;  
      }
      static xdata::Float denorm_min() throw()
      { return  xdata::Float(std::numeric_limits<xdata::FloatT>::denorm_min()); }

      static const bool is_iec559
	= has_infinity && has_quiet_NaN && has_denorm == denorm_present;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = std::numeric_limits<xdata::FloatT>::traps;
      static const bool tinyness_before =  std::numeric_limits<xdata::FloatT>::tinyness_before;
      static const float_round_style round_style = round_to_nearest;
    };
} // end of namespace std

#include "xdata/Float.i"


#endif
