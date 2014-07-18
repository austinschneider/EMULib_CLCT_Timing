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


#ifndef _ttsfmmdbi_version_h_
#define _ttsfmmdbi_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSFMMDBI_VERSION_MAJOR 1
#define TTSFMMDBI_VERSION_MINOR 9
#define TTSFMMDBI_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSFMMDBI_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSFMMDBI_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSFMMDBI_VERSION_CODE PACKAGE_VERSION_CODE(TTSFMMDBI_VERSION_MAJOR,TTSFMMDBI_VERSION_MINOR,TTSFMMDBI_VERSION_PATCH)
#ifndef TTSFMMDBI_PREVIOUS_VERSIONS
#define TTSFMMDBI_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSFMMDBI_VERSION_MAJOR,TTSFMMDBI_VERSION_MINOR,TTSFMMDBI_VERSION_PATCH)
#else 
#define TTSFMMDBI_FULL_VERSION_LIST  TTSFMMDBI_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSFMMDBI_VERSION_MAJOR,TTSFMMDBI_VERSION_MINOR,TTSFMMDBI_VERSION_PATCH)
#endif 
namespace ttsfmmdbi
{
	const std::string package  =  "ttsfmmdbi";
	const std::string versions =  TTSFMMDBI_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsfmmdbi";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
