// $Id: version.h,v 1.6 2008/07/18 15:28:46 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xploreutils_version_h_
#define _xploreutils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XPLOREUTILS_VERSION_MAJOR 1
#define XPLOREUTILS_VERSION_MINOR 10
#define XPLOREUTILS_VERSION_PATCH 1
// If any previous versions available E.g. #define XPLOREUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XPLOREUTILS_PREVIOUS_VERSIONS "1.10.0"


//
// Template macros
//
#define XPLOREUTILS_VERSION_CODE PACKAGE_VERSION_CODE(XPLOREUTILS_VERSION_MAJOR,XPLOREUTILS_VERSION_MINOR,XPLOREUTILS_VERSION_PATCH)
#ifndef XPLOREUTILS_PREVIOUS_VERSIONS
#define XPLOREUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XPLOREUTILS_VERSION_MAJOR,XPLOREUTILS_VERSION_MINOR,XPLOREUTILS_VERSION_PATCH)
#else 
#define XPLOREUTILS_FULL_VERSION_LIST  XPLOREUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XPLOREUTILS_VERSION_MAJOR,XPLOREUTILS_VERSION_MINOR,XPLOREUTILS_VERSION_PATCH)
#endif 

namespace xploreutils
{
	const std::string package  =  "xploreutils";
   	const std::string versions =  XPLOREUTILS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "Xplore support interfaces";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/I2O_Messaging";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
