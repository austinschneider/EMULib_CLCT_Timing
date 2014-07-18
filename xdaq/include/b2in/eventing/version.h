// $Id: version.h,v 1.7 2009/02/13 15:38:42 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_eventing_version_h_
#define _b2in_eventing_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define B2INEVENTING_VERSION_MAJOR 1
#define B2INEVENTING_VERSION_MINOR 4
#define B2INEVENTING_VERSION_PATCH 0
// If any previous versions available E.g. #define B2INEVENTING_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define B2INEVENTING_PREVIOUS_VERSIONS  "1.0.0,1.0.1,1.0.2,1.1.0,1.1.1,1.1.2,1.2.0,1.2.1,1.3.0,1.3.1"


//
// Template macros
//
#define B2INEVENTING_VERSION_CODE PACKAGE_VERSION_CODE(B2INEVENTING_VERSION_MAJOR,B2INEVENTING_VERSION_MINOR,B2INEVENTING_VERSION_PATCH)
#ifndef B2INEVENTING_PREVIOUS_VERSIONS
#define B2INEVENTING_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(B2INEVENTING_VERSION_MAJOR,B2INEVENTING_VERSION_MINOR,B2INEVENTING_VERSION_PATCH)
#else 
#define B2INEVENTING_FULL_VERSION_LIST  B2INEVENTING_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(B2INEVENTING_VERSION_MAJOR,B2INEVENTING_VERSION_MINOR,B2INEVENTING_VERSION_PATCH)
#endif 

namespace b2ineventing
{
	const std::string package  =  "b2ineventing";
	const std::string versions =  B2INEVENTING_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "B2IN fast publish/subscriber";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
