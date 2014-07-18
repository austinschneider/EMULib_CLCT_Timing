// $Id: ParameterSetFailed.h,v 1.4 2008/07/18 15:28:03 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_exception_ParameterSetFailed_h_
#define _xdaq_exception_ParameterSetFailed_h_

#include "xdaq/exception/Exception.h"

namespace xdaq {
	namespace exception { 
		class ParameterSetFailed: public xdaq::exception::Exception 
		{
			public: 
			ParameterSetFailed( std::string name, std::string message, std::string module, int line, std::string function ): 
					xdaq::exception::Exception(name, message, module, line, function) 
			{} 
			ParameterSetFailed( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					xdaq::exception::Exception(name, message, module, line, function, e) 
			{} 
			
			
			
			
			
		}; 
	} 
}

#endif
