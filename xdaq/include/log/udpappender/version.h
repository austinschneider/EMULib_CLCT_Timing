// $Id: version.h,v 1.3 2008/07/18 15:26:55 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _log_udpappender_version_h_
#define _log_udpappender_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define LOGUDPAPPENDER_VERSION_MAJOR 3
#define LOGUDPAPPENDER_VERSION_MINOR 10 
#define LOGUDPAPPENDER_VERSION_PATCH 0
// If any previous versions available E.g. #define LOGUDPAPPENDER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef LOGUDPAPPENDER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define LOGUDPAPPENDER_VERSION_CODE PACKAGE_VERSION_CODE(LOGUDPAPPENDER_VERSION_MAJOR,LOGUDPAPPENDER_VERSION_MINOR,LOGUDPAPPENDER_VERSION_PATCH)
#ifndef LOGUDPAPPENDER_PREVIOUS_VERSIONS
#define LOGUDPAPPENDER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(LOGUDPAPPENDER_VERSION_MAJOR,LOGUDPAPPENDER_VERSION_MINOR,LOGUDPAPPENDER_VERSION_PATCH)
#else 
#define LOGUDPAPPENDER_FULL_VERSION_LIST  LOGUDPAPPENDER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(LOGUDPAPPENDER_VERSION_MAJOR,LOGUDPAPPENDER_VERSION_MINOR,LOGUDPAPPENDER_VERSION_PATCH)
#endif 
namespace logudpappender 
{
	const std::string package  =  "logudpappender";
   	const std::string versions =  LOGUDPAPPENDER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "UDP network appender for log4cplus package";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/log4cplus";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}
#endif
