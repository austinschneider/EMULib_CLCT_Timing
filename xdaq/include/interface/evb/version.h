// $Id: version.h,v 1.2 2007/04/04 08:11:55 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _interface_evb_version_h_
#define _interface_evb_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define INTERFACEEVB_VERSION_MAJOR 1
#define INTERFACEEVB_VERSION_MINOR 9
#define INTERFACEEVB_VERSION_PATCH 0
// If any previous versions available E.g. #define INTERFACEEVB_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define INTERFACEEVB_PREVIOUS_VERSIONS "1.8.0"


//
// Template macros
//
#define INTERFACEEVB_VERSION_CODE PACKAGE_VERSION_CODE(INTERFACEEVB_VERSION_MAJOR,INTERFACEEVB_VERSION_MINOR,INTERFACEEVB_VERSION_PATCH)
#ifndef INTERFACEEVB_PREVIOUS_VERSIONS
#define INTERFACEEVB_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(INTERFACEEVB_VERSION_MAJOR,INTERFACEEVB_VERSION_MINOR,INTERFACEEVB_VERSION_PATCH)
#else 
#define INTERFACEEVB_FULL_VERSION_LIST  INTERFACEEVB_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(INTERFACEEVB_VERSION_MAJOR,INTERFACEEVB_VERSION_MINOR,INTERFACEEVB_VERSION_PATCH)
#endif 


namespace interfaceevb 
{
	const std::string package  =  "interfaceevb";
   	const std::string versions =  INTERFACEEVB_FULL_VERSION_LIST;
	const std::string summary = "The event builder I2O message format";
	const std::string description = "The event builder header files are only required for development purposes";
	const std::string authors = "Steven Murray";
	const std::string link = "http://cms-ru-builder.web.cern.ch/cms-ru-builder";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
