// $Id: Float.i,v 1.2 2008/07/18 15:28:08 gutleber Exp $

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
#include <cmath>

//! Constructor from float value
template<class T> xdata::FloatType<T>::FloatType(T value):xdata::SimpleType<T>(value)
{
	if ( std::isinf(value) != 0 )
	{
		this->limits_.set(xdata::Infinity);
	}
	else if ( std::isnan(value) != 0 )
	{
		this->limits_.set(xdata::NaN);
	}
}

//! uninitialized variable
template<class T> xdata::FloatType<T>::FloatType()
{
}

template<class T> xdata::FloatType<T>::FloatType(const std::string & value) throw (xdata::exception::Exception)
: xdata::SimpleType<T>(value)
{
	this->fromString(value);
}

template<class T> xdata::FloatType<T>::~FloatType()
{
}

//! Return "float" data type
template<class T> std::string xdata::FloatType<T>::type() const
{
		return "float";
}

//! Put number into a string
template<class T> std::string xdata::FloatType<T>::toString () throw (xdata::exception::Exception)
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
		sprintf (tmp, "%f", this->value_);
		return tmp;
	}	
}

//! Create number from a string
template<class T> void  xdata::FloatType<T>::fromString (const std::string & value) throw (xdata::exception::Exception)
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
	// sscanf (value.c_str(), "%f", &value_);
	// The following code will convert an integer
	// from any represenation, e.g. hex, oct, bin or decimal
	//
	char* firstWrong = 0;

	// would like to use strof here, but it only exists in C99
	//
	errno = 0;
	double tmp = strtod ( value.c_str(), &firstWrong );

	if (	(errno == ERANGE) || (*firstWrong != '\0') )
	{
		this->limits_.set(xdata::NaN);
		std::string msg = "Invalid float format. Value ";
		msg += value;
		msg += ", error at ";
		msg += firstWrong;
		XCEPT_RAISE (xdata::exception::Exception, msg);
	}

	this->value_ = (float) tmp;
}	

