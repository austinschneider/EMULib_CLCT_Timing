// $Id: version.h,v 1.9 2008/10/15 11:11:37 apetro Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_atcp_version_h_
#define _pt_atcp_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define PTATCP_VERSION_MAJOR 1
#define PTATCP_VERSION_MINOR 18
#define PTATCP_VERSION_PATCH 0
#define PTATCP_PREVIOUS_VERSIONS "1.14.0,1.15.0,1.16.0,1.17.0,1.18.0"
//#undef PTATCP_PREVIOUS_VERSIONS


//
// Template macros
//
#define PTATCP_VERSION_CODE PACKAGE_VERSION_CODE(PTATCP_VERSION_MAJOR,PTATCP_VERSION_MINOR,PTATCP_VERSION_PATCH)
#ifndef PTATCP_PREVIOUS_VERSIONS
#define PTATCP_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(PTATCP_VERSION_MAJOR,PTATCP_VERSION_MINOR,PTATCP_VERSION_PATCH)
#else 
#define PTATCP_FULL_VERSION_LIST  PTATCP_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(PTATCP_VERSION_MAJOR,PTATCP_VERSION_MINOR,PTATCP_VERSION_PATCH)
#endif 


namespace ptatcp 
{
	const std::string package  =  "ptatcp";
   	const std::string versions =  PTATCP_FULL_VERSION_LIST;
	const std::string summary = "ATCP peer transport with I2O service implementation";
	const std::string description = "";
	const std::string authors = "Marco Pieri, Andrea Petrucci";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xdaq";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
