// $Id: version.h,v 1.2 2007/06/08 08:30:57 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pheaps_version_h_
#define _pheaps_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define PHEAPS_VERSION_MAJOR 1
#define PHEAPS_VERSION_MINOR 14
#define PHEAPS_VERSION_PATCH 0
// If any previous versions available E.g. #define PHEAPS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define PHEAPS_PREVIOUS_VERSIONS  "1.9.0,1.10.0,1.11.0,1.12.0,1.13.0"


//
// Template macros
//
#define PHEAPS_VERSION_CODE PACKAGE_VERSION_CODE(PHEAPS_VERSION_MAJOR,PHEAPS_VERSION_MINOR,PHEAPS_VERSION_PATCH)
#ifndef PHEAPS_PREVIOUS_VERSIONS
#define PHEAPS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(PHEAPS_VERSION_MAJOR,PHEAPS_VERSION_MINOR,PHEAPS_VERSION_PATCH)
#else 
#define PHEAPS_FULL_VERSION_LIST  PHEAPS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(PHEAPS_VERSION_MAJOR,PHEAPS_VERSION_MINOR,PHEAPS_VERSION_PATCH)
#endif 
namespace pheaps
{
	const std::string package  =  "pheaps";
	const std::string versions =  PHEAPS_FULL_VERSION_LIST;
	const std::string summary = "Physical memory pluggable allocator";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Xplore";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
