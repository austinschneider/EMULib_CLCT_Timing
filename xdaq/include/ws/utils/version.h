// $Id: version.h,v 1.7 2008/07/18 15:27:54 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_utils_version_h_
#define _ws_utils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSUTILS_VERSION_MAJOR 1
#define WSUTILS_VERSION_MINOR 3
#define WSUTILS_VERSION_PATCH 0
// If any previous versions available E.g. #define WSUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef WSUTILS_PREVIOUS_VERSIONS


//
// Template macros
//
#define WSUTILS_VERSION_CODE PACKAGE_VERSION_CODE(WSUTILS_VERSION_MAJOR,WSUTILS_VERSION_MINOR,WSUTILS_VERSION_PATCH)
#ifndef WSUTILS_PREVIOUS_VERSIONS
#define WSUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSUTILS_VERSION_MAJOR,WSUTILS_VERSION_MINOR,WSUTILS_VERSION_PATCH)
#else 
#define WSUTILS_FULL_VERSION_LIST  WSUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSUTILS_VERSION_MAJOR,WSUTILS_VERSION_MINOR,WSUTILS_VERSION_PATCH)
#endif 

namespace wsutils
{
	const std::string package  =  "wsutils";
	const std::string versions =  WSUTILS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "WS eventing utilities library";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
