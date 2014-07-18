// $Id: ProfileNotFoundException.h,v 1.1 2008/03/14 10:25:34 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_exception_ProfileNotFoundException_h_
#define _ws_broker_utils_exception_ProfileNotFoundException_h_

#include "xcept/Exception.h"


namespace ws {
	namespace broker {
	namespace utils {
		namespace exception { 
			class ProfileNotFoundException: public xcept::Exception
			{
				public: 
				ProfileNotFoundException( std::string name, std::string message, std::string module, int line, std::string function ): 
					xcept::Exception(name, message, module, line, function) 
				{} 

				ProfileNotFoundException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xcept::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}
	}		
}

#endif
