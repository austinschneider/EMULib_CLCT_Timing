// $Id: version.h,v 1.10 2008/12/02 15:46:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xcept_version_h_
#define _xcept_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XCEPT_VERSION_MAJOR 3
#define XCEPT_VERSION_MINOR 13
#define XCEPT_VERSION_PATCH 3
// If any previous versions available E.g. #define XCEPT_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XCEPT_PREVIOUS_VERSIONS  "3.9.0,3.10.0,3.11.0,3.12.0,3.13.0,3.13.1,3.13.2"


//
// Template macros
//
#define XCEPT_VERSION_CODE PACKAGE_VERSION_CODE(XCEPT_VERSION_MAJOR,XCEPT_VERSION_MINOR,XCEPT_VERSION_PATCH)
#ifndef XCEPT_PREVIOUS_VERSIONS
#define XCEPT_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XCEPT_VERSION_MAJOR,XCEPT_VERSION_MINOR,XCEPT_VERSION_PATCH)
#else 
#define XCEPT_FULL_VERSION_LIST  XCEPT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XCEPT_VERSION_MAJOR,XCEPT_VERSION_MINOR,XCEPT_VERSION_PATCH)
#endif 


namespace xcept 
{
	const std::string package  =  "xcept";
   	const std::string versions = XCEPT_FULL_VERSION_LIST;
	const std::string summary = "Exception definition and handling package";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xcept";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
