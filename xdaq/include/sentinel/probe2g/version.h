/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_probe2g_version_h_
#define _sentinel_probe2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define SENTINELPROBE2G_VERSION_MAJOR 1
#define SENTINELPROBE2G_VERSION_MINOR 0
#define SENTINELPROBE2G_VERSION_PATCH 0
// If any previous versions available E.g. #define SENTINELPROBE2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef SENTINELPROBE2G_PREVIOUS_VERSIONS


//
// Template macros
//
#define SENTINELPROBE2G_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELPROBE2G_VERSION_MAJOR,SENTINELPROBE2G_VERSION_MINOR,SENTINELPROBE2G_VERSION_PATCH)
#ifndef SENTINELPROBE2G_PREVIOUS_VERSIONS
#define SENTINELPROBE2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELPROBE2G_VERSION_MAJOR,SENTINELPROBE2G_VERSION_MINOR,SENTINELPROBE2G_VERSION_PATCH)
#else 
#define SENTINELPROBE2G_FULL_VERSION_LIST  SENTINELPROBE2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELPROBE2G_VERSION_MAJOR,SENTINELPROBE2G_VERSION_MINOR,SENTINELPROBE2G_VERSION_PATCH)
#endif 

namespace sentinelprobe2g
{
	const std::string package  =  "sentinelprobe2g";
	const std::string versions =  SENTINELPROBE2G_FULL_VERSION_LIST;
	const std::string summary = "Sentinel distributed error handling package";
	const std::string description = "";
	const std::string authors = "Roland Moser, Luciano Orsini";
	const std::string link = "http://xdaq.web.cern.ch/";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

