// $Id: version.h,v 1.14 2009/04/06 13:44:55 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_version_h_
#define _sentinel_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define SENTINEL_VERSION_MAJOR 2
#define SENTINEL_VERSION_MINOR 0
#define SENTINEL_VERSION_PATCH 2
// If any previous versions available E.g. #define SENTINEL_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define SENTINEL_PREVIOUS_VERSIONS  "1.10.0,1.10.1,1.10.2,1.11.0,1.12.0,1.12.1,1.12.2,2.0.0,2.0.1"


//
// Template macros
//
#define SENTINEL_VERSION_CODE PACKAGE_VERSION_CODE(SENTINEL_VERSION_MAJOR,SENTINEL_VERSION_MINOR,SENTINEL_VERSION_PATCH)
#ifndef SENTINEL_PREVIOUS_VERSIONS
#define SENTINEL_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINEL_VERSION_MAJOR,SENTINEL_VERSION_MINOR,SENTINEL_VERSION_PATCH)
#else 
#define SENTINEL_FULL_VERSION_LIST  SENTINEL_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINEL_VERSION_MAJOR,SENTINEL_VERSION_MINOR,SENTINEL_VERSION_PATCH)
#endif 

namespace sentinel
{
	const std::string package  =  "sentinel";
	const std::string versions =  SENTINEL_FULL_VERSION_LIST;
	const std::string summary = "Sentinel distributed error handling package";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
