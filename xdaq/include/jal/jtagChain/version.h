/**
 *      @file version.h
 *
 *     @short Provides run-time versioning and dependency checking of libraries
 *
 *       @see ---
 *    @author Johannes Gutleber, Luciano Orsini, Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:51:47 $
 *
 *
 **/


#ifndef _jaljtagChain_version_h_
#define _jaljtagChain_version_h_

#include "config/PackageInfo.h"
// !!! Edit this line to reflect the latest package version !!!

#define JALJTAGCHAIN_VERSION_MAJOR 1
#define JALJTAGCHAIN_VERSION_MINOR 3
#define JALJTAGCHAIN_VERSION_PATCH 1
// If any previous versions available E.g. #define JALJTAGCHAIN_PREVIOUS_VERSIONS "3.8.0,3.8.1"
#undef JALJTAGCHAIN_PREVIOUS_VERSIONS 


//
// Template macros
//
#define JALJTAGCHAIN_VERSION_CODE PACKAGE_VERSION_CODE(JALJTAGCHAIN_VERSION_MAJOR,JALJTAGCHAIN_VERSION_MINOR,JALJTAGCHAIN_VERSION_PATCH)
#ifndef JALJTAGCHAIN_PREVIOUS_VERSIONS
#define JALJTAGCHAIN_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(JALJTAGCHAIN_VERSION_MAJOR,JALJTAGCHAIN_VERSION_MINOR,JALJTAGCHAIN_VERSION_PATCH)
#else 
#define JALJTAGCHAIN_FULL_VERSION_LIST  JALJTAGCHAIN_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(JALJTAGCHAIN_VERSION_MAJOR,JALJTAGCHAIN_VERSION_MINOR,JALJTAGCHAIN_VERSION_PATCH)
#endif 
namespace jaljtagChain
{
	const std::string package  =  "jaljtagChain";
	const std::string versions =  JALJTAGCHAIN_FULL_VERSION_LIST;
	const std::string description = "";
	const std::string authors = "Hannes Sakulin";
	const std::string summary = "jaljtagChain";
	const std::string link = "http://xdaqwiki.cern.ch/index.php";
	config::PackageInfo getPackageInfo();
	void checkPackageDependencies() throw (config::PackageInfo::VersionException);
	std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
