// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: L. Orsiniand A. Petrucci					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xpci_exception_Exception_h_
#define _xpci_exception_Exception_h_

#include "xcept/Exception.h"

namespace xpci {
	namespace exception { 
		class Exception: public xcept::Exception 
		{
			public: 
			Exception( std::string name, std::string message, std::string module, int line, std::string function ): 
					xcept::Exception(name, message, module, line, function) 
			{} 
			Exception( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					xcept::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
