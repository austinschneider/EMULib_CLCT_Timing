// $Id: CannotConnect.h,v 1.1 2007/03/31 14:23:57 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_atcp_exception_CannotConnect_h_
#define _pt_atcp_exception_CannotConnect_h_

#include "pt/atcp/exception/Exception.h"

namespace pt {
namespace atcp {
	namespace exception { 
		class CannotConnect: public pt::atcp::exception::Exception 
		{
			public: 
			CannotConnect ( std::string name, std::string message, std::string module, int line, std::string function ): 
					pt::atcp::exception::Exception(name, message, module, line, function) 
			{} 
			
			CannotConnect ( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					pt::atcp::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

}
#endif
