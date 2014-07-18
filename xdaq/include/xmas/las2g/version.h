// $Id: version.h,v 1.11 2009/02/20 14:09:29 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las2g_version_h_
#define _xmas_las2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASLAS2G_VERSION_MAJOR 2
#define XMASLAS2G_VERSION_MINOR 2
#define XMASLAS2G_VERSION_PATCH 1
// If any previous versions available E.g. #define XMASLAS2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XMASLAS2G_PREVIOUS_VERSIONS


//
// Template macros
//
#define XMASLAS2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASLAS2G_VERSION_MAJOR,XMASLAS2_VERSION_MINOR,XMASLAS2G_VERSION_PATCH)
#ifndef XMASLAS2G_PREVIOUS_VERSIONS
#define XMASLAS2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASLAS2G_VERSION_MAJOR,XMASLAS2G_VERSION_MINOR,XMASLAS2G_VERSION_PATCH)
#else 
#define XMASLAS2G_FULL_VERSION_LIST  XMASLAS2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASLAS2G_VERSION_MAJOR,XMASLAS2G_VERSION_MINOR,XMASLAS2G_VERSION_PATCH)
#endif 

namespace xmaslas2g
{
	const std::string package  =  "xmaslas2g";
	const std::string versions =  XMASLAS2G_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System Life Access Server for B2IN";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
