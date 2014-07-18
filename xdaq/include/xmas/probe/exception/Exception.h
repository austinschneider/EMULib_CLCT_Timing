// $Id: Exception.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_exception_Exception_h_
#define _xmas_probe_exception_Exception_h_

#include "xmas/exception/Exception.h"


namespace xmas {
	namespace probe {
		namespace exception { 
			class Exception: public xmas::exception::Exception 
			{
				public: 
				Exception( std::string name, std::string message, std::string module, int line, std::string function ): 
					xmas::exception::Exception(name, message, module, line, function) 
				{} 

				Exception( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xmas::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
