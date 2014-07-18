// $Id: SharedObjectRegistry.h,v 1.8 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_SharedObjectRegistry_h_
#define _xdaq_SharedObjectRegistry_h_

#include <vector>
#include <map>
#include <string>

#include <dlfcn.h>
#include "config/PackageInfo.h"

#include "xdaq/exception/LoadFailed.h"
#include "xdaq/exception/UnloadFailed.h"
#include "xdaq/exception/SymbolLookupFailed.h"


//#define LD_LAZY  RTLD_LAZY
//#define LD_EAGER RTLD_NOW

#if defined(linux)
#define LIBRARY_PATH_VARIABLE "LD_LIBRARY_PATH"
#endif

#if defined(macosx)
#define LIBRARY_PATH_VARIABLE "DYLD_LIBRARY_PATH"
#endif

namespace xdaq 
{

class SharedObjectRegistry
{
	protected:
		typedef void* (*symbolVFPtrT)();

	public:
		SharedObjectRegistry();
		
		~SharedObjectRegistry();
		
		//! Perform a package dependency check on a loaded module. Modules are identified by their pathname in the file system
		//
		void checkdependency(const std::string & pathname) 
			throw (xdaq::exception::SymbolLookupFailed, config::PackageInfo::VersionException);
		
		//! Retrieve a PackageInfo class for a loaded module. Modules are identified by their pathname in the file system
		//
		config::PackageInfo getPackageInfo (const std::string & pathname) 
			throw (xdaq::exception::SymbolLookupFailed, config::PackageInfo::VersionException);
		
		//! Returns file handle for a module to be loaded from the file system
		void load (const std::string & pathname) 
			throw (xdaq::exception::LoadFailed);
		
		//! Load a module from the filesystem and check its dependencies on other modules if \param checkDependencies is true
		//
		void load (const std::string & pathname, bool checkDependencies) 
			throw (xdaq::exception::LoadFailed, xdaq::exception::SymbolLookupFailed, config::PackageInfo::VersionException);
		
		//! Remove a loded package from the memory. Modules are identified by their pathname in the file system
		//
		void unload(const std::string & pathname) 
			throw (xdaq::exception::UnloadFailed);
		
		//! Look up a function symbol in all loaded packages
		//
		void* lookup (const std::string & name) 
			throw (xdaq::exception::SymbolLookupFailed);
			
		//! Retrieve a list of all loaded objects
		std::vector<std::string> getObjectNames();
			
	protected:
	
	// remember file handles (void*) by filename 
	std::map <std::string, void*, std::less<std::string> > sharedObjects_;
};


}

#endif
