// $Id: version.h,v 1.28 2009/04/01 08:33:17 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_version_h_
#define _xdaq_version_h_

#include "config/PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!

#define XDAQ_VERSION_MAJOR 3
#define XDAQ_VERSION_MINOR 35
#define XDAQ_VERSION_PATCH 0
// If any previous versions available E.g. #define XDAQ_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XDAQ_PREVIOUS_VERSIONS "3.34.0,3.34.1,3.34.2,3.34.3"


//
// Template macros
//
#define XDAQ_VERSION_CODE PACKAGE_VERSION_CODE(XDAQ_VERSION_MAJOR,XDAQ_VERSION_MINOR,XDAQ_VERSION_PATCH)
#ifndef XDAQ_PREVIOUS_VERSIONS
#define XDAQ_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XDAQ_VERSION_MAJOR,XDAQ_VERSION_MINOR,XDAQ_VERSION_PATCH)
#else 
#define XDAQ_FULL_VERSION_LIST  XDAQ_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XDAQ_VERSION_MAJOR,XDAQ_VERSION_MINOR,XDAQ_VERSION_PATCH)
#endif 


namespace xdaq 
{
	const std::string package  =  "xdaq";
   	const std::string versions =  XDAQ_FULL_VERSION_LIST;
	const std::string summary = "XDAQ core package";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xdaq";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
