// $Id: ReceiveError.h,v 1.2 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_exception_ReceiveError_h_
#define _pt_tcp_exception_ReceiveError_h_

#include "pt/tcp/exception/Exception.h"

namespace pt {
namespace tcp {
	namespace exception { 
		class ReceiveError: public pt::tcp::exception::Exception 
		{
			public: 
			ReceiveError ( std::string name, std::string message, std::string module, int line, std::string function ): 
					tcp::exception::Exception(name, message, module, line, function) 
			{} 
			
			ReceiveError ( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					tcp::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}
}
#endif
