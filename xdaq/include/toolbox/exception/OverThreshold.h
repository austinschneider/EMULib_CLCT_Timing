// $Id: OverThreshold.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_exception_OverThreshold_h_
#define _toolbox_exception_OverThreshold_h_

#include "toolbox/exception/Exception.h"

namespace toolbox {
	namespace exception { 
		class OverThreshold: public toolbox::exception::Exception 
		{
			public: 
			OverThreshold( std::string name, std::string message, std::string module, int line, std::string function ): 
					toolbox::exception::Exception(name, message, module, line, function) 
			{} 
			
			OverThreshold( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					toolbox::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
