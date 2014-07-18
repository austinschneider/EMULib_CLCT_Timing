// $Id: JobCrash.h,v 1.2 2008/07/18 15:26:54 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _jobcontrol_exception_JobCrash_h_
#define _jobcontrol_exception_JobCrash_h_

#include "jobcontrol/exception/Exception.h"

namespace jobcontrol {
	namespace exception { 
		class JobCrash: public jobcontrol::exception::Exception 
		{
			public: 
			JobCrash( std::string name, std::string message, std::string module, int line, std::string function ): 
					jobcontrol::exception::Exception(name, message, module, line, function) 
			{} 
			JobCrash( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception & e ): 
					jobcontrol::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
