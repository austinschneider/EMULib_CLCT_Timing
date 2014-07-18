// $Id: HTTPException.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_exception_HTTPException_h_
#define _xoap_exception_HTTPException_h_

#include "xoap/exception/Exception.h"

namespace xoap {
	namespace exception { 
		class HTTPException: public xoap::exception::Exception 
		{
			public: 
			HTTPException ( std::string name, std::string message, std::string module, int line, std::string function ): 
					xoap::exception::Exception(name, message, module, line, function) 
			{} 
			HTTPException ( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					xoap::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
