/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2008/05/26 09:43:48 $
 *
 *
 **/


#ifndef _d2sgtpecontroller_version_h_
#define _d2sgtpecontroller_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define D2SGTPECONTROLLER_VERSION_MAJOR 1
#define D2SGTPECONTROLLER_VERSION_MINOR 10
#define D2SGTPECONTROLLER_VERSION_PATCH 1
// If any previous versions available E.g. #define D2SGTPECONTROLLER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef D2SGTPECONTROLLER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define D2SGTPECONTROLLER_VERSION_CODE PACKAGE_VERSION_CODE(D2SGTPECONTROLLER_VERSION_MAJOR,D2SGTPECONTROLLER_VERSION_MINOR,D2SGTPECONTROLLER_VERSION_PATCH)
#ifndef D2SGTPECONTROLLER_PREVIOUS_VERSIONS
#define D2SGTPECONTROLLER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(D2SGTPECONTROLLER_VERSION_MAJOR,D2SGTPECONTROLLER_VERSION_MINOR,D2SGTPECONTROLLER_VERSION_PATCH)
#else 
#define D2SGTPECONTROLLER_FULL_VERSION_LIST  D2SGTPECONTROLLER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(D2SGTPECONTROLLER_VERSION_MAJOR,D2SGTPECONTROLLER_VERSION_MINOR,D2SGTPECONTROLLER_VERSION_PATCH)
#endif 
namespace d2sgtpecontroller
{
	const std::string package  =  "d2sgtpecontroller";
	const std::string versions =  D2SGTPECONTROLLER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "d2sgtpecontroller";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
