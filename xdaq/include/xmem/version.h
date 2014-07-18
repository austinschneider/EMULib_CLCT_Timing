// $Id: version.h,v 1.4 2008/07/18 15:28:38 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmem_version_h_
#define _xmem_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMEM_VERSION_MAJOR 1
#define XMEM_VERSION_MINOR 9
#define XMEM_VERSION_PATCH 0
// If any previous versions available E.g. #define XMEM_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XMEM_PREVIOUS_VERSIONS 


//
// Template macros
//
#define XMEM_VERSION_CODE PACKAGE_VERSION_CODE(XMEM_VERSION_MAJOR,XMEM_VERSION_MINOR,XMEM_VERSION_PATCH)
#ifndef XMEM_PREVIOUS_VERSIONS
#define XMEM_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMEM_VERSION_MAJOR,XMEM_VERSION_MINOR,XMEM_VERSION_PATCH)
#else 
#define XMEM_FULL_VERSION_LIST  XMEM_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMEM_VERSION_MAJOR,XMEM_VERSION_MINOR,XMEM_VERSION_PATCH)
#endif 

namespace xmem 
{
	const std::string package  =  "xmem";
   	const std::string versions =  XMEM_FULL_VERSION_LIST;
	const std::string summary = "XDAQ memory pools analyzer";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/xdaq";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
