#ifndef _ttc_ttcci_version_h_
#define _ttc_ttcci_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCTTCCI_VERSION_MAJOR 1
#define TTCTTCCI_VERSION_MINOR 6
#define TTCTTCCI_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCTTCCI_VERSION_CODE PACKAGE_VERSION_CODE(TTCTTCCI_VERSION_MAJOR,TTCTTCCI_VERSION_MINOR,TTCTTCCI_VERSION_PATCH)
#ifndef TTCTTCCI_PREVIOUS_VERSIONS
#define TTCTTCCI_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCTTCCI_VERSION_MAJOR,TTCTTCCI_VERSION_MINOR,TTCTTCCI_VERSION_PATCH)
#else
#define TTCTTCCI_FULL_VERSION_LIST  TTCTTCCI_VERSION_MAJOR "," TTCTTCCI_VERSION_MINOR "," TTCTTCCI_VERSION_PATCH
#endif

namespace ttcttcci {
  const std::string package  = "ttcttcci";
  const std::string versions = TTCTTCCI_FULL_VERSION_LIST;
  const std::string description = "XDAQ application for the TTCci control";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "XDAQ application for the TTCci control";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
