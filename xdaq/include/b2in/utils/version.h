// $Id: version.h,v 1.4 2008/08/14 08:03:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_version_h_
#define _b2in_utils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define B2INUTILS_VERSION_MAJOR 4
#define B2INUTILS_VERSION_MINOR 0
#define B2INUTILS_VERSION_PATCH 0
// If any previous versions available E.g. #define B2INUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef B2INUTILS_PREVIOUS_VERSIONS


//
// Template macros
//
#define B2INUTILS_VERSION_CODE PACKAGE_VERSION_CODE(B2INUTILS_VERSION_MAJOR,B2INUTILS_VERSION_MINOR,B2INUTILS_VERSION_PATCH)
#ifndef B2INUTILS_PREVIOUS_VERSIONS
#define B2INUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(B2INUTILS_VERSION_MAJOR,B2INUTILS_VERSION_MINOR,B2INUTILS_VERSION_PATCH)
#else 
#define B2INUTILS_FULL_VERSION_LIST  B2INUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(B2INUTILS_VERSION_MAJOR,B2INUTILS_VERSION_MINOR,B2INUTILS_VERSION_PATCH)
#endif 


namespace b2inutils 
{
	const std::string package  =  "b2inutils";
   	const std::string versions =  B2INUTILS_FULL_VERSION_LIST;
	const std::string summary = "B2IN protocol utilities";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/B2IN_Messaging";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
