// $Id: ModelNotFoundException.h,v 1.1 2008/06/20 09:28:07 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_exception_ModelNotFoundException_h_
#define _ws_broker_exception_ModelNotFoundException_h_

#include "xcept/Exception.h"


namespace xmas {
	namespace broker2g {
		namespace exception { 
			class ModelNotFoundException: public xcept::Exception
			{
				public: 
				ModelNotFoundException( std::string name, std::string message, std::string module, int line, std::string function ): 
					xcept::Exception(name, message, module, line, function) 
				{} 

				ModelNotFoundException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xcept::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
