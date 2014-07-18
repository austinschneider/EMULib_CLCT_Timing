#ifndef _ttc_utils_version_h_
#define _ttc_utils_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCUTILS_VERSION_MAJOR 1
#define TTCUTILS_VERSION_MINOR 6
#define TTCUTILS_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCUTILS_VERSION_CODE PACKAGE_VERSION_CODE(TTCUTILS_VERSION_MAJOR,TTCUTILS_VERSION_MINOR,TTCUTILS_VERSION_PATCH)
#ifndef TTCUTILS_PREVIOUS_VERSIONS
#define TTCUTILS_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCUTILS_VERSION_MAJOR,TTCUTILS_VERSION_MINOR,TTCUTILS_VERSION_PATCH)
#else
#define TTCUTILS_FULL_VERSION_LIST  TTCUTILS_VERSION_MAJOR "," TTCUTILS_VERSION_MINOR "," TTCUTILS_VERSION_PATCH
#endif

namespace ttcutils {
  const std::string package  = "ttcutils";
  const std::string versions = TTCUTILS_FULL_VERSION_LIST;
  const std::string description = "Library of various generic utilities for TTC";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "Library of various generic utilities for TTC";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
