// $Id: version.h,v 1.24 2008/07/18 15:27:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_version_h_
#define _ws_service_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSSERVICE_VERSION_MAJOR 1
#define WSSERVICE_VERSION_MINOR 15
#define WSSERVICE_VERSION_PATCH 1
// If any previous versions available E.g. #define WSSERVICE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define WSSERVICE_PREVIOUS_VERSIONS "1.14.0,1.14.1,1.14.2,1.14.3,1.15.0"


//
// Template macros
//
#define WSSERVICE_VERSION_CODE PACKAGE_VERSION_CODE(WSSERVICE_VERSION_MAJOR,WSSERVICE_VERSION_MINOR,WSSERVICE_VERSION_PATCH)
#ifndef WSSERVICE_PREVIOUS_VERSIONS
#define WSSERVICE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSSERVICE_VERSION_MAJOR,WSSERVICE_VERSION_MINOR,WSSERVICE_VERSION_PATCH)
#else 
#define WSSERVICE_FULL_VERSION_LIST  WSSERVICE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSSERVICE_VERSION_MAJOR,WSSERVICE_VERSION_MINOR,WSSERVICE_VERSION_PATCH)
#endif 

namespace wsserviceeventing
{
	const std::string package  =  "wsservice";
	const std::string versions =  WSSERVICE_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "WS-Eventing service application";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
