// $Id: version.h,v 1.18 2008/07/18 15:28:27 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_pulser_version_h_
#define _xmas_pulser_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XMASPULSER_VERSION_MAJOR 1
#define XMASPULSER_VERSION_MINOR 15
#define XMASPULSER_VERSION_PATCH 2
// If any previous versions available E.g. #define XMASPULSER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XMASPULSER_PREVIOUS_VERSIONS "1.15.0,1.15.1"


//
// Template macros
//
#define XMASPULSER_VERSION_CODE PACKAGE_VERSION_CODE(XMASPULSER_VERSION_MAJOR,XMASPULSER_VERSION_MINOR,XMASPULSER_VERSION_PATCH)
#ifndef XMASPULSER_PREVIOUS_VERSIONS
#define XMASPULSER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XMASPULSER_VERSION_MAJOR,XMASPULSER_VERSION_MINOR,XMASPULSER_VERSION_PATCH)
#else 
#define XMASPULSER_FULL_VERSION_LIST  XMASPULSER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XMASPULSER_VERSION_MAJOR,XMASPULSER_VERSION_MINOR,XMASPULSER_VERSION_PATCH)
#endif 

namespace xmaspulser
{
	const std::string package  =  "xmaspulser";
	const std::string versions =  XMASPULSER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "XDAQ Monitoring and Alarming System pulser";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
