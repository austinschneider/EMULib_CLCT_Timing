// $Id: String.h,v 1.7 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_String_h_
#define _xdata_String_h_

#include <string>
#include "xdata/exception/Exception.h"
#include "xdata/Serializable.h"

namespace xdata {

//template <class T>
class String: public xdata::Serializable
{	
	public:
	
		String(std::string value);
		
		// uninitialized variable
		String();
		
		virtual ~String();
		
		//! Creation from const char *
		String( const char* s );
		
		//! Type cast operator returns the real value
		operator std::string ();
		
		void setValue(const xdata::Serializable & s);
		
		// Comparison operators inherited from Serializable
		int equals(const xdata::Serializable & s);
		
		//! Assignment from const char *
		String& operator=(const char * s);
		
		int operator==(const String & b);
				
		int operator!=(const String & b);
		
		int operator<(const String & b);
		
		int operator<=(const String & b);
		
		int operator>(const String & b);
		
		int operator>=(const String & b);
		
		int operator==(const std::string & s);
		
		int operator!=(const std::string & s);
		
		int operator<(const std::string & s);
		
		int operator>(const std::string & s);
		
		
		int operator==(const char* b);
		
		int operator!=(const char* b);
		
		int operator<(const char* b);
		
		int operator>(const char* b);
		
		std::string type() const;

		std::string toString () throw (xdata::exception::Exception);

		std::string toString (bool quoted) throw (xdata::exception::Exception);

		void  fromString (const std::string& value) throw (xdata::exception::Exception);
	
		std::string value_;	
};


} // end namespace xdata

#endif
