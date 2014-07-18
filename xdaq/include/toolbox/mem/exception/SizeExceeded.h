// $Id: SizeExceeded.h,v 1.4 2008/07/18 15:27:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_exception_SizeExceeded_h
#define _toolbox_mem_exception_SizeExceeded_h

#include "toolbox/mem/exception/Exception.h"

namespace toolbox {
namespace mem {
	namespace exception { 
		class SizeExceeded: public toolbox::mem::exception::Exception 
		{
			public: 
			SizeExceeded( std::string name, std::string message, std::string module, int line, std::string function ): 
					toolbox::mem::exception::Exception(name, message, module, line, function) 
			{} 
			
			SizeExceeded( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					toolbox::mem::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}
}

#endif
