// $Id: MalformedURN.h,v 1.3 2008/07/18 15:27:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_exception_MalformedURN_h_
#define _toolbox_net_exception_MalformedURN_h_

#include "toolbox/net/exception/Exception.h"

namespace toolbox {
namespace net {
	namespace exception { 
		class MalformedURN: public toolbox::net::exception::Exception 
		{
			public: 
			MalformedURN( std::string name, std::string message, std::string module, int line, std::string function ): 
					toolbox::net::exception::Exception(name, message, module, line, function) 
			{} 
			
			MalformedURN( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					toolbox::net::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}
}

#endif
