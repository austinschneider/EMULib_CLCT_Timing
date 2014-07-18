// $Id: NoJobs.h,v 1.2 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_exception_NoJobs_h_
#define _toolbox_task_exception_NoJobs_h_

#include "toolbox/task/exception/Exception.h"

namespace toolbox {
	namespace task {
	namespace exception { 
		class NoJobs: public toolbox::task::exception::Exception 
		{
			public: 
			NoJobs( std::string name, std::string message, std::string module, int line, std::string function ): 
					toolbox::task::exception::Exception(name, message, module, line, function) 
			{} 
			
			NoJobs( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					toolbox::task::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
	}
}

#endif
