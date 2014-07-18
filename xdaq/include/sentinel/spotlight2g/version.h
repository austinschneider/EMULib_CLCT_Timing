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

#ifndef _sentinel_spotlight2g_version_h_
#define _sentinel_spotlight2g_version_h_

#include "config/PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!

#define SENTINELSPOTLIGHT2G_VERSION_MAJOR 1
#define SENTINELSPOTLIGHT2G_VERSION_MINOR 4
#define SENTINELSPOTLIGHT2G_VERSION_PATCH 0
// If any previous versions available E.g. #define SENTINELSPOTLIGHT2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define SENTINELSPOTLIGHT2G_PREVIOUS_VERSIONS "1.0.0,1.0.1,1.0.2,1.1.0,1.2.0,1.2.1,1.3.0,1.3.1,1.3.2"


//
// Template macros
//
#define SENTINELSPOTLIGHT2G_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELSPOTLIGHT2G_VERSION_MAJOR,SENTINELSPOTLIGHT2G_VERSION_MINOR,SENTINELSPOTLIGHT2G_VERSION_PATCH)
#ifndef SENTINELSPOTLIGHT2G_PREVIOUS_VERSIONS
#define SENTINELSPOTLIGHT2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELSPOTLIGHT2G_VERSION_MAJOR,SENTINELSPOTLIGHT2G_VERSION_MINOR,SENTINELSPOTLIGHT2G_VERSION_PATCH)
#else 
#define SENTINELSPOTLIGHT2G_FULL_VERSION_LIST  SENTINELSPOTLIGHT2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELSPOTLIGHT2G_VERSION_MAJOR,SENTINELSPOTLIGHT2G_VERSION_MINOR,SENTINELSPOTLIGHT2G_VERSION_PATCH)
#endif 

namespace sentinelspotlight2g
{
	const std::string package  =  "sentinelspotlight2g";
	const std::string versions =  SENTINELSPOTLIGHT2G_FULL_VERSION_LIST;
	const std::string summary = "Server for exceptions and alarms";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
