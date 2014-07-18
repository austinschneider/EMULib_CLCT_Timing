// $Id: Method.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_Method_h_
#define _xoap_Method_h_

#include <iostream>
#include <string.h>
#include "toolbox/lang/Method.h"
#include "xoap/MessageReference.h"
#include "xoap/exception/Exception.h"

namespace xoap {

//
// This functor support any  type of member functions :)
// ( namely a listener )
//

class MethodSignature: public toolbox::lang::Method
{
	public:
		virtual ~MethodSignature()
		{
		}

		//! Invoke the SOAP callback
		virtual xoap::MessageReference invoke (xoap::MessageReference arg) throw (xoap::exception::Exception) = 0;
		
		//! Get the SOAP method name
		virtual std::string name() = 0;
};

template <class LISTENER>
class Method: public MethodSignature 
{
	public:
	
	virtual ~Method()
	{
	}

	std::string type()
	{
		return "soap";
	}
        
	xoap::MessageReference invoke (xoap::MessageReference arg) throw (xoap::exception::Exception)
        {
		// signature is xoap::MessageReference f(xoap::MessageReference)	
		return (obj_->*func_)(arg);
	}
	
	std::string name()
	{
		return name_;
	}
	
	void name(std::string name)
	{
		name_ = name;
	}

	void namespaceURI(std::string namespaceURI)
	{
		namespaceURI_ = namespaceURI;
	}

	std::string namespaceURI()
	{
		return namespaceURI_;
	}
	
	LISTENER * obj_;
	xoap::MessageReference (LISTENER::*func_)(xoap::MessageReference) throw (xoap::exception::Exception);
	std::string name_;
	std::string namespaceURI_;
};

//! binds a SOAP callback function to a message name and registers it
/*! Using this function, an application can bind
a tag name to a method of an XDAQ application class.
Upon reception of the tag in a SOAP request, the 
XDAQ executive will call back the bound object and function.
Each command is preceeded by a namespace URI definition. 
*/


template <class LISTENER>
void bind(LISTENER * obj, 
		xoap::MessageReference (LISTENER::*func)(xoap::MessageReference) throw (xoap::exception::Exception), 
		const std::string & messageName, 
		const std::string & namespaceURI) 
{
	xoap::Method<LISTENER> * f = new xoap::Method<LISTENER>;
	f->obj_ = obj;
	f->func_ = func;
	f->namespaceURI_ = namespaceURI;
	f->name_ = messageName;
	std::string name = namespaceURI + ":";
	name += messageName;
	obj->addMethod(f, name);	
}

} // end of namespace xoap 

#endif
