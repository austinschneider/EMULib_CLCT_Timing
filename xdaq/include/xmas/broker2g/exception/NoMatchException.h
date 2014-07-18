/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_exception_NoMatchException_h_
#define _xmas_broker2g_exception_NoMatchException_h_

#include "xmas/broker2g/exception/Exception.h"


namespace xmas {
	namespace broker2g {
		namespace exception { 
			class NoMatchException: public xmas::broker2g::exception::Exception
			{
				public: 
				NoMatchException( std::string name, std::string message, std::string module, int line, std::string function ): 
					xmas::broker2g::exception::Exception(name, message, module, line, function) 
				{} 

				NoMatchException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xmas::broker2g::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
