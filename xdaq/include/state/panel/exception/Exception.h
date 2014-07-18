// $Id: Exception.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_exception_Exception_h_
#define _statepanel_exception_Exception_h_

#include "xcept/Exception.h"

namespace state {
namespace panel {
	namespace exception { 
		class Exception: public xcept::Exception
		{
			public: 
			Exception( std::string name, std::string message, std::string module, int line, std::string function ): 
				xcept::Exception(name, message, module, line, function) 
			{} 

			Exception( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
				xcept::Exception(name, message, module, line, function, e) 
			{} 

		};  
	}
}
}
#endif

