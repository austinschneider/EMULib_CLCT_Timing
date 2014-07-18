/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:46:37 $
 *
 *
 **/


#ifndef _ttsttsbase_version_h_
#define _ttsttsbase_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSTTSBASE_VERSION_MAJOR 1
#define TTSTTSBASE_VERSION_MINOR 9
#define TTSTTSBASE_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSTTSBASE_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSTTSBASE_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSTTSBASE_VERSION_CODE PACKAGE_VERSION_CODE(TTSTTSBASE_VERSION_MAJOR,TTSTTSBASE_VERSION_MINOR,TTSTTSBASE_VERSION_PATCH)
#ifndef TTSTTSBASE_PREVIOUS_VERSIONS
#define TTSTTSBASE_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSTTSBASE_VERSION_MAJOR,TTSTTSBASE_VERSION_MINOR,TTSTTSBASE_VERSION_PATCH)
#else 
#define TTSTTSBASE_FULL_VERSION_LIST  TTSTTSBASE_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSTTSBASE_VERSION_MAJOR,TTSTTSBASE_VERSION_MINOR,TTSTTSBASE_VERSION_PATCH)
#endif 
namespace ttsttsbase
{
	const std::string package  =  "ttsttsbase";
	const std::string versions =  TTSTTSBASE_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsttsbase";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
