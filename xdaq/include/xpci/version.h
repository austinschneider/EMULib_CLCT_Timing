// $Id: version.h,v 1.28 2008/10/13 12:58:57 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xpci_version_h_
#define _xpci_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XPCI_VERSION_MAJOR 1
#define XPCI_VERSION_MINOR 0
#define XPCI_VERSION_PATCH 0
// If any previous versions available E.g. #define XPCI_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef XPCI_PREVIOUS_VERSIONS


//
// Template macros
//
#define XPCI_VERSION_CODE PACKAGE_VERSION_CODE(XPCI_VERSION_MAJOR,XPCI_VERSION_MINOR,XPCI_VERSION_PATCH)
#ifndef XPCI_PREVIOUS_VERSIONS
#define XPCI_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XPCI_VERSION_MAJOR,XPCI_VERSION_MINOR,XPCI_VERSION_PATCH)
#else 
#define XPCI_FULL_VERSION_LIST  XPCI_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XPCI_VERSION_MAJOR,XPCI_VERSION_MINOR,XPCI_VERSION_PATCH)
#endif 

namespace xpci 
{
	const std::string package  =  "xpci";
   	const std::string versions =  XPCI_FULL_VERSION_LIST;
	const std::string summary = "Accessing PCI devices and memory on user space";
	const std::string description = "";
	const std::string authors = "Luciano Orsini, Andrea Petrucci";
	const std::string link = "http://xdaq.web.cern.ch";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
