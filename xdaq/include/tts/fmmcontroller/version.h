/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.12 $
 *     $Date: 2008/10/06 06:59:05 $
 *
 *
 **/


#ifndef _ttsfmmcontroller_version_h_
#define _ttsfmmcontroller_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSFMMCONTROLLER_VERSION_MAJOR 2
#define TTSFMMCONTROLLER_VERSION_MINOR 0
#define TTSFMMCONTROLLER_VERSION_PATCH 1
// If any previous versions available E.g. #define TTSFMMCONTROLLER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSFMMCONTROLLER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSFMMCONTROLLER_VERSION_CODE PACKAGE_VERSION_CODE(TTSFMMCONTROLLER_VERSION_MAJOR,TTSFMMCONTROLLER_VERSION_MINOR,TTSFMMCONTROLLER_VERSION_PATCH)
#ifndef TTSFMMCONTROLLER_PREVIOUS_VERSIONS
#define TTSFMMCONTROLLER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSFMMCONTROLLER_VERSION_MAJOR,TTSFMMCONTROLLER_VERSION_MINOR,TTSFMMCONTROLLER_VERSION_PATCH)
#else 
#define TTSFMMCONTROLLER_FULL_VERSION_LIST  TTSFMMCONTROLLER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSFMMCONTROLLER_VERSION_MAJOR,TTSFMMCONTROLLER_VERSION_MINOR,TTSFMMCONTROLLER_VERSION_PATCH)
#endif 
namespace ttsfmmcontroller
{
	const std::string package  =  "ttsfmmcontroller";
	const std::string versions =  TTSFMMCONTROLLER_FULL_VERSION_LIST;
	const std::string description = "This package provides the FMM Controller application that controls Fast Merging Modules (FMMs)";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsfmmcontroller";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
