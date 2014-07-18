// $Id: version.h,v 1.13 2009/04/27 13:26:05 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight_version_h_
#define _sentinel_spotlight_version_h_

#include "config/PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!

#define SENTINELSPOTLIGHT_VERSION_MAJOR 4
#define SENTINELSPOTLIGHT_VERSION_MINOR 1
#define SENTINELSPOTLIGHT_VERSION_PATCH 0
// If any previous versions available E.g. #define SENTINELSPOTLIGHT_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define SENTINELSPOTLIGHT_PREVIOUS_VERSIONS "4.0.0,4.0.1,4.0.2,4.0.3,4.0.4"


//
// Template macros
//
#define SENTINELSPOTLIGHT_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELSPOTLIGHT_VERSION_MAJOR,SENTINELSPOTLIGHT_VERSION_MINOR,SENTINELSPOTLIGHT_VERSION_PATCH)
#ifndef SENTINELSPOTLIGHT_PREVIOUS_VERSIONS
#define SENTINELSPOTLIGHT_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELSPOTLIGHT_VERSION_MAJOR,SENTINELSPOTLIGHT_VERSION_MINOR,SENTINELSPOTLIGHT_VERSION_PATCH)
#else 
#define SENTINELSPOTLIGHT_FULL_VERSION_LIST  SENTINELSPOTLIGHT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELSPOTLIGHT_VERSION_MAJOR,SENTINELSPOTLIGHT_VERSION_MINOR,SENTINELSPOTLIGHT_VERSION_PATCH)
#endif 

namespace sentinelspotlight
{
	const std::string package  =  "sentinelspotlight";
	const std::string versions =  SENTINELSPOTLIGHT_FULL_VERSION_LIST;
	const std::string summary = "Server for exceptions and alarms";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
