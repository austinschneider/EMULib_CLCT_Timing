// $Id: UnsignedShort.i,v 1.2 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
#include <stdlib.h>

template<class T> xdata::UnsignedShortType<T>::UnsignedShortType(T value): xdata::SimpleType<T>(value)
{		
}

// uninitialized variable
template<class T> xdata::UnsignedShortType<T>::UnsignedShortType()
{		
}
template<class T> xdata::UnsignedShortType<T>::UnsignedShortType(const std::string & value) throw (xdata::exception::Exception)
: xdata::SimpleType<T>(value)
{
	this->fromString(value);
}
template<class T> xdata::UnsignedShortType<T>::~UnsignedShortType()
{		
}

template<class T> std::string xdata::UnsignedShortType<T>::type() const
{
		return "unsigned short";
}

template<class T> std::string xdata::UnsignedShortType<T>::toString () 
	throw (xdata::exception::Exception)
{
	if (this->isInf())
	{
		return "infinite";
	}
	else if (this->isNaN())
	{
		return "NaN";
	}
	else
	{
		char tmp[255];
		sprintf (tmp, "%u", this->value_);
		return tmp;
	}
}

template<class T> void  xdata::UnsignedShortType<T>::fromString
(
	const std::string & value
)
	throw (xdata::exception::Exception)
{
	this->limits_.reset(); // reset any bits
	if ((value == "") || (value == "NaN"))
	{
		// empty string is not a number
		this->limits_.set(xdata::NaN);
		return;
	}
	else if (value == "infinite")
	{
		this->limits_.set(xdata::Infinity);
		return;
	}

	  char* firstWrong = 0;

          unsigned long tmp = strtoul ( value.c_str(), &firstWrong, 0 );

          if (    (tmp > USHRT_MAX) ||
                  (*firstWrong != '\0') )
          {
	  	this->limits_.set(xdata::NaN);
		std::string msg = "Invalid unsigned short integer format/size. Value ";
		msg += value;
		msg += ", error at ";
		msg += firstWrong;
		XCEPT_RAISE (xdata::exception::Exception, msg);
          }

	  this->value_ = (unsigned short)tmp;
}


