/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_version_h_
#define _ws_broker_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSBROKER_VERSION_MAJOR 1
#define WSBROKER_VERSION_MINOR 0 
#define WSBROKER_VERSION_PATCH 4
// If any previous versions available E.g. #define WSBROKER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define WSBROKER_PREVIOUS_VERSIONS "1.0.0,1.0.1,1.0.2,1.0.3"


//
// Template macros
//
#define WSBROKER_VERSION_CODE PACKAGE_VERSION_CODE(WSBROKER_VERSION_MAJOR,WSBROKER_VERSION_MINOR,WSBROKER_VERSION_PATCH)
#ifndef WSBROKER_PREVIOUS_VERSIONS
#define WSBROKER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSBROKER_VERSION_MAJOR,WSBROKER_VERSION_MINOR,WSBROKER_VERSION_PATCH)
#else 
#define WSBROKER_FULL_VERSION_LIST  WSBROKER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSBROKER_VERSION_MAJOR,WSBROKER_VERSION_MINOR,WSBROKER_VERSION_PATCH)
#endif 

namespace wsbroker
{
	const std::string package  =  "wsbroker";
	const std::string versions =  WSBROKER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini, Roland Moser";
	const std::string summary = "A load balancer for ws eventing";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
