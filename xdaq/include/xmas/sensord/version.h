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

#ifndef _xmas_sensord_version_h_
#define _xmas_sensord_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASSENSORD_VERSION_MAJOR 1
#define XMASSENSORD_VERSION_MINOR 0
#define XMASSENSORD_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASSENSORD_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XMASSENSORD_PREVIOUS_VERSIONS


//
// Template macros
//
#define XMASSENSORD_VERSION_CODE PACKAGE_VERSION_CODE(XMASSENSORD_VERSION_MAJOR,XMASSENSORD_VERSION_MINOR,XMASSENSORD_VERSION_PATCH)
#ifndef XMASSENSORD_PREVIOUS_VERSIONS
#define XMASSENSORD_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASSENSORD_VERSION_MAJOR,XMASSENSORD_VERSION_MINOR,XMASSENSORD_VERSION_PATCH)
#else 
#define XMASSENSORD_FULL_VERSION_LIST  XMASSENSORD_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASSENSORD_VERSION_MAJOR,XMASSENSORD_VERSION_MINOR,XMASSENSORD_VERSION_PATCH)
#endif 

namespace xmassensord
{
	const std::string package  =  "xmassensord";
	const std::string versions =  XMASSENSORD_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System sensord";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
