// $Id: version.h,v 1.4 2008/07/18 15:27:56 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xaccess_version_h_
#define _xaccess_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XACCESS_VERSION_MAJOR 1
#define XACCESS_VERSION_MINOR 9
#define XACCESS_VERSION_PATCH 0
// If any previous versions available E.g. #define XACCESS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XACCESS_PREVIOUS_VERSIONS 


//
// Template macros
//
#define XACCESS_VERSION_CODE PACKAGE_VERSION_CODE(XACCESS_VERSION_MAJOR,XACCESS_VERSION_MINOR,XACCESS_VERSION_PATCH)
#ifndef XACCESS_PREVIOUS_VERSIONS
#define XACCESS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XACCESS_VERSION_MAJOR,XACCESS_VERSION_MINOR,XACCESS_VERSION_PATCH)
#else 
#define XACCESS_FULL_VERSION_LIST  XACCESS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XACCESS_VERSION_MAJOR,XACCESS_VERSION_MINOR,XACCESS_VERSION_PATCH)
#endif 

namespace xaccess 
{
	const std::string package  =  "xaccess";
   	const std::string versions =  XACCESS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "User authentication/authorization agent";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xdaq";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
