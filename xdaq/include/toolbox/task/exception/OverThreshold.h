// $Id: OverThreshold.h,v 1.2 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_exception_OverThreshold_h_
#define _toolbox_task_exception_OverThreshold_h_

#include "toolbox/task/exception/Exception.h"

namespace toolbox 
{
	namespace task 
	{
		namespace exception 
		{ 
			class OverThreshold: public toolbox::task::exception::Exception 
			{
				public: 
				OverThreshold( std::string name, std::string message, std::string module, int line, std::string function ): 
						toolbox::task::exception::Exception(name, message, module, line, function) 
				{} 

				OverThreshold( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
						toolbox::task::exception::Exception(name, message, module, line, function, e) 
				{} 
			}; 
		} 
	}
}

#endif
