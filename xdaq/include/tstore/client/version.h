// $Id: version.h,v 1.8 2007/10/25 08:44:44 brett Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _tstoreclient_version_h_
#define _tstoreclient_version_h_

#include "config/PackageInfo.h"

#define TSTORECLIENT_VERSION_MAJOR 1
#define TSTORECLIENT_VERSION_MINOR 16
#define TSTORECLIENT_VERSION_PATCH 0
// If any previous versions available E.g. #define TSTORECLIENT_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TSTORECLIENT_PREVIOUS_VERSIONS

//
// Template macros
//
#define TSTORECLIENT_VERSION_CODE PACKAGE_VERSION_CODE(TSTORECLIENT_VERSION_MAJOR,TSTORECLIENT_VERSION_MINOR,TSTORECLIENT_VERSION_PATCH)
#ifndef TSTORECLIENT_PREVIOUS_VERSIONS
#define TSTORECLIENT_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TSTORECLIENT_VERSION_MAJOR,TSTORECLIENT_VERSION_MINOR,TSTORECLIENT_VERSION_PATCH)
#else 
#define TSTORECLIENT_FULL_VERSION_LIST  TSTORECLIENT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TSTORECLIENT_VERSION_MAJOR,TSTORECLIENT_VERSION_MINOR,TSTORECLIENT_VERSION_PATCH)
#endif 

namespace tstoreclient
{
	const std::string package  =  "tstoreclient";
	const std::string versions =  TSTORECLIENT_FULL_VERSION_LIST;
	const std::string description = "Library containing useful functions for client applications of TStore";
	const std::string summary = "TStore client library";
	const std::string authors = "Angela Brett";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/TStore";
	
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
