/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_version_h_
#define _ws_broker_utils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSBROKERUTILS_VERSION_MAJOR 1
#define WSBROKERUTILS_VERSION_MINOR 1 
#define WSBROKERUTILS_VERSION_PATCH 0
// If any previous versions available E.g. #define WSBROKERUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef WSBROKERUTILS_PREVIOUS_VERSIONS


//
// Template macros
//
#define WSBROKERUTILS_VERSION_CODE PACKAGE_VERSION_CODE(WSBROKERUTILS_VERSION_MAJOR,WSBROKERUTILS_VERSION_MINOR,WSBROKERUTILS_VERSION_PATCH)
#ifndef WSBROKERUTILS_PREVIOUS_VERSIONS
#define WSBROKERUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSBROKERUTILS_VERSION_MAJOR,WSBROKERUTILS_VERSION_MINOR,WSBROKERUTILS_VERSION_PATCH)
#else 
#define WSBROKERUTILS_FULL_VERSION_LIST  WSBROKERUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSBROKERUTILS_VERSION_MAJOR,WSBROKERUTILS_VERSION_MINOR,WSBROKERUTILS_VERSION_PATCH)
#endif 

namespace wsbrokerutils
{
	const std::string package  =  "wsbrokerutils";
	const std::string versions =  WSBROKERUTILS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Roland Moser";
	const std::string summary = "ws broker utils package for writing models and accessing the ws broker service";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
