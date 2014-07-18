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


#ifndef _ttsipcutils_version_h_
#define _ttsipcutils_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSIPCUTILS_VERSION_MAJOR 1
#define TTSIPCUTILS_VERSION_MINOR 10
#define TTSIPCUTILS_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSIPCUTILS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSIPCUTILS_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSIPCUTILS_VERSION_CODE PACKAGE_VERSION_CODE(TTSIPCUTILS_VERSION_MAJOR,TTSIPCUTILS_VERSION_MINOR,TTSIPCUTILS_VERSION_PATCH)
#ifndef TTSIPCUTILS_PREVIOUS_VERSIONS
#define TTSIPCUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSIPCUTILS_VERSION_MAJOR,TTSIPCUTILS_VERSION_MINOR,TTSIPCUTILS_VERSION_PATCH)
#else 
#define TTSIPCUTILS_FULL_VERSION_LIST  TTSIPCUTILS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSIPCUTILS_VERSION_MAJOR,TTSIPCUTILS_VERSION_MINOR,TTSIPCUTILS_VERSION_PATCH)
#endif 
namespace ttsipcutils
{
	const std::string package  =  "ttsipcutils";
	const std::string versions =  TTSIPCUTILS_FULL_VERSION_LIST;
	const std::string description = "Provides a semaphore array for inter-process communication";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsipcutils";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
