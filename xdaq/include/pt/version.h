// $Id: version.h,v 1.4 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_version_h_
#define _pt_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define PT_VERSION_MAJOR 3
#define PT_VERSION_MINOR 10
#define PT_VERSION_PATCH 0
// If any previous versions available E.g. #define PT_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef PT_PREVIOUS_VERSIONS


//
// Template macros
//
#define PT_VERSION_CODE PACKAGE_VERSION_CODE(PT_VERSION_MAJOR,PT_VERSION_MINOR,PT_VERSION_PATCH)
#ifndef PT_PREVIOUS_VERSIONS
#define PT_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(PT_VERSION_MAJOR,PT_VERSION_MINOR,PT_VERSION_PATCH)
#else 
#define PT_FULL_VERSION_LIST  PT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(PT_VERSION_MAJOR,PT_VERSION_MINOR,PT_VERSION_PATCH)
#endif 

namespace pt 
{
	const std::string package  =  "pt";
   	const std::string versions =  PT_FULL_VERSION_LIST;
	const std::string summary = "Peer Transport management package";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/pt";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
