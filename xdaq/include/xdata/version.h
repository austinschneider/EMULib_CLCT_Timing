// $Id: version.h,v 1.28 2008/10/13 12:58:57 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_version_h_
#define _xdata_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XDATA_VERSION_MAJOR 5
#define XDATA_VERSION_MINOR 3
#define XDATA_VERSION_PATCH 1
// If any previous versions available E.g. #define XDATA_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XDATA_PREVIOUS_VERSIONS


//
// Template macros
//
#define XDATA_VERSION_CODE PACKAGE_VERSION_CODE(XDATA_VERSION_MAJOR,XDATA_VERSION_MINOR,XDATA_VERSION_PATCH)
#ifndef XDATA_PREVIOUS_VERSIONS
#define XDATA_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XDATA_VERSION_MAJOR,XDATA_VERSION_MINOR,XDATA_VERSION_PATCH)
#else 
#define XDATA_FULL_VERSION_LIST  XDATA_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XDATA_VERSION_MAJOR,XDATA_VERSION_MINOR,XDATA_VERSION_PATCH)
#endif 

namespace xdata 
{
	const std::string package  =  "xdata";
   	const std::string versions =  XDATA_FULL_VERSION_LIST;
	const std::string summary = "SOAP C++ programming package, Xerces, namespace xoap";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Core_Tools";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
