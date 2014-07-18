/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_bridge2g_version_h_
#define _sentinel_bridge2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define SENTINELBRIDGE2G_VERSION_MAJOR 1
#define SENTINELBRIDGE2G_VERSION_MINOR 0
#define SENTINELBRIDGE2G_VERSION_PATCH 0
// If any previous versions available E.g. #define SENTINELBRIDGE2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef SENTINELBRIDGE2G_PREVIOUS_VERSIONS


//
// Template macros
//
#define SENTINELBRIDGE2G_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELBRIDGE2G_VERSION_MAJOR,SENTINELBRIDGE2G_VERSION_MINOR,SENTINELBRIDGE2G_VERSION_PATCH)
#ifndef SENTINELBRIDGE2G_PREVIOUS_VERSIONS
#define SENTINELBRIDGE2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELBRIDGE2G_VERSION_MAJOR,SENTINELBRIDGE2G_VERSION_MINOR,SENTINELBRIDGE2G_VERSION_PATCH)
#else 
#define SENTINELBRIDGE2G_FULL_VERSION_LIST  SENTINELBRIDGE2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELBRIDGE2G_VERSION_MAJOR,SENTINELBRIDGE2G_VERSION_MINOR,SENTINELBRIDGE2G_VERSION_PATCH)
#endif 

namespace sentinelbridge2g
{
	const std::string package  =  "sentinelbridge2g";
	const std::string versions =  SENTINELBRIDGE2G_FULL_VERSION_LIST;
	const std::string summary = "Sentinel bridge from SOAP to B2IN";
	const std::string description = "";
	const std::string authors = "Roland Moser, Luciano Orsini";
	const std::string link = "http://xdaq.web.cern.ch/";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

