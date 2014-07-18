// $Id: version.h,v 1.4 2008/07/18 15:26:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_version_h_
#define _i2o_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define I2O_VERSION_MAJOR 3
#define I2O_VERSION_MINOR 10
#define I2O_VERSION_PATCH 0
// If any previous versions available E.g. #define I2O_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef I2O_PREVIOUS_VERSIONS 


//
// Template macros
//
#define I2O_VERSION_CODE PACKAGE_VERSION_CODE(I2O_VERSION_MAJOR,I2O_VERSION_MINOR,I2O_VERSION_PATCH)
#ifndef I2O_PREVIOUS_VERSIONS
#define I2O_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(I2O_VERSION_MAJOR,I2O_VERSION_MINOR,I2O_VERSION_PATCH)
#else 
#define I2O_FULL_VERSION_LIST  I2O_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(I2O_VERSION_MAJOR,I2O_VERSION_MINOR,I2O_VERSION_PATCH)
#endif 


namespace i2o
{
	const std::string package  =  "i2o";
   	const std::string versions =  I2O_FULL_VERSION_LIST;
	const std::string summary = "I2O support interfaces";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/I2O_Messaging";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
