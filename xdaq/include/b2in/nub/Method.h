// $Id: Method.h,v 1.3 2008/07/18 15:26:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_Method_h_
#define _b2in_Method_h_

#include <iostream>

#include "toolbox/lang/Method.h"
#include "toolbox/mem/Reference.h"
#include "xdata/Properties.h"
#include "b2in/nub/exception/Exception.h"

namespace b2in {

namespace nub {
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
		
		//! Invoke the B2IN callback
		virtual void invoke (toolbox::mem::Reference* arg, xdata::Properties & plist) throw (b2in::nub::exception::Exception) = 0;
};

template <class LISTENER>
struct Method: public b2in::nub::MethodSignature
{
	public:

	virtual ~Method()
	{
	}

	std::string type()
	{
		return "b2in";
	}
	
	void invoke(toolbox::mem::Reference* arg,  xdata::Properties & plist) throw (b2in::nub::exception::Exception)
	{
		(obj_->*func_)(arg,plist);
	}
	
	LISTENER * obj_;
	void (LISTENER::*func_)(toolbox::mem::Reference*, xdata::Properties & ) throw (b2in::nub::exception::Exception);
};

//! binds a B2IN callback function to a message code and registers it
template <class LISTENER>
void bind( LISTENER * obj, void (LISTENER::*func)(toolbox::mem::Reference*, xdata::Properties & ) throw (b2in::nub::exception::Exception)) 
{
	b2in::nub::Method<LISTENER> * f = new b2in::nub::Method<LISTENER>;
	f->obj_ = obj;
	f->func_ = func;
	obj->addMethod(f, 0);
}

}} // end of namespace

#endif
