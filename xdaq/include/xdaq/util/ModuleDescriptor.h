// $Id: ModuleDescriptor.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ModuleDescriptor_h_
#define _xdaq_util_ModuleDescriptor_h_

#include <string>

namespace xdaq 
{

namespace util
{

	class ModuleDescriptor
	{
		public:

		//! Create a new module with url.
		/*! A module is uniquely identified by its url, e.g. file:/lxcmd112/libmylib.so */
		ModuleDescriptor (const std::string  & url,
                                  const std::string  & type, 
                                  const std::string  & platform,
                                  const std::string  & arch   ): url_(url), 
				  type_(type), platform_(platform),  arch_(arch)
		{
		}
		


		//! Retrieve the url that uniquely identifies a module 
		std::string getURL()
		{
			return url_;
		}
		
		//! Retrieve the type of the module ( e.g. shared object) 
		std::string getType()
		{
			return type_;
		}
                
                //! Retrieve the platform required ( e.g. linux, macosx, solaris) 
		std::string getPlatform()
		{
			return platform_;
		}
                
                //! Retrieve the architecture required ( e.g. x86, sparc, ppc) 
		std::string getArch()
		{
			return arch_;
		}

		private:

		std::string url_;
		std::string type_;
                std::string platform_;
		std::string arch_;
	};
}	

}

#endif
