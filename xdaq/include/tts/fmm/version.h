// $Id: version.h,v 1.1 2007/03/26 09:43:22 hsakulin Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _TTSFMM_version_h_
#define _TTSFMM_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSFMM_VERSION_MAJOR 2
#define TTSFMM_VERSION_MINOR 0
#define TTSFMM_VERSION_PATCH 1
// If any previous versions available E.g. #define TTSFMM_PREVIOUS_VERSIONS "3.8.0,3.8.1"
//#undef TTSFMM_PREVIOUS_VERSIONS 
#define JOBCONTROL_PREVIOUS_VERSIONS "2.0.0"

//
// Template macros
//
#define TTSFMM_VERSION_CODE PACKAGE_VERSION_CODE(TTSFMM_VERSION_MAJOR,TTSFMM_VERSION_MINOR,TTSFMM_VERSION_PATCH)
#ifndef TTSFMM_PREVIOUS_VERSIONS
#define TTSFMM_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSFMM_VERSION_MAJOR,TTSFMM_VERSION_MINOR,TTSFMM_VERSION_PATCH)
#else 
#define TTSFMM_FULL_VERSION_LIST  TTSFMM_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSFMM_VERSION_MAJOR,TTSFMM_VERSION_MINOR,TTSFMM_VERSION_PATCH)
#endif 
namespace ttsfmm
{
	const std::string package  =  "ttsfmm";
	const std::string versions =  TTSFMM_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsfmm";
	const std::string link = "http://xdaqwiki.cern.ch/";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
