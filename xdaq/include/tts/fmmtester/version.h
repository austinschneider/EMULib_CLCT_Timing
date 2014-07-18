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


#ifndef _ttsfmmtester_version_h_
#define _ttsfmmtester_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSFMMTESTER_VERSION_MAJOR 2
#define TTSFMMTESTER_VERSION_MINOR 0
#define TTSFMMTESTER_VERSION_PATCH 0
// If any previous versions available E.g. #define TTSFMMTESTER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSFMMTESTER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSFMMTESTER_VERSION_CODE PACKAGE_VERSION_CODE(TTSFMMTESTER_VERSION_MAJOR,TTSFMMTESTER_VERSION_MINOR,TTSFMMTESTER_VERSION_PATCH)
#ifndef TTSFMMTESTER_PREVIOUS_VERSIONS
#define TTSFMMTESTER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSFMMTESTER_VERSION_MAJOR,TTSFMMTESTER_VERSION_MINOR,TTSFMMTESTER_VERSION_PATCH)
#else 
#define TTSFMMTESTER_FULL_VERSION_LIST  TTSFMMTESTER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSFMMTESTER_VERSION_MAJOR,TTSFMMTESTER_VERSION_MINOR,TTSFMMTESTER_VERSION_PATCH)
#endif 
namespace ttsfmmtester
{
	const std::string package  =  "ttsfmmtester";
	const std::string versions =  TTSFMMTESTER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsfmmtester";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
