// $Id: version.h,v 1.3 2007/11/23 10:40:08 lorsini Exp $

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

#define INTERFACESHARED_VERSION_MAJOR 1
#define INTERFACESHARED_VERSION_MINOR 12
#define INTERFACESHARED_VERSION_PATCH 0
// If any previous versions available E.g. #define INTERFACESHARED_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef INTERFACESHARED_PREVIOUS_VERSIONS


//
// Template macros
//
#define INTERFACESHARED_VERSION_CODE PACKAGE_VERSION_CODE(INTERFACESHARED_VERSION_MAJOR,INTERFACESHARED_VERSION_MINOR,INTERFACESHARED_VERSION_PATCH)
#ifndef INTERFACESHARED_PREVIOUS_VERSIONS
#define INTERFACESHARED_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(INTERFACESHARED_VERSION_MAJOR,INTERFACESHARED_VERSION_MINOR,INTERFACESHARED_VERSION_PATCH)
#else 
#define INTERFACESHARED_FULL_VERSION_LIST  INTERFACESHARED_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(INTERFACESHARED_VERSION_MAJOR,INTERFACESHARED_VERSION_MINOR,INTERFACESHARED_VERSION_PATCH)
#endif 


namespace interfaceshared
{
	const std::string package  =  "interfaceshared";
   	const std::string versions =  INTERFACESHARED_FULL_VERSION_LIST;
	const std::string summary = "Header files shared by event builder and FED builder";
	const std::string description = "The header files are only required for development purposes";
	const std::string authors = "Steven Murray";
	const std::string link = "http://cms-ru-builder.web.cern.ch/cms-ru-builder";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
