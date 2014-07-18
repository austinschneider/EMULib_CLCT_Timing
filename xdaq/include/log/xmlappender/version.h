// $Id: version.h,v 1.4 2008/07/18 15:27:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _log_xmlappender_version_h_
#define _log_xmlappender_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define LOGXMLAPPENDER_VERSION_MAJOR 3
#define LOGXMLAPPENDER_VERSION_MINOR 10 
#define LOGXMLAPPENDER_VERSION_PATCH 3
// If any previous versions available E.g. #define LOGXMLAPPENDER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define LOGXMLAPPENDER_PREVIOUS_VERSIONS "3.10.0,3.10.1,3.10.2"


//
// Template macros
//
#define LOGXMLAPPENDER_VERSION_CODE PACKAGE_VERSION_CODE(LOGXMLAPPENDER_VERSION_MAJOR,LOGXMLAPPENDER_VERSION_MINOR,LOGXMLAPPENDER_VERSION_PATCH)
#ifndef LOGXMLAPPENDER_PREVIOUS_VERSIONS
#define LOGXMLAPPENDER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(LOGXMLAPPENDER_VERSION_MAJOR,LOGXMLAPPENDER_VERSION_MINOR,LOGXMLAPPENDER_VERSION_PATCH)
#else 
#define LOGXMLAPPENDER_FULL_VERSION_LIST  LOGXMLAPPENDER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(LOGXMLAPPENDER_VERSION_MAJOR,LOGXMLAPPENDER_VERSION_MINOR,LOGXMLAPPENDER_VERSION_PATCH)
#endif 

namespace logxmlappender 
{
	const std::string package  =  "logxmlappender";
   	const std::string versions =  LOGXMLAPPENDER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XML message over TCP network appender for log4cplus package";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/log4cplus";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
