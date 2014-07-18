// $Id: MissingInfoSpaceDeclaration.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_exception_MissingInfoSpaceDeclaration_h_
#define _xmas_probe_exception_MissingInfoSpaceDeclaration_h_

#include "xmas/probe/exception/Exception.h"


namespace xmas {
	namespace probe {
		namespace exception { 
			class MissingInfoSpaceDeclaration: public xmas::probe::exception::Exception 
			{
				public: 
				MissingInfoSpaceDeclaration( std::string name, std::string message, std::string module, int line, std::string function ): 
					xmas::probe::exception::Exception(name, message, module, line, function) 
				{} 

				MissingInfoSpaceDeclaration( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xmas::probe::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
