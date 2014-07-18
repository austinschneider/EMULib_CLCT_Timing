// $Id: ModulesTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ModulesTable_h_
#define _xdaq_util_ModulesTable_h_

#include <string>
#include <map>


#include "xdaq/exception/ModuleNotFound.h"
#include "xdaq/exception/DuplicateModule.h"

#include "xdaq/util/ModuleDescriptor.h"


namespace xdaq {

namespace util {

class ModulesTable
{
	public:
	
	// DTOR
	~ModulesTable()
	{
		std::map<std::string, xdaq::util::ModuleDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  modules_.begin(); i != modules_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new module located at url.
	/*! A modules is uniquely identified by its url e.g. file:/usr/lib/libmylib.so  */
	xdaq::util::ModuleDescriptor* createModuleDescriptor (const std::string & url,
                                                            const std::string  & type, 
                                                            const std::string  & os,
                                                            const std::string  & arch ) throw  (xdaq::exception::DuplicateModule )
	{
                
		if ( modules_.find(url) == modules_.end() ) 
		{
			modules_[url] = new xdaq::util::ModuleDescriptor(url,type,os,arch);
			return modules_[url];
		}
		else
		{
			std::string msg = toolbox::toString("Module url %s already existing", url.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateHost, msg);
		}	
	}
	
	//! Remove a module descriptor by name 
 	void removeModule(const std::string & url) throw (xdaq::exception::HostNotFound)
	{
		if ( modules_.find(url) != modules_.end() ) 
		{
			xdaq::util::ModuleDescriptor* d = modules_[url];
			delete d;
			modules_.erase(url);
		}
		else
		{
			std::string msg = toolbox::toString("No descriptor for url % found",url.c_str());
			XCEPT_RAISE(xdaq::exception::ModuleNotFound, msg);
		}
	}
	
	//! Retrieve a host by indicating the name 
 	xdaq::util::ModuleDescriptor*  getModuletDescriptor(const std::string & url) 
		throw (xdaq::exception::ModuleNotFound)
	{
		if ( modules_.find(url) != modules_.end() ) 
		{
			return modules_[url];

		}
		else
		{
			std::string msg = toolbox::toString("No descritptor for url % found",url.c_str());
			XCEPT_RAISE(xdaq::exception::HostNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::ModuleDescriptor*>   getModuleDescriptors() 
	{
		std::vector<xdaq::util::ModuleDescriptor*> modules;

		std::map<std::string, xdaq::util::ModuleDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  modules_.begin(); i != modules_.end(); i++ )
		{
			modules.push_back((*i).second);

		}
		return modules;

	}
	
	private:
	
	std::map<std::string, xdaq::util::ModuleDescriptor*, std::less<std::string> > modules_;
	
};
}
}

#endif
