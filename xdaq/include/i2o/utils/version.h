// $Id: version.h,v 1.4 2008/07/18 15:26:51 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_utils_version_h_
#define _i2o_utils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define I2OUTILS_VERSION_MAJOR 3
#define I2OUTILS_VERSION_MINOR 9
#define I2OUTILS_VERSION_PATCH 0
// If any previous versions available E.g. #define I2OUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef I2OUTILS_PREVIOUS_VERSIONS 


//
// Template macros
//
#define I2OUTILS_VERSION_CODE PACKAGE_VERSION_CODE(I2OUTILS_VERSION_MAJOR,I2OUTILS_VERSION_MINOR,I2OUTILS_VERSION_PATCH)
#ifndef I2OUTILS_PREVIOUS_VERSIONS
#define I2OUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(I2OUTILS_VERSION_MAJOR,I2OUTILS_VERSION_MINOR,I2OUTILS_VERSION_PATCH)
#else 
#define I2OUTILS_FULL_VERSION_LIST  I2OUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(I2OUTILS_VERSION_MAJOR,I2OUTILS_VERSION_MINOR,I2OUTILS_VERSION_PATCH)
#endif 

namespace i2outils 
{
	const std::string package  =  "i2outils";
   	const std::string versions =  I2OUTILS_FULL_VERSION_LIST;
	const std::string summary = "Utility package for sending binary I2O messages";
	const std::string description = "";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/I2O_Messaging";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
