// $Id: FailedSerialization.h,v 1.1 2008/08/27 15:30:58 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_exception_FailedSerialization_h_
#define _xmas_collector2g_exception_FailedSerialization_h_

#include "xmas/collector2g/exception/Exception.h"


namespace xmas {
	namespace collector2g {
		namespace exception { 
			class FailedSerialization: public xmas::collector2g::exception::Exception 
			{
				public: 
				FailedSerialization( std::string name, std::string message, std::string module, int line, std::string function ): 
					xmas::collector2g::exception::Exception(name, message, module, line, function) 
				{} 

				FailedSerialization( std::string name, std::string message, std::string module, int line, std::string function,
					xcept::Exception& e ): 
					xmas::collector2g::exception::Exception(name, message, module, line, function, e) 
				{} 

			};  
		}
	}		
}

#endif
