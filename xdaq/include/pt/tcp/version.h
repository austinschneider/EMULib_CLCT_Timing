// $Id: version.h,v 1.19 2009/03/04 08:51:31 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_version_h_
#define _pt_tcp_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define PTTCP_VERSION_MAJOR 2
#define PTTCP_VERSION_MINOR 13
#define PTTCP_VERSION_PATCH 3
// If any previous versions available E.g. #define PTTCP_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define PTTCP_PREVIOUS_VERSIONS "2.12.3,2.13.0,2.13.1,2.13.2"


//
// Template macros
//
#define PTTCP_VERSION_CODE PACKAGE_VERSION_CODE(PTTCP_VERSION_MAJOR,PTTCP_VERSION_MINOR,PTTCP_VERSION_PATCH)
#ifndef PTTCP_PREVIOUS_VERSIONS
#define PTTCP_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(PTTCP_VERSION_MAJOR,PTTCP_VERSION_MINOR,PTTCP_VERSION_PATCH)
#else 
#define PTTCP_FULL_VERSION_LIST  PTTCP_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(PTTCP_VERSION_MAJOR,PTTCP_VERSION_MINOR,PTTCP_VERSION_PATCH)
#endif 


namespace pttcp 
{
	const std::string package  =  "pttcp";
   	const std::string versions =  PTTCP_FULL_VERSION_LIST;
	const std::string summary = "TCP peer transport with I2O service implementation";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xdaq";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
