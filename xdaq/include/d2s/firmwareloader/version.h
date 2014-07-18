/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.3 $
 *     $Date: 2008/05/14 08:26:21 $
 *
 *
 **/


#ifndef _d2sfirmwareloader_version_h_
#define _d2sfirmwareloader_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define D2SFIRMWARELOADER_VERSION_MAJOR 1
#define D2SFIRMWARELOADER_VERSION_MINOR 14
#define D2SFIRMWARELOADER_VERSION_PATCH 0
// If any previous versions available E.g. #define D2SFIRMWARELOADER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef D2SFIRMWARELOADER_PREVIOUS_VERSIONS


//
// Template macros
//
#define D2SFIRMWARELOADER_VERSION_CODE PACKAGE_VERSION_CODE(D2SFIRMWARELOADER_VERSION_MAJOR,D2SFIRMWARELOADER_VERSION_MINOR,D2SFIRMWARELOADER_VERSION_PATCH)
#ifndef D2SFIRMWARELOADER_PREVIOUS_VERSIONS
#define D2SFIRMWARELOADER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(D2SFIRMWARELOADER_VERSION_MAJOR,D2SFIRMWARELOADER_VERSION_MINOR,D2SFIRMWARELOADER_VERSION_PATCH)
#else 
#define D2SFIRMWARELOADER_FULL_VERSION_LIST  D2SFIRMWARELOADER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(D2SFIRMWARELOADER_VERSION_MAJOR,D2SFIRMWARELOADER_VERSION_MINOR,D2SFIRMWARELOADER_VERSION_PATCH)
#endif 
namespace d2sfirmwareloader
{
	const std::string package  =  "d2sfirmwareloader";
	const std::string versions =  D2SFIRMWARELOADER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "d2sfirmwareloader";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
