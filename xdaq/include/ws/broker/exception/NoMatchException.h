/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_exception_NoMatchException_h_
#define _ws_broker_exception_NoMatchException_h_

#include "ws/broker/exception/Exception.h"


namespace ws {
	namespace broker {
		namespace exception { 
			class NoMatchException: public ws::broker::exception::Exception
			{
				public: 
				NoMatchException( std::string name, std::string message, std::string module, int line, std::string function ): 
					ws::broker::exception::Exception(name, message, module, line, function) 
				{} 

				NoMatchException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					ws::broker::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
