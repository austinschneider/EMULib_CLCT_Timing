// $Id: NotFound.h,v 1.2 2008/07/18 15:27:26 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight_exception_NotFound_h_
#define _sentinel_spotlight_exception_NotFound_h_

#include "sentinel/spotlight/exception/Exception.h"


namespace sentinel {
	namespace spotlight {
		namespace exception { 
			class NotFound: public sentinel::spotlight::exception::Exception 
			{
				public: 
				NotFound( std::string name, std::string message, std::string module, int line, std::string function ): 
					sentinel::spotlight::exception::Exception(name, message, module, line, function) 
				{} 

				NotFound( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					sentinel::spotlight::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
