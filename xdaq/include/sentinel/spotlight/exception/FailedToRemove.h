// $Id: FailedToRemove.h,v 1.1 2008/09/01 13:22:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight_exception_FailedToRemove_h_
#define _sentinel_spotlight_exception_FailedToRemove_h_

#include "sentinel/spotlight/exception/Exception.h"


namespace sentinel {
	namespace spotlight {
		namespace exception { 
			class FailedToRemove: public sentinel::spotlight::exception::Exception 
			{
				public: 
				FailedToRemove( std::string name, std::string message, std::string module, int line, std::string function ): 
					sentinel::spotlight::exception::Exception(name, message, module, line, function) 
				{} 

				FailedToRemove( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					sentinel::spotlight::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
