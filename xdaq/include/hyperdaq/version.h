// $Id: version.h,v 1.8 2009/04/01 13:00:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _hyperdaq_version_h_
#define _hyperdaq_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define HYPERDAQ_VERSION_MAJOR 4
#define HYPERDAQ_VERSION_MINOR 1
#define HYPERDAQ_VERSION_PATCH 2
// If any previous versions available E.g. #define HYPERDAQ_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define HYPERDAQ_PREVIOUS_VERSIONS "4.1.0,4.1.1"


//
// Template macros
//
#define HYPERDAQ_VERSION_CODE PACKAGE_VERSION_CODE(HYPERDAQ_VERSION_MAJOR,HYPERDAQ_VERSION_MINOR,HYPERDAQ_VERSION_PATCH)
#ifndef HYPERDAQ_PREVIOUS_VERSIONS
#define HYPERDAQ_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(HYPERDAQ_VERSION_MAJOR,HYPERDAQ_VERSION_MINOR,HYPERDAQ_VERSION_PATCH)
#else 
#define HYPERDAQ_FULL_VERSION_LIST  HYPERDAQ_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(HYPERDAQ_VERSION_MAJOR,HYPERDAQ_VERSION_MINOR,HYPERDAQ_VERSION_PATCH)
#endif 
namespace hyperdaq 
{
	const std::string package  =  "hyperdaq";
   	const std::string versions =  HYPERDAQ_FULL_VERSION_LIST;
	const std::string summary = "Web browser based access to XDAQ resources";
	const std::string description = "Hyperdaq lets users access XDAQ processes directly through their Web browsers";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Main_Page";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
