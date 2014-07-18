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


#ifndef _ttsfmmtd_version_h_
#define _ttsfmmtd_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSFMMTD_VERSION_MAJOR 1
#define TTSFMMTD_VERSION_MINOR 9
#define TTSFMMTD_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSFMMTD_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSFMMTD_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSFMMTD_VERSION_CODE PACKAGE_VERSION_CODE(TTSFMMTD_VERSION_MAJOR,TTSFMMTD_VERSION_MINOR,TTSFMMTD_VERSION_PATCH)
#ifndef TTSFMMTD_PREVIOUS_VERSIONS
#define TTSFMMTD_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSFMMTD_VERSION_MAJOR,TTSFMMTD_VERSION_MINOR,TTSFMMTD_VERSION_PATCH)
#else 
#define TTSFMMTD_FULL_VERSION_LIST  TTSFMMTD_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSFMMTD_VERSION_MAJOR,TTSFMMTD_VERSION_MINOR,TTSFMMTD_VERSION_PATCH)
#endif 
namespace ttsfmmtd
{
	const std::string package  =  "ttsfmmtd";
	const std::string versions =  TTSFMMTD_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsfmmtd";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
