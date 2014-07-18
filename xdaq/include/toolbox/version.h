// $Id: version.h,v 1.30 2009/05/12 13:33:51 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/


#ifndef _toolbox_version_h_
#define _toolbox_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TOOLBOX_VERSION_MAJOR 5
#define TOOLBOX_VERSION_MINOR 2
#define TOOLBOX_VERSION_PATCH 2
// If any previous versions available E.g. #define TOOLBOX_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TOOLBOX_PREVIOUS_VERSIONS

//
// Template macros
//
#define TOOLBOX_VERSION_CODE PACKAGE_VERSION_CODE(TOOLBOX_VERSION_MAJOR,TOOLBOX_VERSION_MINOR,TOOLBOX_VERSION_PATCH)
#ifndef TOOLBOX_PREVIOUS_VERSIONS
#define TOOLBOX_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TOOLBOX_VERSION_MAJOR,TOOLBOX_VERSION_MINOR,TOOLBOX_VERSION_PATCH)
#else 
#define TOOLBOX_FULL_VERSION_LIST  TOOLBOX_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TOOLBOX_VERSION_MAJOR,TOOLBOX_VERSION_MINOR,TOOLBOX_VERSION_PATCH)
#endif 

namespace toolbox 
{
	const std::string package  =  "toolbox";
    	const std::string versions = TOOLBOX_FULL_VERSION_LIST;
	const std::string summary = "System and basic programming support classes";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Core_Tools";

    	config::PackageInfo getPackageInfo();
    	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
    	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
