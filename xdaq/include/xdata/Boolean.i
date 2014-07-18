// $Id: Boolean.i,v 1.2 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
#include <string.h>
#include <stdlib.h>

template<class T> xdata::BooleanType<T>::BooleanType(T value): xdata::SimpleType<T>(value)
{
}


// uninitialized variable
template<class T> xdata::BooleanType<T>::BooleanType()
{
}

template<class T> xdata::BooleanType<T>::BooleanType(const std::string & value) throw (xdata::exception::Exception)
{
	this->fromString(value);
}

template<class T> xdata::BooleanType<T>::~BooleanType()
{
}

template<class T> std::string xdata::BooleanType<T>::type() const
{
	return "bool";
}

template<class T> std::string xdata::BooleanType<T>::toString () throw (xdata::exception::Exception)
{	
	if (this->isNaN())
	{
		return "NaN";
	}
	else if ( this->value_ ) return "true";
	else return "false";
}

template<class T> void  xdata::BooleanType<T>::fromString (const std::string & value) throw (xdata::exception::Exception)
{
	this->limits_.reset(); // reset any bits
	
	if (strcasecmp(value.c_str(),"true") == 0 ) 
	{
		this->value_ = true;
	} 
	else if (strcasecmp(value.c_str(),"false") == 0 ) 
	{
		this->value_ = false;
	} 
	else
	{
		// any other value is not a number
		this->limits_.set(xdata::NaN);
	}	
}	
