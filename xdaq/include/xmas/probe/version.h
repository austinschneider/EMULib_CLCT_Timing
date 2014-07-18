// $Id: version.h,v 1.14 2008/11/14 08:19:54 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_version_h_
#define _xmas_probe_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASPROBE_VERSION_MAJOR 1
#define XMASPROBE_VERSION_MINOR 0
#define XMASPROBE_VERSION_PATCH 1
// If any previous versions available E.g. #define XMASPROBE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASPROBE_PREVIOUS_VERSIONS "1.0.0"


//
// Template macros
//
#define XMASPROBE_VERSION_CODE PACKAGE_VERSION_CODE(XMASPROBE_VERSION_MAJOR,XMASPROBE_VERSION_MINOR,XMASPROBE_VERSION_PATCH)
#ifndef XMASPROBE_PREVIOUS_VERSIONS
#define XMASPROBE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASPROBE_VERSION_MAJOR,XMASPROBE_VERSION_MINOR,XMASPROBE_VERSION_PATCH)
#else 
#define XMASPROBE_FULL_VERSION_LIST  XMASPROBE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASPROBE_VERSION_MAJOR,XMASPROBE_VERSION_MINOR,XMASPROBE_VERSION_PATCH)
#endif 

namespace xmasprobe
{
	const std::string package  =  "xmasprobe";
	const std::string versions =  XMASPROBE_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System probe";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
