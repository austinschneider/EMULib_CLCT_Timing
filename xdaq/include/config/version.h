// $Id: version.h,v 1.6 2008/07/18 15:26:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _config_version_h_
#define _config_version_h_

#include "PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!

#define CONFIG_VERSION_MAJOR 3
#define CONFIG_VERSION_MINOR 9
#define CONFIG_VERSION_PATCH 2
// If any previous versions available E.g. #define CONFIG_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define CONFIG_PREVIOUS_VERSIONS  "3.9.0,3.9.2"


//
// Template macros
//
#define CONFIG_VERSION_CODE PACKAGE_VERSION_CODE(CONFIG_VERSION_MAJOR,CONFIG_VERSION_MINOR,CONFIG_VERSION_PATCH)
#ifndef CONFIG_PREVIOUS_VERSIONS
#define CONFIG_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(CONFIG_VERSION_MAJOR,CONFIG_VERSION_MINOR,CONFIG_VERSION_PATCH)
#else 
#define CONFIG_FULL_VERSION_LIST  CONFIG_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(CONFIG_VERSION_MAJOR,CONFIG_VERSION_MINOR,CONFIG_VERSION_PATCH)
#endif 

namespace config 
{
	const std::string package  =  "config";
	// !!! Edit this line to reflect the latest package version and previous compatible versions !!!
   	const std::string versions = CONFIG_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "Package versioning and checking module";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
