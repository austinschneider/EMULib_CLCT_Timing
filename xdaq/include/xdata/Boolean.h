// $Id: Boolean.h,v 1.11 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Boolean_h
#define _xdata_Boolean_h

#include <string>
#include <limits>
#include "xdata/SimpleType.h"

namespace xdata {

template <class T>
class BooleanType: public xdata::SimpleType<T> 
{	
	public:
	
		BooleanType(T value);
		
		// uninitialized variable
		BooleanType();
		BooleanType (const std::string & value) throw (xdata::exception::Exception);
		virtual ~BooleanType();
		
		std::string type() const;

		std::string toString () throw (xdata::exception::Exception);

		void  fromString (const std::string & value) throw (xdata::exception::Exception);
};



typedef  BooleanType<bool> Boolean;
typedef  BooleanType<bool&> BooleanRef;
typedef  bool BooleanT;
} // end namespace xdata

namespace std {
  template<>
    struct numeric_limits<xdata::Boolean>
    {
      static const bool is_specialized = true;

      static xdata::Boolean min() throw()
      { 
      	return xdata::Boolean(std::numeric_limits<xdata::BooleanT>::min());; 
      }
      
      static xdata::Boolean max() throw()
      { 
	return xdata::Boolean(std::numeric_limits<xdata::BooleanT>::max());
      }

      static const int digits = 1;
      static const int digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;
      static xdata::Boolean epsilon() throw()
      { 
      	return xdata::Boolean(false); 
      }
      
      static xdata::Boolean round_error() throw()
      { 
      	return xdata::Boolean(false);  
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

      static xdata::Boolean infinity() throw()
      { 
      	return xdata::Boolean(false);  
      }
      static xdata::Boolean quiet_NaN() throw()
      { 
      	return xdata::Boolean();
      }
      static xdata::Boolean signaling_NaN() throw()
      { 
      	return xdata::Boolean(false);  
      }
      
      static xdata::Boolean denorm_min() throw()
      { 
      	return xdata::Boolean(false);  
      }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      // It is not clear what it means for a boolean type to trap.
      // This is a DR on the LWG issue list.  Here, I use integer
      // promotion semantics.
      static const bool traps = std::numeric_limits<xdata::BooleanT>::traps;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };
}

#include "xdata/Boolean.i"

#endif
