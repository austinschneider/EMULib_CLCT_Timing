// $Id: ParserException.h,v 1.2 2008/07/18 15:28:16 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_broker_exception_ParserException_h_
#define _ws_broker_exception_ParserException_h_

#include "xcept/Exception.h"


namespace xmas {
	namespace broker2g {
		namespace exception { 
			class ParserException: public xcept::Exception
			{
				public: 
				ParserException( std::string name, std::string message, std::string module, int line, std::string function ): 
					xcept::Exception(name, message, module, line, function) 
				{} 

				ParserException( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xcept::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
