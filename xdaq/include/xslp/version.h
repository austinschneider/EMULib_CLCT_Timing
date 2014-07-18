// $Id: version.h,v 1.3 2008/11/10 09:53:31 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xslp_version_h_
#define _xslp_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define XSLP_VERSION_MAJOR 1
#define XSLP_VERSION_MINOR 10
#define XSLP_VERSION_PATCH 1
// If any previous versions available E.g. #define XSLP_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#define XSLP_PREVIOUS_VERSIONS "1.10.0"


//
// Template macros
//
#define XSLP_VERSION_CODE PACKAGE_VERSION_CODE(XSLP_VERSION_MAJOR,XSLP_VERSION_MINOR,XSLP_VERSION_PATCH)
#ifndef XSLP_PREVIOUS_VERSIONS
#define XSLP_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XSLP_VERSION_MAJOR,XSLP_VERSION_MINOR,XSLP_VERSION_PATCH)
#else 
#define XSLP_FULL_VERSION_LIST  XSLP_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XSLP_VERSION_MAJOR,XSLP_VERSION_MINOR,XSLP_VERSION_PATCH)
#endif 

namespace xslp 
{
    const std::string package  =  "xslp";
    const std::string versions =  XSLP_FULL_VERSION_LIST;
    const std::string description = "";
    const std::string authors = "Johannes Gutleber, Luciano Orsini";
    const std::string summary = "SLP based discovery service package";
    const std::string link = "http://xdaqwiki.cern.ch/index.php/Power_Pack";
    config::PackageInfo getPackageInfo();
    void checkPackageDependencies() throw (config::PackageInfo::VersionException);
    std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
