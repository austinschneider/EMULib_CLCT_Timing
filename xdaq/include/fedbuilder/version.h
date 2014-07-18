// $Id: version.h,v 1.43 2009/05/28 12:46:19 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedbuilder_version_h_
#define _fedbuilder_version_h_

#include "config/PackageInfo.h"

// !!! Edit this line to reflect the latest package version !!!
#define FEDBUILDER_VERSION_MAJOR 1
#define FEDBUILDER_VERSION_MINOR 25
#define FEDBUILDER_VERSION_PATCH 2
// If any previous versions available E.g. #define FEDBUILDER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
//#undef FEDBUILDER_PREVIOUS_VERSIONS
#define FEDBUILDER_PREVIOUS_VERSIONS "1.19.0,1.19.1,1.21.0,1.21.1"

//
// Template macros
//
#define FEDBUILDER_VERSION_CODE PACKAGE_VERSION_CODE(FEDBUILDER_VERSION_MAJOR,FEDBUILDER_VERSION_MINOR,FEDBUILDER_VERSION_PATCH)
#ifndef FEDBUILDER_PREVIOUS_VERSIONS
#define FEDBUILDER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(FEDBUILDER_VERSION_MAJOR,FEDBUILDER_VERSION_MINOR,FEDBUILDER_VERSION_PATCH)
#else 
#define FEDBUILDER_FULL_VERSION_LIST  FEDBUILDER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(FEDBUILDER_VERSION_MAJOR,FEDBUILDER_VERSION_MINOR,FEDBUILDER_VERSION_PATCH)
#endif 

namespace infospacebrowser
{
	const std::string package  =  "infospacebrowser";
	const std::string versions =  FEDBUILDER_FULL_VERSION_LIST;
	const std::string description = "Monitoring of the Infospaces.";
	const std::string authors = "Christoph Schwick";
	const std::string summary = "Browses Infospaces for registered applications";
	const std::string link = "http://makerpmhappy";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

namespace fbo
{
	const std::string package  =  "fbo";
	const std::string versions =  FEDBUILDER_FULL_VERSION_LIST;
	const std::string description = "Output of the FED Builder.";
	const std::string authors = "Christoph Schwick";
	const std::string summary = "FED Builder application (output)";
	const std::string link = "http://makerpmhappy";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

namespace frlcontroller
{
	const std::string package  =  "frlcontroller";
	const std::string versions =  FEDBUILDER_FULL_VERSION_LIST;
	const std::string description = "Controller software for the FRL and input of the FED Builder.";
	const std::string authors = "Johannes Gutleber, Luciano Orsini";
	const std::string summary = "FED Builder application (controller)";
	const std::string link = "http://xdaq.cern.ch";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

namespace fedbtools
{
	const std::string package  =  "fedbtools";
	const std::string versions =  FEDBUILDER_FULL_VERSION_LIST;
	const std::string description = "Common classes for fedbuilder software.";
	const std::string authors = "Christoph Schwick";
	const std::string summary = "FED Builder common tools";
	const std::string link = "http://makerpmhappy";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

namespace fedbuilder
{
	const std::string package  =  "fedbuilder";
	const std::string versions =  FEDBUILDER_FULL_VERSION_LIST;
	const std::string description = "Contains the frlcontroller, the fbo and a tools library.";
	const std::string authors = "Christoph Schwick";
	const std::string summary = "CMS Fed-builder software.";
	const std::string link = "http://makerpmhappy";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
