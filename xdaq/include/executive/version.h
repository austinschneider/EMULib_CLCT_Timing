// $Id: version.h,v 1.12 2009/05/11 16:26:36 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _executive_version_h_
#define _executive_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define EXECUTIVE_VERSION_MAJOR 3
#define EXECUTIVE_VERSION_MINOR 15
#define EXECUTIVE_VERSION_PATCH 4
// If any previous versions available E.g. #define EXECUTIVE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define EXECUTIVE_PREVIOUS_VERSIONS "3.11.0,3.11.1,3.12.0,3.13.0,3.14.0,3.15.0,3.15.1,3.15.2,3.15.3" 


//
// Template macros
//
#define EXECUTIVE_VERSION_CODE PACKAGE_VERSION_CODE(EXECUTIVE_VERSION_MAJOR,EXECUTIVE_VERSION_MINOR,EXECUTIVE_VERSION_PATCH)
#ifndef EXECUTIVE_PREVIOUS_VERSIONS
#define EXECUTIVE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(EXECUTIVE_VERSION_MAJOR,EXECUTIVE_VERSION_MINOR,EXECUTIVE_VERSION_PATCH)
#else 
#define EXECUTIVE_FULL_VERSION_LIST  EXECUTIVE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(EXECUTIVE_VERSION_MAJOR,EXECUTIVE_VERSION_MINOR,EXECUTIVE_VERSION_PATCH)
#endif 

namespace executive 
{
	const std::string package  =  "executive";
   	const std::string versions =  EXECUTIVE_FULL_VERSION_LIST;
	const std::string summary = "XDAQ process controller";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Executive_configuration";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
