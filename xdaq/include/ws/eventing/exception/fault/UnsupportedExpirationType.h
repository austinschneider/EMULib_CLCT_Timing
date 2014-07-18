// $Id: UnsupportedExpirationType.h,v 1.3 2008/07/18 15:27:51 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_exception_fault_UnsupportedExpirationType_h_
#define _ws_eventing_exception_fault_UnsupportedExpirationType_h_

#include "ws/eventing/exception/Exception.h"


namespace ws {
	namespace eventing {
		namespace exception { 
			namespace fault { 
				class UnsupportedExpirationType: public ws::eventing::exception::Exception 
				{
					public: 
					UnsupportedExpirationType( std::string name, std::string message, std::string module, int line, std::string function ): 
						ws::eventing::exception::Exception(name, message, module, line, function) 
					{} 

					UnsupportedExpirationType( std::string name, std::string message, std::string module, int line, std::string function,
						xcept::Exception& e ): 
						ws::eventing::exception::Exception(name, message, module, line, function, e) 
					{} 

				}; 
			}
		} 
	}	
}

#endif
