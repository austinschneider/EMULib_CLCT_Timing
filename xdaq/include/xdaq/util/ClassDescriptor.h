// $Id: ClassDescriptor.h,v 1.3 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ClassDescriptor_h_
#define _xdaq_util_ClassDescriptor_h_

#include <string>

namespace xdaq 
{

namespace util
{

	class ClassDescriptor
	{
		public:

		//! Create a new network  device with name.
		/*! A device is uniquely identified by its name, e.g. lxcmd112 */
                /*! E.g. of usage */
                /*! ClassDescriptor("FastIron 400/800/1500", "http://www.foundrynet.com/", "atcp,tcp,udp") */
		ClassDescriptor (const std::string & name, 
                                 const std::string & info ): name_(name), info_(info)
		{
                }
		


		//! Retrieve the name that uniquely identifies a host 
		std::string getName()
		{
			return name_;
		}
		
		//! Retrieve the info that describes the device 
		std::string getInfo()
		{
			return info_;
		}
                
                //! Add a required module for loading application
		void addModule(const std::string & module, size_t position = 0)
		{
                    // TBD insert  module at position
			if ( modules_.find(module) == modules_.end() ) 
			{
				modules_[module] = 0; // symbolic link to ModulesTable 
			}
			else
			{
				std::string msg = toolbox::toString("Module url %s already existing", module.c_str());
				XCEPT_RAISE(xdaq::exception::DuplicateModule, msg);
			}
		}
                
                 //! Remove the module from list 
                void removeModule(const std::string & module) throw (xdaq::exception::ModuleNotFound)
		{
			if (modules_.find(module) != modules_.end() ) 
			{
				modules_.erase(module);
			}
			else
			{
				std::string msg = toolbox::toString("No module for url % found",module.c_str());
				XCEPT_RAISE(xdaq::exception::ModuleNotFound, msg);
			}

		}

                
                //! Retrieve the supported communication protocols matching with XDAQ transports (tcp, udp, gm, maze etc. )
		vector<std::string> getModules()
		{
			std::vector<std::string> modules;

			std::map<std::string, size_t, std::less<std::string> >::iterator i;
			for ( i = modules_.begin(); i != modules_.end(); i++ )
			{
				modules.push_back((*i).first);
	
			}
			return modules;

		}



		private:

		std::string name_;
		std::string info_;
                std::map<std::string, size_t, std::less<std::string> > modules_;
	};
}	

}

#endif
