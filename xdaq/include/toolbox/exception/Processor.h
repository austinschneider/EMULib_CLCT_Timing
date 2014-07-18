// $Id: Processor.h,v 1.5 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_exception_Processor_h_
#define _toolbox_exception_Processor_h_

#include "toolbox/squeue.h"
#include "toolbox/Task.h"
#include "toolbox/exception/Handler.h"

namespace toolbox
{
	namespace exception
	{
		class Processor: public toolbox::Task
		{
			public:
			//! Retrieve a pointer to the singleton
			//
			static Processor* getInstance();
			
			//! Destroy the singleton
			//
			static void destroyInstance();
		
			struct HandlerInfo
			{
				xcept::Exception* exception;
				toolbox::exception::HandlerSignature * handler;
				void * context;	
			};

			public:

				Processor();
				~Processor();

				//! Enqueue an exception into the exception processor task
				//
				void push (xcept::Exception & ex, toolbox::exception::HandlerSignature* handler, void * context);
				
				//! Set a defualt exception handler callback
				//
				void setDefaultHandler(toolbox::exception::HandlerSignature* handler);
				
				//! The exception handler thread routine
				//
				int svc();

			private:
				static Processor* instance_;

				toolbox::squeue<toolbox::exception::Processor::HandlerInfo> exceptions_;
				toolbox::exception::HandlerSignature* defaultHandler_;
		};
		
		Processor* getProcessor();		
	}
}

#endif
