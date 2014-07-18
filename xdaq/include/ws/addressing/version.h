// $Id: version.h,v 1.7 2008/07/18 15:27:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_addressing_version_h_
#define _ws_addressing_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSADDRESSING_VERSION_MAJOR 1
#define WSADDRESSING_VERSION_MINOR 10
#define WSADDRESSING_VERSION_PATCH 1
// If any previous versions available E.g. #define WSADDRESSING_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define WSADDRESSING_PREVIOUS_VERSIONS "1.10.0"


//
// Template macros
//
#define WSADDRESSING_VERSION_CODE PACKAGE_VERSION_CODE(WSADDRESSING_VERSION_MAJOR,WSADDRESSING_VERSION_MINOR,WSADDRESSING_VERSION_PATCH)
#ifndef WSADDRESSING_PREVIOUS_VERSIONS
#define WSADDRESSING_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSADDRESSING_VERSION_MAJOR,WSADDRESSING_VERSION_MINOR,WSADDRESSING_VERSION_PATCH)
#else 
#define WSADDRESSING_FULL_VERSION_LIST  WSADDRESSING_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSADDRESSING_VERSION_MAJOR,WSADDRESSING_VERSION_MINOR,WSADDRESSING_VERSION_PATCH)
#endif 

namespace wsaddressing
{
	const std::string package  =  "wsaddressing";
	const std::string versions =  WSADDRESSING_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "WS-Addressing package";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
