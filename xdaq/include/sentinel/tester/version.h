// $Id: version.h,v 1.9 2008/12/02 15:57:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_tester_version_h_
#define _sentinel_tester_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define SENTINELTESTER_VERSION_MAJOR 2
#define SENTINELTESTER_VERSION_MINOR 0 
#define SENTINELTESTER_VERSION_PATCH 0
// If any previous versions available E.g. #define SENTINELTESTER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef SENTINELTESTER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define SENTINELTESTER_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELTESTER_VERSION_MAJOR,SENTINELTESTER_VERSION_MINOR,SENTINELTESTER_VERSION_PATCH)
#ifndef SENTINELTESTER_PREVIOUS_VERSIONS
#define SENTINELTESTER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELTESTER_VERSION_MAJOR,SENTINELTESTER_VERSION_MINOR,SENTINELTESTER_VERSION_PATCH)
#else 
#define SENTINELTESTER_FULL_VERSION_LIST  SENTINELTESTER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELTESTER_VERSION_MAJOR,SENTINELTESTER_VERSION_MINOR,SENTINELTESTER_VERSION_PATCH)
#endif 

namespace sentineltester
{
	const std::string package  =  "sentineltester";
	const std::string versions =  SENTINELTESTER_FULL_VERSION_LIST;
	const std::string summary = "Distributed error handling tester";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
