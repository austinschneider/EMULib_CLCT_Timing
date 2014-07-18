// $Id: version.h,v 1.30 2009/03/31 14:29:13 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las_version_h_
#define _xmas_las_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASLAS_VERSION_MAJOR 1
#define XMASLAS_VERSION_MINOR 22
#define XMASLAS_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASLAS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASLAS_PREVIOUS_VERSIONS "1.20.0,1.20.1,1.21.0,1.21.1,1.21.2"


//
// Template macros
//
#define XMASLAS_VERSION_CODE PACKAGE_VERSION_CODE(XMASLAS_VERSION_MAJOR,XMASLAS_VERSION_MINOR,XMASLAS_VERSION_PATCH)
#ifndef XMASLAS_PREVIOUS_VERSIONS
#define XMASLAS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASLAS_VERSION_MAJOR,XMASLAS_VERSION_MINOR,XMASLAS_VERSION_PATCH)
#else 
#define XMASLAS_FULL_VERSION_LIST  XMASLAS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASLAS_VERSION_MAJOR,XMASLAS_VERSION_MINOR,XMASLAS_VERSION_PATCH)
#endif 

namespace xmaslas
{
	const std::string package  =  "xmaslas";
	const std::string versions =  XMASLAS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System Life Access Server";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
