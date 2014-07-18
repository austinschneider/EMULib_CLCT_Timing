#ifndef _xdaq2rc_version_h_
#define _xdaq2rc_version_h_

#include "config/PackageInfo.h"

#define XDAQ2RC_VERSION_MAJOR 1
#define XDAQ2RC_VERSION_MINOR 9
#define XDAQ2RC_VERSION_PATCH 2
#define XDAQ2RC_PREVIOUS_VERSIONS "1.8.0,1.9.0,1.9.1"


#define XDAQ2RC_VERSION_CODE PACKAGE_VERSION_CODE(XDAQ2RC_VERSION_MAJOR,XDAQ2RC_VERSION_MINOR,XDAQ2RC_VERSION_PATCH)
#ifndef XDAQ2RC_PREVIOUS_VERSIONS
#define XDAQ2RC_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(XDAQ2RC_VERSION_MAJOR,XDAQ2RC_VERSION_MINOR,XDAQ2RC_VERSION_PATCH)
#else 
#define XDAQ2RC_FULL_VERSION_LIST  XDAQ2RC_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(XDAQ2RC_VERSION_MAJOR,XDAQ2RC_VERSION_MINOR,XDAQ2RC_VERSION_PATCH)
#endif 

namespace xdaq2rc
{
    const std::string package = "xdaq2rc";
    const std::string versions = XDAQ2RC_FULL_VERSION_LIST;
    const std::string version = PACKAGE_VERSION_STRING(RUBUILDEREVM_VERSION_MAJOR,RUBUILDEREVM_VERSION_MINOR,RUBUILDEREVM_VERSION_PATCH);
    const std::string description = "XDAQ to run-control communications library";
    const std::string summary = "XDAQ to run-control communications library";
    const std::string authors = "Steven Murray, Remi Mommsen";
    const std::string link = "http://cms-ru-builder.web.cern.ch/cms-ru-builder";

    config::PackageInfo getPackageInfo();

    void checkPackageDependencies()
    throw (config::PackageInfo::VersionException);

    std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
