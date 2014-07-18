// $Id: version.h,v 1.2 2008/07/18 15:26:40 gutleber Exp $

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
// Version definition for MStreamIO
//
#ifndef _mstreamio_Version_H_
#define _mstreamio_Version_H_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define MSTREAMIO_VERSION_MAJOR 1
#define MSTREAMIO_VERSION_MINOR 9
#define MSTREAMIO_VERSION_PATCH 0
// If any previous versions available E.g. #define MSTREAMIO_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef MSTREAMIO_PREVIOUS_VERSIONS 


//
// Template macros
//
#define MSTREAMIO_VERSION_CODE PACKAGE_VERSION_CODE(MSTREAMIO_VERSION_MAJOR,MSTREAMIO_VERSION_MINOR,MSTREAMIO_VERSION_PATCH)
#ifndef MSTREAMIO_PREVIOUS_VERSIONS
#define MSTREAMIO_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(MSTREAMIO_VERSION_MAJOR,MSTREAMIO_VERSION_MINOR,MSTREAMIO_VERSION_PATCH)
#else 
#define MSTREAMIO_FULL_VERSION_LIST  MSTREAMIO_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(MSTREAMIO_VERSION_MAJOR,MSTREAMIO_VERSION_MINOR,MSTREAMIO_VERSION_PATCH)
#endif 

namespace mstreamio 
{
	const std::string package  =  "mstreamio";
	const std::string versions =  MSTREAMIO_FULL_VERSION_LIST;
	const std::string summary = "Stream I/O example (1 to N point to point communication)";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
