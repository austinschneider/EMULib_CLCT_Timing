// $Id: Exception.hh,v 1.1 2007/07/09 11:55:46 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedbuilder_exception_MyrinetError_h_
#define _fedbuilder_exception_MyrinetError_h_

#include "fedbuilder/exception/Exception.h"

namespace fedbuilder {
	namespace exception { 
		class MyrinetError: public fedbuilder::exception::Exception 
		{
			public: 
			MyrinetError( std::string name, std::string message, std::string module, int line, std::string function ): 
					fedbuilder::exception::Exception(name, message, module, line, function) 
			{} 
			MyrinetError( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					fedbuilder::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
