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

#ifndef _xmas_slash2g_version_h_
#define _xmas_slash2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASSLASH2G_VERSION_MAJOR 1
#define XMASSLASH2G_VERSION_MINOR 1
#define XMASSLASH2G_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASSLASH2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XMASSLASH2G_PREVIOUS_VERSIONS


//
// Template macros
//
#define XMASSLASH2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASSLASH2G_VERSION_MAJOR,XMASLAS2_VERSION_MINOR,XMASSLASH2G_VERSION_PATCH)
#ifndef XMASSLASH2G_PREVIOUS_VERSIONS
#define XMASSLASH2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASSLASH2G_VERSION_MAJOR,XMASSLASH2G_VERSION_MINOR,XMASSLASH2G_VERSION_PATCH)
#else 
#define XMASSLASH2G_FULL_VERSION_LIST  XMASSLASH2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASSLASH2G_VERSION_MAJOR,XMASSLASH2G_VERSION_MINOR,XMASSLASH2G_VERSION_PATCH)
#endif 

namespace xmasslash2g
{
	const std::string package  =  "xmasslash2g";
	const std::string versions =  XMASSLASH2G_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Roland Moser, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System Smart Life Access Server Hub for B2IN";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif

