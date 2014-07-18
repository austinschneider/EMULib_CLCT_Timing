// $Id: version.h,v 1.20 2009/05/26 09:16:09 hsakulin Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini	
 *                                                                       *
 * JobControl is programmed by Alexander Oh				 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _jobcontrol_version_h_
#define _jobcontrol_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define JOBCONTROL_VERSION_MAJOR 1
#define JOBCONTROL_VERSION_MINOR 16
#define JOBCONTROL_VERSION_PATCH 2
#define JOBCONTROL_PREVIOUS_VERSIONS "1.10.1,1.10.2,1.10.3,1.11.0,1.11.1,1.11.2,1.11.3,1.12.0,1.12.1,1.12.2,1.13.0,1.14.0,1.14.1,1.14.2,1.14.3,1.15.0,1.15.1,1.16.0,1.16.1"


//
// Template macros
//
#define JOBCONTROL_VERSION_CODE PACKAGE_VERSION_CODE(JOBCONTROL_VERSION_MAJOR,JOBCONTROL_VERSION_MINOR,JOBCONTROL_VERSION_PATCH)
#ifndef JOBCONTROL_PREVIOUS_VERSIONS
#define JOBCONTROL_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(JOBCONTROL_VERSION_MAJOR,JOBCONTROL_VERSION_MINOR,JOBCONTROL_VERSION_PATCH)
#else 
#define JOBCONTROL_FULL_VERSION_LIST  JOBCONTROL_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(JOBCONTROL_VERSION_MAJOR,JOBCONTROL_VERSION_MINOR,JOBCONTROL_VERSION_PATCH)
#endif 
namespace jobcontrol
{
	const std::string package  =  "jobcontrol";
	const std::string versions =  JOBCONTROL_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Alexander Oh, Luciano Orsini, Johannes Guleber, Roland Moser, Andrea Petrucci";
	const std::string summary = "Controls execution of XDAQ services";
	const std::string link = "http://xdaqwiki.cern.ch/index.php/JobControl";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
