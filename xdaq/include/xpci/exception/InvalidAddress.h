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

#ifndef _xpci_exception_InvalidAddress_h_
#define _xpci_exception_InvalidAddress_h_

#include "xpci/exception/Exception.h"

namespace xpci {
	namespace exception { 
		class InvalidAddress: public xpci::exception::Exception 
		{
			public: 
			InvalidAddress( std::string name, std::string message, std::string module, int line, std::string function ): 
					xpci::exception::Exception(name, message, module, line, function) 
			{} 
			InvalidAddress( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					xpci::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
