// $Id: SimpleType.i,v 1.2 2008/07/18 15:28:08 gutleber Exp $

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
/*template<class T>  xdata::SimpleType<T>::SimpleType (const std::string & value) throw (xdata::exception::Exception)
{

}
*/

template<class T> xdata::SimpleType<T>::SimpleType ( T value) :  value_(value)
{
	limits_.reset();
}

template<class T> xdata::SimpleType<T>::SimpleType ()
{
	limits_.set(xdata::NaN);
}


template<class T> xdata::SimpleType<T>::~SimpleType() 
{
}

//! Type cast operator returns the real value
template<class T> xdata::SimpleType<T>::operator T () 
{ 
	return value_; 
}

/*
template<class T> T & xdata::SimpleType<T>::operator *() 
{ 
	return *this; 
}
*/

// virtual assignement operator
template<class T>  void xdata::SimpleType<T>::setValue(const xdata::Serializable & s) 
{	
	*this = dynamic_cast<const SimpleType<T> &>(s);	
}

//! C++ types compatible Assignment operator
template<class T> xdata::SimpleType<T>& xdata::SimpleType<T>::operator=(const T & value)
{
	std::cout << "template<class T> xdata::SimpleType<T>& xdata::SimpleType<T>::operator=(const T & value)" << std::endl;
	value_ = value;
	limits_.reset();
	return *this;
}

// ------------------------------------------------------------------

template<class T> int xdata::SimpleType<T>::operator==(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ == b.value_);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator!=(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ != b.value_);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator<(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ < b.value_);
	else
		return false;
}

template<class T> int xdata::SimpleType<T>::operator<=(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ <= b.value_);
	else
		return false;		
}

template<class T> int xdata::SimpleType<T>::operator>(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ > b.value_);
	else
		return false;		
}

template<class T> int xdata::SimpleType<T>::operator>=(const SimpleType<T> & b)
{
	if ( this->isFinite() && b.isFinite() )
		return (value_ >= b.value_);
	else
		return false;			
}

// ------------------------------------------------------------------

template<class T> int xdata::SimpleType<T>::operator==(const T & b)
{
	if ( this->isFinite() )
		return (value_ == b);
	else
		return false;
}

template<class T> int xdata::SimpleType<T>::operator!=(const T & b)
{
	if ( this->isFinite() )
		return (value_ != b);
	else
		return false;
}

template<class T> int xdata::SimpleType<T>::operator!()
{
	if ( this->isFinite() )
		return (!value_);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator<(const T & b)
{
	if ( this->isFinite() )
		return (value_ < b);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator<=(const T & b)
{
	if ( this->isFinite() )
		return (value_ <= b);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator>(const T & b)
{
	if ( this->isFinite() )
		return (value_ > b);
	else
		return false;	
}

template<class T> int xdata::SimpleType<T>::operator>=(const T & b)
{
	if ( this->isFinite() )
		return (value_ >= b);
	else
		return false;	
}

// ------------------------------------------------------------------

template<class T> int xdata::SimpleType<T>::equals(const xdata::Serializable & s)
{
	return (*this == dynamic_cast<const xdata::SimpleType<T>&>(s));
}

// ------------------------------------------------------------------
/*template<class T> T& xdata::SimpleType<T>::operator++()
{
	return (++value_);
}

template<class T> T& xdata::SimpleType<T>::operator--()
{
	return (--value_);
}

template<class T> T xdata::SimpleType<T>::operator++(int)
{
	value_++;
	return value_;
}

template<class T> T xdata::SimpleType<T>::operator--(int)
{
	value_--;
	return value_;
}
*/
