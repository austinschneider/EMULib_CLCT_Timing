// $Id: Integer64.i,v 1.2 2008/07/18 15:28:08 gutleber Exp $

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

template<class T> xdata::Integer64Type<T>::Integer64Type(T value): xdata::SimpleType<T>(value)
{		
}

// uninitialized variable
template<class T> xdata::Integer64Type<T>::Integer64Type()
{		
}

template<class T> xdata::Integer64Type<T>::Integer64Type
(
	const std::string & value
) 
	throw (xdata::exception::Exception)
	: xdata::SimpleType<T>(value)
{
	this->fromString(value);
}

template<class T> xdata::Integer64Type<T>::~Integer64Type()
{		
}

template<class T> std::string xdata::Integer64Type<T>::type() const
{
	return "int 64";
}

template<class T> std::string xdata::Integer64Type<T>::toString () 
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
	
#if (__WORDSIZE == 32 ) 
		sprintf (tmp, "%lld", (long long) this->value_);
#elif (__WORDSIZE == 64 )
		sprintf (tmp, "%ld", (long) this->value_);
#else
#error "xdata type not supported"
#endif
		return tmp;
	}
}

template<class T> void  xdata::Integer64Type<T>::fromString 
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

	errno = 0;
#if (__WORDSIZE == 32 ) 
	this->value_ = strtoll ( value.c_str(), &firstWrong, 0 );
#elif (__WORDSIZE == 64 )
	this->value_ = strtol ( value.c_str(), &firstWrong, 0 );
#else
#error "xdata type not supported"
#endif
	if ((errno == ERANGE) || (*firstWrong != '\0'))
	{
		this->limits_.set(xdata::NaN);
		std::string msg = "Failure creating 'int 64' from string '";
		msg += value;
		msg += "', error at position ";
		msg += firstWrong;
		XCEPT_RAISE (xdata::exception::Exception, msg);
	}
}

template<class T> T& xdata::Integer64Type<T>::operator++()
{
	if ( std::numeric_limits<xdata::Integer64>::max()  == this->value_ )
	{
		this->limits_.set(xdata::Infinity);
		return this->value_;
	}
	else
	{
		return (++this->value_);
	}
}

template<class T> T& xdata::Integer64Type<T>::operator--()
{
	if ( std::numeric_limits<xdata::Integer64>::min()  == this->value_ )
	{
		this->limits_.set(xdata::Infinity);
		return this->value_;
	}
	else
	{
		return (--this->value_);
	}	
}

template<class T> T xdata::Integer64Type<T>::operator++(int)
{
	if ( std::numeric_limits<xdata::Integer64>::max()  == this->value_ )
	{
		this->limits_.set(xdata::Infinity);
		return this->value_;
	}
	else
	{
		this->value_++;
		return this->value_;
	}
}

template<class T> T xdata::Integer64Type<T>::operator--(int)
{
	if ( std::numeric_limits<xdata::Integer64>::min()  == this->value_ )
	{
		this->limits_.set(xdata::Infinity);
		return this->value_;
	}
	else
	{
		this->value_--;
		return this->value_;
	}	
}
