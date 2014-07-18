// $Id: version.h,v 1.7 2008/11/12 10:45:11 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinelutils_version_h_
#define _sentinelutils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define SENTINELUTILS_VERSION_MAJOR 2
#define SENTINELUTILS_VERSION_MINOR 0
#define SENTINELUTILS_VERSION_PATCH 1
// If any previous versions available E.g. #define SENTINELUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define SENTINELUTILS_PREVIOUS_VERSIONS "1.9.0,1.10.0,1.11.0,1.11.1,2.0.0"


//
// Template macros
//
#define SENTINELUTILS_VERSION_CODE PACKAGE_VERSION_CODE(SENTINELUTILS_VERSION_MAJOR,SENTINELUTILS_VERSION_MINOR,SENTINELUTILS_VERSION_PATCH)
#ifndef SENTINELUTILS_PREVIOUS_VERSIONS
#define SENTINELUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(SENTINELUTILS_VERSION_MAJOR,SENTINELUTILS_VERSION_MINOR,SENTINELUTILS_VERSION_PATCH)
#else 
#define SENTINELUTILS_FULL_VERSION_LIST  SENTINELUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(SENTINELUTILS_VERSION_MAJOR,SENTINELUTILS_VERSION_MINOR,SENTINELUTILS_VERSION_PATCH)
#endif 

namespace sentinelutils
{
	const std::string package  =  "sentinelutils";
   	const std::string versions =  SENTINELUTILS_FULL_VERSION_LIST;
	const std::string summary = "Sentinel utilities";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
