// $Id: Handler.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_exception_Handler_h_
#define _toolbox_exception_Handler_h_

#include <string>

#include "xcept/Exception.h"
#include "toolbox/lang/Method.h"

namespace toolbox 
{
	namespace exception 
	{
		
		/**
		* Basic interface for exception handlers.
		 *
		 * <p>xcept::Handler is a callback interface that an implementation
		 * can call when reporting errors that happens while processing data, or
		 * when doing some other processing (e.g. sending a message).</p>
		 *
		 * <p>The application that wants to handle exceptions that are raised
		 * asynchronously is expected to implement this interface.</p>
		 *
		 * @see Class#Method
		 */
		
		class HandlerSignature: public toolbox::lang::Method
		{
	
			public:
			virtual ~HandlerSignature()
			{
			}

			/**
			* This method is called on the error handler when an error occures.
			 * 
			 * <p><b>An implementation of this callback shall not throw an exception."</b></p>

			 * @param ex The exception object that describes the error, this object
			 *                 may be reused across multiple
			 *                 calls to the handleError method.
			 * @return If the onError method returns <code>true</code> the exception could be handled and
			 *		the implementation should continue as if the error didn't happen
			 *         when possible, if the method returns <code>false</code> then the
			 *         implementation should stop the current processing when
			 *         possible.
			 *
			 */

			virtual bool invoke (xcept::Exception& ex, void * context) = 0;

			//! Get the exception method name
			//
			virtual std::string name() = 0;
		};

		template <class LISTENER>
		class Handler: public HandlerSignature 
		{
			public:

			virtual ~Handler()
			{
			}


			std::string type()
			{
				return "exception";
			}

			bool invoke (xcept::Exception& exception, void * context) 
			{
				return (obj_->*func_)(exception,context);
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
			bool (LISTENER::*func_)(xcept::Exception&, void *);
			std::string name_;

		};


		template <class LISTENER>
		toolbox::exception::Handler<LISTENER> * bind(LISTENER * obj, bool (LISTENER::*func)(xcept::Exception&, void *), const std::string & messageName) 
		{
			toolbox::exception::Handler<LISTENER> * f = new toolbox::exception::Handler<LISTENER>;
			f->obj_ = obj;
			f->func_ = func;
			f->name_ = messageName;
			obj->addMethod(f, messageName);	
			return f;
		}

	} 

} // end  of namespace



#endif
