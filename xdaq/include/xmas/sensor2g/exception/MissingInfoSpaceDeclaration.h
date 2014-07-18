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

#ifndef _xmas_sensor2g_exception_MissingInfoSpaceDeclaration_h_
#define _xmas_sensor2g_exception_MissingInfoSpaceDeclaration_h_

#include "xmas/sensor2g/exception/Exception.h"


namespace xmas {
	namespace sensor2g {
		namespace exception { 
			class MissingInfoSpaceDeclaration: public xmas::sensor2g::exception::Exception 
			{
				public: 
				MissingInfoSpaceDeclaration( std::string name, std::string message, std::string module, int line, std::string function ): 
					xmas::sensor2g::exception::Exception(name, message, module, line, function) 
				{} 

				MissingInfoSpaceDeclaration( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xmas::sensor2g::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
