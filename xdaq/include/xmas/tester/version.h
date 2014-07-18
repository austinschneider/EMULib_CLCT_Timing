// $Id: version.h,v 1.8 2008/07/18 15:28:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_tester_version_h_
#define _xmas_tester_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASTESTER_VERSION_MAJOR 1
#define XMASTESTER_VERSION_MINOR 11 
#define XMASTESTER_VERSION_PATCH 2
// If any previous versions available E.g. #define XMASTESTER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASTESTER_PREVIOUS_VERSIONS "1.11.1"


//
// Template macros
//
#define XMASTESTER_VERSION_CODE PACKAGE_VERSION_CODE(XMASTESTER_VERSION_MAJOR,XMASTESTER_VERSION_MINOR,XMASTESTER_VERSION_PATCH)
#ifndef XMASTESTER_PREVIOUS_VERSIONS
#define XMASTESTER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASTESTER_VERSION_MAJOR,XMASTESTER_VERSION_MINOR,XMASTESTER_VERSION_PATCH)
#else 
#define XMASTESTER_FULL_VERSION_LIST  XMASTESTER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASTESTER_VERSION_MAJOR,XMASTESTER_VERSION_MINOR,XMASTESTER_VERSION_PATCH)
#endif 

namespace xmastester
{
	const std::string package  =  "xmastester";
	const std::string versions =  XMASTESTER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System tester";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
