// $Id: version.h,v 1.3 2009/01/09 08:19:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_nub_version_h_
#define _b2in_nub_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define B2INNUB_VERSION_MAJOR 2
#define B2INNUB_VERSION_MINOR 1
#define B2INNUB_VERSION_PATCH 0
// If any previous versions available E.g. #define B2INNUB_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef B2INNUB_PREVIOUS_VERSIONS


//
// Template macros
//
#define B2INNUB_VERSION_CODE PACKAGE_VERSION_CODE(B2INNUB_VERSION_MAJOR,B2INNUB_VERSION_MINOR,B2INNUB_VERSION_PATCH)
#ifndef B2INNUB_PREVIOUS_VERSIONS
#define B2INNUB_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(B2INNUB_VERSION_MAJOR,B2INNUB_VERSION_MINOR,B2INNUB_VERSION_PATCH)
#else 
#define B2INNUB_FULL_VERSION_LIST  B2INNUB_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(B2INNUB_VERSION_MAJOR,B2INNUB_VERSION_MINOR,B2INNUB_VERSION_PATCH)
#endif 


namespace b2innub 
{
	const std::string package  =  "b2innub";
   	const std::string versions =  B2INNUB_FULL_VERSION_LIST;
	const std::string summary = "B2IN protocol pluggable core";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/B2IN_Messaging";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
