// $Id: version.h,v 1.10 2009/02/20 14:02:17 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_collector2g_version_h_
#define _xmas_collector2g_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASCOLLECTOR2G_VERSION_MAJOR 2
#define XMASCOLLECTOR2G_VERSION_MINOR 2
#define XMASCOLLECTOR2G_VERSION_PATCH 0
// If any previous versions available E.g. #define XMASCOLLECTOR2G_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASCOLLECTOR2G_PREVIOUS_VERSIONS "2.0.0,2.0.1,2.0.2,2.1.0"


//
// Template macros
//
#define XMASCOLLECTOR2G_VERSION_CODE PACKAGE_VERSION_CODE(XMASCOLLECTOR2G_VERSION_MAJOR,XMASCOLLECTOR2G_VERSION_MINOR,XMASCOLLECTOR2G_VERSION_PATCH)
#ifndef XMASCOLLECTOR2G_PREVIOUS_VERSIONS
#define XMASCOLLECTOR2G_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASCOLLECTOR2G_VERSION_MAJOR,XMASCOLLECTOR2G_VERSION_MINOR,XMASCOLLECTOR2G_VERSION_PATCH)
#else 
#define XMASCOLLECTOR2G_FULL_VERSION_LIST  XMASCOLLECTOR2G_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASCOLLECTOR2G_VERSION_MAJOR,XMASCOLLECTOR2G_VERSION_MINOR,XMASCOLLECTOR2G_VERSION_PATCH)
#endif 

namespace xmascollector2g
{
	const std::string package  =  "xmascollector2g";
	const std::string versions =  XMASCOLLECTOR2G_FULL_VERSION_LIST;
	const std::string description = "Collectes a flashlist from multiple b2in-eventing services and reinjects it into a b2in-eventing service";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System collector for B2IN";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
