/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_version_h_
#define _xmas_broker2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASBROKER2G_VERSION_MAJOR 2
#define XMASBROKER2G_VERSION_MINOR 3
#define XMASBROKER2G_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASBROKER2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XMASBROKER2G_PREVIOUS_VERSIONS


//
// Template macros
//
#define XMASBROKER2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASBROKER2G_VERSION_MAJOR,XMASBROKER2G_VERSION_MINOR,XMASBROKER2G_VERSION_PATCH)
#ifndef XMASBROKER2G_PREVIOUS_VERSIONS
#define XMASBROKER2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASBROKER2G_VERSION_MAJOR,XMASBROKER2G_VERSION_MINOR,XMASBROKER2G_VERSION_PATCH)
#else 
#define XMASBROKER2G_FULL_VERSION_LIST  XMASBROKER2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASBROKER2G_VERSION_MAJOR,XMASBROKER2G_VERSION_MINOR,XMASBROKER2G_VERSION_PATCH)
#endif 

namespace xmasbroker2g
{
	const std::string package  =  "xmasbroker2g";
	const std::string versions =  XMASBROKER2G_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini, Roland Moser";
	const std::string summary = "A load balancer for b2in eventing";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
