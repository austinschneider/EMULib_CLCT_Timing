// $Id: Exception.h,v 1.2 2008/07/18 15:27:26 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight2g_exception_Exception_h_
#define _sentinel_spotlight2g_exception_Exception_h_

#include "sentinel/exception/Exception.h"


namespace sentinel {
	namespace spotlight2g {
		namespace exception { 
			class Exception: public sentinel::exception::Exception 
			{
				public: 
				Exception( std::string name, std::string message, std::string module, int line, std::string function ): 
					sentinel::exception::Exception(name, message, module, line, function) 
				{} 

				Exception( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					sentinel::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
