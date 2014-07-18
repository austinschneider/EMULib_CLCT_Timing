//$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_exception_UnresolvedAddress_h_
#define _toolbox_net_exception_UnresolvedAddress_h_

#include "toolbox/net/exception/Exception.h"

namespace toolbox {
namespace net {
	namespace exception { 
		class UnresolvedAddress: public toolbox::net::exception::Exception 
		{
			public: 
			UnresolvedAddress( std::string name, std::string message, std::string module, int line, std::string function ): 
					toolbox::net::exception::Exception(name, message, module, line, function) 
			{} 
			
			UnresolvedAddress( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					toolbox::net::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}
}

#endif
