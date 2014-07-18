/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2007, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

//
// Version definition for SOAPtestV
//
#ifndef _state_dashboard_Version_H_
#define _state_dashboard_Version_H_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define STATEDASHBOARD_VERSION_MAJOR 1
#define STATEDASHBOARD_VERSION_MINOR 0
#define STATEDASHBOARD_VERSION_PATCH 4
// If any previous versions available E.g. #define STATEDASHBOARD_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef STATEDASHBOARD_PREVIOUS_VERSIONS


//
// Template macros
//
#define STATEDASHBOARD_VERSION_CODE PACKAGE_VERSION_CODE(STATEDASHBOARD_VERSION_MAJOR,STATEDASHBOARD_VERSION_MINOR,STATEDASHBOARD_VERSION_PATCH)
#ifndef STATEDASHBOARD_PREVIOUS_VERSIONS
#define STATEDASHBOARD_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(STATEDASHBOARD_VERSION_MAJOR,STATEDASHBOARD_VERSION_MINOR,STATEDASHBOARD_VERSION_PATCH)
#else
#define STATEDASHBOARD_FULL_VERSION_LIST  STATEDASHBOARD_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(STATEDASHBOARD_VERSION_MAJOR,STATEDASHBOARD_VERSION_MINOR,STATEDASHBOARD_VERSION_PATCH)
#endif

namespace statedashboard 
{
	const std::string package  =  "statedashboard";
	const std::string versions =  STATEDASHBOARD_FULL_VERSION_LIST;
	const std::string summary = "dashboard service for state notifications";
	const std::string description = "";
	const std::string authors = "Roland Moser";
	const std::string link = "http://xdaqwiki.cern.ch";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

