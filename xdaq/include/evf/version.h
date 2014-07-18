// $Id: version.h,v 1.1 2008/02/06 13:48:24 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _interface_shared_version_h_
#define _interface_shared_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define EVF_VERSION_MAJOR 1
#define EVF_VERSION_MINOR 3
#define EVF_VERSION_PATCH 2
// If any previous versions available E.g. #define INTERFACESHARED_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef EVF_PREVIOUS_VERSIONS 


//
// Template macros
//
#define EVF_VERSION_CODE PACKAGE_VERSION_CODE(EVF_VERSION_MAJOR,EVF_VERSION_MINOR,EVF_VERSION_PATCH)
#ifndef EVF_PREVIOUS_VERSIONS
#define EVF_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(EVF_VERSION_MAJOR,EVF_VERSION_MINOR,EVF_VERSION_PATCH)
#else 
#define EVF_FULL_VERSION_LIST  EVF_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(EVF_VERSION_MAJOR,EVF_VERSION_MINOR,EVF_VERSION_PATCH)
#endif 


namespace xdaqevf
{
	const std::string package  =  "xdaqevf";
   	const std::string versions =  EVF_FULL_VERSION_LIST;
	const std::string summary = "Images package for event filter";
	const std::string description = "";
	const std::string authors = "Emilio Meschi";
	const std::string link = "http://";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
