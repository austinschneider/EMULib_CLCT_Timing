// $Id: DuplicateEndpoint.h,v 1.5 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_exception_DuplicateEndpoint_h_
#define _pt_exception_DuplicateEndpoint_h_

#include "pt/exception/Exception.h"

namespace pt {
	namespace exception { 
		class DuplicateEndpoint: public pt::exception::Exception 
		{
			public: 
			DuplicateEndpoint( std::string name, std::string message, std::string module, int line, std::string function ): 
					p::exception::Exception(name, message, module, line, function) 
			{} 
			
			DuplicateEndpoint( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					p::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
