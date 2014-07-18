/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/27 08:46:36 $
 *
 *
 **/


#ifndef _ttsatts_version_h_
#define _ttsatts_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define TTSATTS_VERSION_MAJOR 1
#define TTSATTS_VERSION_MINOR 9
#define TTSATTS_VERSION_PATCH 1
// If any previous versions available E.g. #define TTSATTS_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef TTSATTS_PREVIOUS_VERSIONS 


//
// Template macros
//
#define TTSATTS_VERSION_CODE PACKAGE_VERSION_CODE(TTSATTS_VERSION_MAJOR,TTSATTS_VERSION_MINOR,TTSATTS_VERSION_PATCH)
#ifndef TTSATTS_PREVIOUS_VERSIONS
#define TTSATTS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTSATTS_VERSION_MAJOR,TTSATTS_VERSION_MINOR,TTSATTS_VERSION_PATCH)
#else 
#define TTSATTS_FULL_VERSION_LIST  TTSATTS_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(TTSATTS_VERSION_MAJOR,TTSATTS_VERSION_MINOR,TTSATTS_VERSION_PATCH)
#endif 
namespace ttsatts
{
	const std::string package  =  "ttsatts";
	const std::string versions =  TTSATTS_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "ttsatts";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
