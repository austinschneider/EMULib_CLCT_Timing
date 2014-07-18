// $Id: version.h,v 1.5 2008/07/18 15:27:47 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_client_version_h_
#define _ws_client_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define WSCLIENT_VERSION_MAJOR 1
#define WSCLIENT_VERSION_MINOR 9
#define WSCLIENT_VERSION_PATCH 0
// If any previous versions available E.g. #define WSCLIENT_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef WSCLIENT_PREVIOUS_VERSIONS 


//
// Template macros
//
#define WSCLIENT_VERSION_CODE PACKAGE_VERSION_CODE(WSCLIENT_VERSION_MAJOR,WSCLIENT_VERSION_MINOR,WSCLIENT_VERSION_PATCH)
#ifndef WSCLIENT_PREVIOUS_VERSIONS
#define WSCLIENT_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(WSCLIENT_VERSION_MAJOR,WSCLIENT_VERSION_MINOR,WSCLIENT_VERSION_PATCH)
#else 
#define WSCLIENT_FULL_VERSION_LIST  WSCLIENT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(WSCLIENT_VERSION_MAJOR,WSCLIENT_VERSION_MINOR,WSCLIENT_VERSION_PATCH)
#endif 

namespace wsclient
{
	const std::string package  =  "wsclient";
	const std::string versions =  WSCLIENT_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "WS eventing test client";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
