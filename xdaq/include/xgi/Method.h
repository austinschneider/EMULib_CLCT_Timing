// $Id: Method.h,v 1.5 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Method_h_
#define _xgi_Method_h_

#include <iostream>
#include <string.h>

#include "xgi/exception/Exception.h"
#include "toolbox/lang/Method.h"
#include "xgi/Input.h"
#include "xgi/Output.h"

namespace xgi {

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

		//! Invoke the HTTP callback
		virtual void invoke (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception) = 0;
		
		//! Get the HTTP method name
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
		return "cgi";
	}
        
	void invoke (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception)
        {
		// signature is void f(xgi::Input,xgi::Output)	
		(obj_->*func_)(in,out);
	}
	
	std::string name()
	{
		return name_;
	}
	
	void name(std::string name)
	{
		name_ = name;
	}
	
	LISTENER * obj_;
	void (LISTENER::*func_)(xgi::Input*,xgi::Output*) throw (xgi::exception::Exception);
	std::string name_;
};

//! binds a HTTP callback methd to a name and registers it
template <class LISTENER>
void bind(LISTENER * obj, void (LISTENER::*func)(xgi::Input*,xgi::Output*) throw (xgi::exception::Exception), const std::string & messageName)
{
	xgi::Method<LISTENER> * f = new xgi::Method<LISTENER>;
	f->obj_ = obj;
	f->func_ = func;
	f->name_ = messageName;
	obj->addMethod(f, messageName);	
}

} // end  of namespace

#endif
