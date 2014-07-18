// $Id: version.h,v 1.4 2008/07/22 13:01:46 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedemulator_version_h_
#define _fedemulator_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define FEDEMULATOR_VERSION_MAJOR 1
#define FEDEMULATOR_VERSION_MINOR 3
#define FEDEMULATOR_VERSION_PATCH 2
// If any previous versions available E.g. #define FEDEMULATOR_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define FEDEMULATOR_PREVIOUS_VERSIONS  "1.2.0"


//
// Template macros
//
#define FEDEMULATOR_VERSION_CODE PACKAGE_VERSION_CODE(FEDEMULATOR_VERSION_MAJOR,FEDEMULATOR_VERSION_MINOR,FEDEMULATOR_VERSION_PATCH)
#ifndef FEDEMULATOR_PREVIOUS_VERSIONS
#define FEDEMULATOR_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(FEDEMULATOR_VERSION_MAJOR,FEDEMULATOR_VERSION_MINOR,FEDEMULATOR_VERSION_PATCH)
#else 
#define FEDEMULATOR_FULL_VERSION_LIST  FEDEMULATOR_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(FEDEMULATOR_VERSION_MAJOR,FEDEMULATOR_VERSION_MINOR,FEDEMULATOR_VERSION_PATCH)
#endif 
namespace fedemulator
{
	const std::string package  =  "fedemulator";
	const std::string versions =  FEDEMULATOR_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "Emulates a FED with a GIII card.";
	const std::string link = "";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
