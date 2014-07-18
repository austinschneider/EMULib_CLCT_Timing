// $Id: version.h,v 1.10 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_version_h_
#define _ws_eventing_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSEVENTING_VERSION_MAJOR 1
#define WSEVENTING_VERSION_MINOR 14
#define WSEVENTING_VERSION_PATCH 1
// If any previous versions available E.g. #define WSEVENTING_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define WSEVENTING_PREVIOUS_VERSIONS "1.14.0"


//
// Template macros
//
#define WSEVENTING_VERSION_CODE PACKAGE_VERSION_CODE(WSEVENTING_VERSION_MAJOR,WSEVENTING_VERSION_MINOR,WSEVENTING_VERSION_PATCH)
#ifndef WSEVENTING_PREVIOUS_VERSIONS
#define WSEVENTING_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSEVENTING_VERSION_MAJOR,WSEVENTING_VERSION_MINOR,WSEVENTING_VERSION_PATCH)
#else 
#define WSEVENTING_FULL_VERSION_LIST  WSEVENTING_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSEVENTING_VERSION_MAJOR,WSEVENTING_VERSION_MINOR,WSEVENTING_VERSION_PATCH)
#endif 
namespace wseventing
{
	const std::string package  =  "wseventing";
	const std::string versions =  WSEVENTING_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "WS-Eventing package";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
