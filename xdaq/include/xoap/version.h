// $Id: version.h,v 1.25 2008/11/18 11:20:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_version_h_
#define _xoap_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XOAP_VERSION_MAJOR 3
#define XOAP_VERSION_MINOR 12
#define XOAP_VERSION_PATCH 2
// If any previous versions available E.g. #define XOAP_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XOAP_PREVIOUS_VERSIONS "3.12.0,3.12.1"


//
// Template macros
//
#define XOAP_VERSION_CODE PACKAGE_VERSION_CODE(XOAP_VERSION_MAJOR,XOAP_VERSION_MINOR,XOAP_VERSION_PATCH)
#ifndef XOAP_PREVIOUS_VERSIONS
#define XOAP_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XOAP_VERSION_MAJOR,XOAP_VERSION_MINOR,XOAP_VERSION_PATCH)
#else 
#define XOAP_FULL_VERSION_LIST  XOAP_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XOAP_VERSION_MAJOR,XOAP_VERSION_MINOR,XOAP_VERSION_PATCH)
#endif 

namespace xoap 
{
	const std::string package  =  "xoap";
   	const std::string versions =  XOAP_FULL_VERSION_LIST;
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "SOAP C++ programming package based on Xerces 2.7";
	const std::string description = "";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xoap";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
