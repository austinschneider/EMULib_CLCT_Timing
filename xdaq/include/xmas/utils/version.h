// $Id: version.h,v 1.12 2008/07/18 15:28:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_utils_version_h_
#define _xmas_utils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASUTILS_VERSION_MAJOR 1
#define XMASUTILS_VERSION_MINOR 17
#define XMASUTILS_VERSION_PATCH 2
// If any previous versions available E.g. #define XMAS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASUTILS_PREVIOUS_VERSIONS "1.16.0,1.17.0,1.17.1"


//
// Template macros
//
#define XMASUTILS_VERSION_CODE PACKAGE_VERSION_CODE(XMASUTILS_VERSION_MAJOR,XMASUTILS_VERSION_MINOR,XMASUTILS_VERSION_PATCH)
#ifndef XMASUTILS_PREVIOUS_VERSIONS
#define XMASUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASUTILS_VERSION_MAJOR,XMASUTILS_VERSION_MINOR,XMASUTILS_VERSION_PATCH)
#else 
#define XMASUTILS_FULL_VERSION_LIST  XMASUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASUTILS_VERSION_MAJOR,XMASUTILS_VERSION_MINOR,XMASUTILS_VERSION_PATCH)
#endif 
namespace xmasutils
{
	const std::string package  =  "xmasutils";
	const std::string versions =  XMASUTILS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System common library";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
