// $Id: TestAlternateException.h,v 1.1 2008/12/02 15:41:21 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_tester_exception_TestAlternateException_h_
#define _sentinel_tester_exception_TestAlternateException_h_

#include "sentinel/exception/Exception.h"


namespace sentinel {
	namespace tester {
		namespace exception { 
			class TestAlternateException: public sentinel::exception::Exception 
			{
				public: 
				TestAlternateException( std::string name, std::string message, std::string module, int line, std::string function ): 
					sentinel::exception::Exception(name, message, module, line, function) 
				{} 

				TestAlternateException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					sentinel::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
