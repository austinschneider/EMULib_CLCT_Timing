// $Id: TimeVal.i,v 1.3 2008/07/18 15:28:08 gutleber Exp $

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
#include<sstream>

template<class T> xdata::TimeValType<T>::TimeValType(T value): xdata::SimpleType<T>(value)
{
}


// uninitialized variable
template<class T> xdata::TimeValType<T>::TimeValType()
{
}

template<class T> xdata::TimeValType<T>::TimeValType(const std::string & value) 
	throw (xdata::exception::Exception)
: xdata::SimpleType<T>()
{
	this->fromString(value);
}

template<class T> xdata::TimeValType<T>::~TimeValType()
{
}

template<class T> std::string xdata::TimeValType<T>::type() const
{
	return "time";
}

template<class T> std::string xdata::TimeValType<T>::toString () 
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
		// The format is: %Z %Y/%m/%d %H:%M:%S
		// %Z is the timezone
		// We would like to encode the time zone, too, but this does
		// not work due to a problem with strptime
		//
		// So just put seconds and microseconds into a stringstream.
		// std::stringstream t;
		// t << hex << this->value_.sec() << ' ' << this->value_.usec();
		return this->value_.toString("", toolbox::TimeVal::gmt);
	}
}

template<class T> void  xdata::TimeValType<T>::fromString (const std::string & value)
	throw (xdata::exception::Exception)
{
	this->limits_.reset(); // reset any bits
	if ((value == "NaN") || (value == ""))
	{
		// empty string is not a number
		this->limits_.set(xdata::NaN);
		return;
	}
	
	// The expected format is: %Z %Y/%m/%d %H:%M:%S
	// %Z is the timezone, internally create a GMT time value out of this by specifying toolbox::TimeVal::gmt
	// %Z DOES NOT WORK!!!
	// So just expect seconds.useconds in a stringstream style
	/*
	time_t sec;
	suseconds_t usec;
	std::istringstream is;
	is.str(value);
	is >> hex >> sec >> usec;
	this->value_.sec(sec);
	this->value_.usec(usec);
	*/
	try
	{
		this->value_.fromString (value, "", toolbox::TimeVal::gmt);
	}
	catch (toolbox::exception::Exception& e)
	{
		this->limits_.set(xdata::NaN);
		XCEPT_RETHROW (xdata::exception::Exception, "Failed to parse TimeVal string", e);
	}
}	
