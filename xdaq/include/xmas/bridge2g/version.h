/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_bridge2g_version_h_
#define _xmas_bridge2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASBRIDGE2G_VERSION_MAJOR 1
#define XMASBRIDGE2G_VERSION_MINOR 1
#define XMASBRIDGE2G_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASBRIDGE2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASBRIDGE2G_PREVIOUS_VERSIONS "1.0.0,1.0.1"


//
// Template macros
//
#define XMASBRIDGE2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASBRIDGE2G_VERSION_MAJOR,XMASBRIDGE2G_VERSION_MINOR,XMASBRIDGE2G_VERSION_PATCH)
#ifndef XMASBRIDGE2G_PREVIOUS_VERSIONS
#define XMASBRIDGE2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASBRIDGE2G_VERSION_MAJOR,XMASBRIDGE2G_VERSION_MINOR,XMASBRIDGE2G_VERSION_PATCH)
#else 
#define XMASBRIDGE2G_FULL_VERSION_LIST  XMASBRIDGE2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASBRIDGE2G_VERSION_MAJOR,XMASBRIDGE2G_VERSION_MINOR,XMASBRIDGE2G_VERSION_PATCH)
#endif 

namespace xmasbridge2g
{
	const std::string package  =  "xmasbridge2g";
	const std::string versions =  XMASBRIDGE2G_FULL_VERSION_LIST;
	const std::string summary = "Monitoring bridge from SOAP to B2IN";
	const std::string description = "";
	const std::string authors = "Roland Moser, Luciano Orsini";
	const std::string link = "http://xdaq.web.cern.ch/";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

