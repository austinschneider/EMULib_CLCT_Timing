// $Id: version.h,v 1.2 2008/07/18 15:26:42 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

//
// Version definition for RoundTrip
//
#ifndef _roundtrip_Version_H_
#define _roundtrip_Version_H_

#include "config/PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!

#define ROUNDTRIP_VERSION_MAJOR 1
#define ROUNDTRIP_VERSION_MINOR 9
#define ROUNDTRIP_VERSION_PATCH 0
// If any previous versions available E.g. #define ROUNDTRIP_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef ROUNDTRIP_PREVIOUS_VERSIONS 


//
// Template macros
//
#define ROUNDTRIP_VERSION_CODE PACKAGE_VERSION_CODE(ROUNDTRIP_VERSION_MAJOR,ROUNDTRIP_VERSION_MINOR,ROUNDTRIP_VERSION_PATCH)
#ifndef ROUNDTRIP_PREVIOUS_VERSIONS
#define ROUNDTRIP_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(ROUNDTRIP_VERSION_MAJOR,ROUNDTRIP_VERSION_MINOR,ROUNDTRIP_VERSION_PATCH)
#else 
#define ROUNDTRIP_FULL_VERSION_LIST  ROUNDTRIP_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(ROUNDTRIP_VERSION_MAJOR,ROUNDTRIP_VERSION_MINOR,ROUNDTRIP_VERSION_PATCH)
#endif 

namespace roundtrip 
{
	const std::string package  =  "roundtrip";
	const std::string versions =  ROUNDTRIP_FULL_VERSION_LIST;
	const std::string summary = "RoundTrip example (ping/pong sending and receiving with timing measurements)";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
