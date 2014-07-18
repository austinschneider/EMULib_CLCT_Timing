// $Id: Method.h,v 1.7 2008/07/18 15:26:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_Method_h_
#define _i2o_Method_h_

#include <iostream>
#include "i2o/i2o.h"
#include "i2o/shared/i2omsg.h"

#include "toolbox/lang/Method.h"
#include "toolbox/mem/Reference.h"
#include "i2o/exception/Exception.h"

#define XDAQ_ORGANIZATION_ID 0x100
#define XDAQ_XFUNCTION_PLACEMENT  0x0;
#define XDAQ_MULTICAST 0x2

namespace i2o {
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

		//! Invoke the I2O callback
		virtual void invoke (toolbox::mem::Reference* arg) throw (i2o::exception::Exception) = 0;
		
		//! Get the I2O method code (function id)
		virtual U16 fid() = 0;
};

template <class LISTENER>
struct Method: public i2o::MethodSignature
{
	public:
	virtual ~Method()
	{
	}

	std::string type()
	{
		return "i2o";
	}
	
	void invoke(toolbox::mem::Reference* arg) throw (i2o::exception::Exception)
	{
		(obj_->*func_)(arg);
	}
	
	U16 fid()
	{
		return fid_;
	}
	
	void fid(U16 fid)
	{
		fid_ = fid;
	}

	LISTENER * obj_;
	void (LISTENER::*func_)(toolbox::mem::Reference*) throw (i2o::exception::Exception);
	U16 fid_;
};

//! binds a I2O callback function to a message code and registers it
template <class LISTENER>
void bind( LISTENER * obj, void (LISTENER::*func)(toolbox::mem::Reference*) throw (i2o::exception::Exception), U8 msgCode) 
{
	i2o::Method<LISTENER> * f = new i2o::Method<LISTENER>;
	f->obj_ = obj;
	f->func_ = func;
	f->fid_ = msgCode;
	obj->addMethod(f, msgCode);
}

//! binds a I2O callback function to a message code and organization id (code = msgCode | OrganizationID) and registers it
template <class LISTENER>
void bind(LISTENER * obj, void (LISTENER::*func)(toolbox::mem::Reference*) throw (i2o::exception::Exception), U8 msgCode, U16 OrganizationID)
{     
	i2o::Method<LISTENER> * f = new i2o::Method<LISTENER>;
	f->obj_ = obj;
	f->func_ = func;
	U16 code = ((U16) msgCode) | OrganizationID;
	f->fid_ = code;
	obj->addMethod(f, code);
}


} // end of namespace

#endif
