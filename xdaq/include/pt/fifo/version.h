// $Id: version.h,v 1.4 2008/07/18 15:27:14 gutleber Exp $

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
// Version definition for FIFO peer transport
//
#ifndef _pt_fifo_h_
#define _pt_fifo_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define PTFIFO_VERSION_MAJOR 4
#define PTFIFO_VERSION_MINOR 1
#define PTFIFO_VERSION_PATCH 1
// If any previous versions available E.g. #define PTFIFO_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define PTFIFO_PREVIOUS_VERSIONS "4.1.0"


//
// Template macros
//
#define PTFIFO_VERSION_CODE PACKAGE_VERSION_CODE(PTFIFO_VERSION_MAJOR,PTFIFO_VERSION_MINOR,PTFIFO_VERSION_PATCH)
#ifndef PTFIFO_PREVIOUS_VERSIONS
#define PTFIFO_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(PTFIFO_VERSION_MAJOR,PTFIFO_VERSION_MINOR,PTFIFO_VERSION_PATCH)
#else 
#define PTFIFO_FULL_VERSION_LIST  PTFIFO_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(PTFIFO_VERSION_MAJOR,PTFIFO_VERSION_MINOR,PTFIFO_VERSION_PATCH)
#endif 

namespace ptfifo
{
	const std::string package  =  "ptfifo";
	const std::string versions =  PTFIFO_FULL_VERSION_LIST;
	const std::string summary = "FIFO peer transport for process internal communication";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Core_Tools";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
