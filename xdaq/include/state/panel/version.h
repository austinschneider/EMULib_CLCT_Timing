/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _statepanel_version_h_
#define _statepanel_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define STATEPANEL_VERSION_MAJOR 1
#define STATEPANEL_VERSION_MINOR 0 
#define STATEPANEL_VERSION_PATCH 0
// If any previous versions available E.g. #define STATEPANEL_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef STATEPANEL_PREVIOUS_VERSIONS


//
// Template macros
//
#define STATEPANEL_VERSION_CODE PACKAGE_VERSION_CODE(STATEPANEL_VERSION_MAJOR,STATEPANEL_VERSION_MINOR,STATEPANEL_VERSION_PATCH)
#ifndef STATEPANEL_PREVIOUS_VERSIONS
#define STATEPANEL_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(STATEPANEL_VERSION_MAJOR,STATEPANEL_VERSION_MINOR,STATEPANEL_VERSION_PATCH)
#else 
#define STATEPANEL_FULL_VERSION_LIST  STATEPANEL_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(STATEPANEL_VERSION_MAJOR,STATEPANEL_VERSION_MINOR,STATEPANEL_VERSION_PATCH)
#endif 

namespace statepanel
{
	const std::string package  =  "statepanel";
	const std::string versions =  STATEPANEL_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Roland Moser";
	const std::string summary = "Status panel for errors and countermeasures";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
