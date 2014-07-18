/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:51:48 $
 *
 *
 **/


#ifndef _jaljtagController_version_h_
#define _jaljtagController_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define JALJTAGCONTROLLER_VERSION_MAJOR 1
#define JALJTAGCONTROLLER_VERSION_MINOR 3
#define JALJTAGCONTROLLER_VERSION_PATCH 1
// If any previous versions available E.g. #define JALJTAGCONTROLLER_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef JALJTAGCONTROLLER_PREVIOUS_VERSIONS 


//
// Template macros
//
#define JALJTAGCONTROLLER_VERSION_CODE PACKAGE_VERSION_CODE(JALJTAGCONTROLLER_VERSION_MAJOR,JALJTAGCONTROLLER_VERSION_MINOR,JALJTAGCONTROLLER_VERSION_PATCH)
#ifndef JALJTAGCONTROLLER_PREVIOUS_VERSIONS
#define JALJTAGCONTROLLER_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(JALJTAGCONTROLLER_VERSION_MAJOR,JALJTAGCONTROLLER_VERSION_MINOR,JALJTAGCONTROLLER_VERSION_PATCH)
#else 
#define JALJTAGCONTROLLER_FULL_VERSION_LIST  JALJTAGCONTROLLER_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(JALJTAGCONTROLLER_VERSION_MAJOR,JALJTAGCONTROLLER_VERSION_MINOR,JALJTAGCONTROLLER_VERSION_PATCH)
#endif 
namespace jaljtagController
{
	const std::string package  =  "jaljtagController";
	const std::string versions =  JALJTAGCONTROLLER_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "jaljtagController";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
