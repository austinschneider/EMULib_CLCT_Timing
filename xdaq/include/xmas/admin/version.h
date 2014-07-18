// $Id$
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, L. Orsini, R. Moser                             *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_admin_version_h_
#define _xmas_admin_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASADMIN_VERSION_MAJOR 1
#define XMASADMIN_VERSION_MINOR 1
#define XMASADMIN_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASADMIN_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASADMIN_PREVIOUS_VERSIONS "1.0.3,1.0.4"


//
// Template macros
//
#define XMASADMIN_VERSION_CODE PACKAGE_VERSION_CODE(XMASADMIN_VERSION_MAJOR,XMASADMIN_VERSION_MINOR,XMASADMIN_VERSION_PATCH)
#ifndef XMASADMIN_PREVIOUS_VERSIONS
#define XMASADMIN_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASADMIN_VERSION_MAJOR,XMASADMIN_VERSION_MINOR,XMASADMIN_VERSION_PATCH)
#else 
#define XMASADMIN_FULL_VERSION_LIST  XMASADMIN_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASADMIN_VERSION_MAJOR,XMASADMIN_VERSION_MINOR,XMASADMIN_VERSION_PATCH)
#endif 

namespace xmasadmin
{
	const std::string package  =  "xmasadmin";
	const std::string versions =  XMASADMIN_FULL_VERSION_LIST;
	const std::string description = "This server is used for perfroming admin task on the monitoring services (e.g. clear)";
	const std::string authors = "Luciano Orsini, Roland Moser";
	const std::string summary = "A admin server for monitoring services";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
