// $Id: version.h,v 1.8 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_version_h_
#define _xgi_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XGI_VERSION_MAJOR 3
#define XGI_VERSION_MINOR 13
#define XGI_VERSION_PATCH 0
// If any previous versions available E.g. #define XGI_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XGI_PREVIOUS_VERSIONS "3.11.0, 3.11.1,3.11.2,3.12.0"


//
// Template macros
//
#define XGI_VERSION_CODE PACKAGE_VERSION_CODE(XGI_VERSION_MAJOR,XGI_VERSION_MINOR,XGI_VERSION_PATCH)
#ifndef XGI_PREVIOUS_VERSIONS
#define XGI_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XGI_VERSION_MAJOR,XGI_VERSION_MINOR,XGI_VERSION_PATCH)
#else 
#define XGI_FULL_VERSION_LIST  XGI_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XGI_VERSION_MAJOR,XGI_VERSION_MINOR,XGI_VERSION_PATCH)
#endif 

namespace xgi 
{
	const std::string package  =  "xgi";
   	const std::string versions =  XGI_FULL_VERSION_LIST;
	const std::string summary = "CGI embedded Web page processing package";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xgi";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
