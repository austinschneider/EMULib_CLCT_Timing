// $Id: Vector.i,v 1.4 2008/07/18 15:28:08 gutleber Exp $

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

template<class T> std::string xdata::Vector<T>::type() const
{
	return "vector";
}

template<class T> xdata::Vector<T>::Vector()
{
	
	//cout << "this -> mangled name  <" << (char*)typeid(this).name() << ">" << endl;
	// string realname = toolbox::lang::demangle(typeid(this));
	//cout << "this -> demangled name  <" << realname << ">" << endl;
	
	//cout << "T -> mangled name  <" << (char*)typeid(T).name() << ">" << endl;
	// realname = toolbox::lang::demangle(typeid(T));
	//cout << "T -> demangled name  <" << realname << ">" << endl;
	
	/*if ( xdata::validtype(realname) )
	{
	
		cout << "T is a valid type" << endl;
		
	}
	else 
	{
	
		cout << "T is a invalid type" << endl;
	}
	*/
}

template<class T> xdata::Vector<T>::~Vector()
{
}

//implementation of abstract vector methods

template<class T> size_t xdata::Vector<T>::elements()
{
	return this->size();
}

template<class T> xdata::Serializable * xdata::Vector<T>::elementAt(size_t i)
{
	return &(*this)[i];
}

template<class T> void xdata::Vector<T>::setSize(size_t s)
{
	this->resize(s);
}	


template<class T> void xdata::Vector<T>::fromString (const std::string& value) throw (xdata::exception::Exception)
{
	XCEPT_RAISE (xdata::exception::Exception, "xdata::Vector fromString not implemented");
}


template<class T> std::string xdata::Vector<T>::toString () throw (xdata::exception::Exception)
{
	xdata::Vector<T> j;

	std::string r = "[";
	for (size_t i = 0;  i < this->size(); i++ ) 
	{
		if ( i !=  0 ) r += ",";
		r += this->elementAt(i)->toString();

	}
	r += "]";
	return r;
}

template<class T> xdata::Serializable & xdata::Vector<T>::operator=(const xdata::Serializable & s)
{
	*this = dynamic_cast<const xdata::Vector<T>& >(s);
	return *this;
}
