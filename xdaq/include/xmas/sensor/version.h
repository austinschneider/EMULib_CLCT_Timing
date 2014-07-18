// $Id: version.h,v 1.46 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_version_h_
#define _xmas_sensor_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASSENSOR_VERSION_MAJOR 1
#define XMASSENSOR_VERSION_MINOR 29
#define XMASSENSOR_VERSION_PATCH 2
// If any previous versions available E.g. #define XMASSENSOR_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASSENSOR_PREVIOUS_VERSIONS "1.29.0,1.29.1"


//
// Template macros
//
#define XMASSENSOR_VERSION_CODE PACKAGE_VERSION_CODE(XMASSENSOR_VERSION_MAJOR,XMASSENSOR_VERSION_MINOR,XMASSENSOR_VERSION_PATCH)
#ifndef XMASSENSOR_PREVIOUS_VERSIONS
#define XMASSENSOR_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASSENSOR_VERSION_MAJOR,XMASSENSOR_VERSION_MINOR,XMASSENSOR_VERSION_PATCH)
#else 
#define XMASSENSOR_FULL_VERSION_LIST  XMASSENSOR_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASSENSOR_VERSION_MAJOR,XMASSENSOR_VERSION_MINOR,XMASSENSOR_VERSION_PATCH)
#endif 

namespace xmassensor
{
	const std::string package  =  "xmassensor";
	const std::string versions =  XMASSENSOR_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System sensor";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
