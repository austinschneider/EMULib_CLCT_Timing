// $Id: version.h,v 1.7 2008/07/18 15:28:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_filter_version_h_
#define _xoap_filter_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XOAPFILTER_VERSION_MAJOR 3
#define XOAPFILTER_VERSION_MINOR 9
#define XOAPFILTER_VERSION_PATCH 2
// If any previous versions available E.g. #define XOAPFILTER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XOAPFILTER_PREVIOUS_VERSIONS "3.9.0,3.9.1" 


//
// Template macros
//
#define XOAPFILTER_VERSION_CODE PACKAGE_VERSION_CODE(XOAPFILTER_VERSION_MAJOR,XOAPFILTER_VERSION_MINOR,XOAPFILTER_VERSION_PATCH)
#ifndef XOAPFILTER_PREVIOUS_VERSIONS
#define XOAPFILTER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XOAPFILTER_VERSION_MAJOR,XOAPFILTER_VERSION_MINOR,XOAPFILTER_VERSION_PATCH)
#else 
#define XOAPFILTER_FULL_VERSION_LIST  XOAPFILTER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XOAPFILTER_VERSION_MAJOR,XOAPFILTER_VERSION_MINOR,XOAPFILTER_VERSION_PATCH)
#endif 
namespace xoapfilter 
{
	const std::string package  =  "xoapfilter";
	const std::string versions =  XOAPFILTER_FULL_VERSION_LIST;
	const std::string summary = "XOAP XPath filter library";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Core_Tools";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
