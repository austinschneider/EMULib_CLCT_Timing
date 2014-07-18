// $Id: Action.h,v 1.4 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_Action_h_
#define _toolbox_task_Action_h_

#include <string>

#include "toolbox/lang/Method.h"

namespace toolbox 
{
	namespace task 
	{
		class WorkLoop;
		
		class ActionSignature: public toolbox::lang::Method
		{
	
			public:
			virtual ~ActionSignature()
			{
			}

			virtual bool invoke (toolbox::task::WorkLoop *) = 0;

			//! Get the exception method name
			//
			virtual std::string name() = 0;
		};

		template <class LISTENER>
		class Action: public ActionSignature 
		{
			public:

			virtual ~Action()
			{
			}
			
			std::string type()
			{
				return "action";
			}

			bool invoke (toolbox::task::WorkLoop * wl) 
			{
				return (obj_->*func_)(wl);
			}

			std::string name()
			{
				return name_;
			}

			void name(const std::string & name)
			{
				name_ = name;
			}

			LISTENER * obj_;
			bool (LISTENER::*func_)(toolbox::task::WorkLoop *);
			std::string name_;

		};


		template <class LISTENER>
		toolbox::task::Action<LISTENER> * bind(LISTENER * obj, bool (LISTENER::*func)(toolbox::task::WorkLoop *), const std::string & name) 
		{
			toolbox::task::Action<LISTENER> * f = new toolbox::task::Action<LISTENER>;
			f->obj_ = obj;
			f->func_ = func;
			f->name_ = name;
			obj->addMethod(f, name);	
			return f;
		}

	} // end of namespace task

} // end  of namespace toolbox



#endif
