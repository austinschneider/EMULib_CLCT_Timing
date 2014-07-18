// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors:  L. Orsini							 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedsteramer_version_h_
#define _fedstreamer_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define FEDSTREAMER_VERSION_MAJOR 2
#define FEDSTREAMER_VERSION_MINOR 1
#define FEDSTREAMER_VERSION_PATCH 0
// If any previous versions available E.g. #define PHEAPS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define PHEAPS_PREVIOUS_VERSIONS "2.0.0"

//
// Template macros
//
#define FEDSTREAMER_VERSION_CODE PACKAGE_VERSION_CODE(FEDSTREAMER_VERSION_MAJOR,FEDSTREAMER_VERSION_MINOR,FEDSTREAMER_VERSION_PATCH)
#ifndef FEDSTREAMER_PREVIOUS_VERSIONS
#define FEDSTREAMER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(FEDSTREAMER_VERSION_MAJOR,FEDSTREAMER_VERSION_MINOR,FEDSTREAMER_VERSION_PATCH)
#else 
#define FEDSTREAMER_FULL_VERSION_LIST  FEDSTREAMER_PREVIOUS_VERSIONS "," FEDSTREAMER_VERSION_STRING(FEDSTREAMER_VERSION_MAJOR,FEDSTREAMER_VERSION_MINOR,FEDSTREAMER_VERSION_PATCH)
#endif 
namespace fedstreamer
{
	const std::string package  =  "fedstreamer";
	const std::string versions =  FEDSTREAMER_FULL_VERSION_LIST;
	const std::string summary = " Generic-III PCI card delivered by the CERN CMD group";
	const std::string description = "The fedstreamer application can be used to read data from the Generic-III PCI card delivered by the CERN CMD group. The application is kept as simple as possible, yet offers as much configuration options as are necessary to achieve good data transmission over the SLink 64 interface implemented by the PCI card.";
	const std::string authors = "Luciano Orsini";
	const std::string link = "https://twiki.cern.ch/twiki/bin/view/XdaqWiki/Fedstreamer";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
