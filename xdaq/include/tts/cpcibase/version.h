/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:46:36 $
 *
 *
 **/


#ifndef _ttscpcibase_version_h_
#define _ttscpcibase_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSCPCIBASE_VERSION_MAJOR 1
#define TTSCPCIBASE_VERSION_MINOR 9
#define TTSCPCIBASE_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSCPCIBASE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSCPCIBASE_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSCPCIBASE_VERSION_CODE PACKAGE_VERSION_CODE(TTSCPCIBASE_VERSION_MAJOR,TTSCPCIBASE_VERSION_MINOR,TTSCPCIBASE_VERSION_PATCH)
#ifndef TTSCPCIBASE_PREVIOUS_VERSIONS
#define TTSCPCIBASE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSCPCIBASE_VERSION_MAJOR,TTSCPCIBASE_VERSION_MINOR,TTSCPCIBASE_VERSION_PATCH)
#else 
#define TTSCPCIBASE_FULL_VERSION_LIST  TTSCPCIBASE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSCPCIBASE_VERSION_MAJOR,TTSCPCIBASE_VERSION_MINOR,TTSCPCIBASE_VERSION_PATCH)
#endif 
namespace ttscpcibase
{
	const std::string package  =  "ttscpcibase";
	const std::string versions =  TTSCPCIBASE_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttscpcibase";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
