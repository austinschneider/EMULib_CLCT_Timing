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

#ifndef _xmas_sensor2g_version_h_
#define _xmas_sensor2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASSENSOR2G_VERSION_MAJOR 2
#define XMASSENSOR2G_VERSION_MINOR 2
#define XMASSENSOR2G_VERSION_PATCH 2
// If any previous versions available E.g. #define XMASSENSOR2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASSENSOR2G_PREVIOUS_VERSIONS "2.0.0,2.0.1,2.0.2,2.1.0,2.1.1,2.2.0,2.2.1"


//
// Template macros
//
#define XMASSENSOR2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASSENSOR2G_VERSION_MAJOR,XMASSENSOR2G_VERSION_MINOR,XMASSENSOR2G_VERSION_PATCH)
#ifndef XMASSENSOR2G_PREVIOUS_VERSIONS
#define XMASSENSOR2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASSENSOR2G_VERSION_MAJOR,XMASSENSOR2G_VERSION_MINOR,XMASSENSOR2G_VERSION_PATCH)
#else 
#define XMASSENSOR2G_FULL_VERSION_LIST  XMASSENSOR2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASSENSOR2G_VERSION_MAJOR,XMASSENSOR2G_VERSION_MINOR,XMASSENSOR2G_VERSION_PATCH)
#endif 

namespace xmassensor2g
{
	const std::string package  =  "xmassensor2g";
	const std::string versions =  XMASSENSOR2G_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System sensor2g";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
