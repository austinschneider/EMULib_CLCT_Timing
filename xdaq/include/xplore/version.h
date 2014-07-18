// $Id: version.h,v 1.17 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_version_h_
#define _xplore_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XPLORE_VERSION_MAJOR 1
#define XPLORE_VERSION_MINOR 17
#define XPLORE_VERSION_PATCH 0
// If any previous versions available E.g. #define XPLORE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XPLORE_PREVIOUS_VERSIONS "1.16.0,1.16.1"


//
// Template macros
//
#define XPLORE_VERSION_CODE PACKAGE_VERSION_CODE(XPLORE_VERSION_MAJOR,XPLORE_VERSION_MINOR,XPLORE_VERSION_PATCH)
#ifndef XPLORE_PREVIOUS_VERSIONS
#define XPLORE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XPLORE_VERSION_MAJOR,XPLORE_VERSION_MINOR,XPLORE_VERSION_PATCH)
#else 
#define XPLORE_FULL_VERSION_LIST  XPLORE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XPLORE_VERSION_MAJOR,XPLORE_VERSION_MINOR,XPLORE_VERSION_PATCH)
#endif 
namespace xplore
{
	const std::string package  =  "xplore";
	const std::string versions =  XPLORE_FULL_VERSION_LIST;
	const std::string summary = "Service discovery explorer and retrieval services";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Xplore";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
