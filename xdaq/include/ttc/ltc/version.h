#ifndef _ttc_ltc_version_h_
#define _ttc_ltc_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCLTC_VERSION_MAJOR 1
#define TTCLTC_VERSION_MINOR 6
#define TTCLTC_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCLTC_VERSION_CODE PACKAGE_VERSION_CODE(TTCLTC_VERSION_MAJOR,TTCLTC_VERSION_MINOR,TTCLTC_VERSION_PATCH)
#ifndef TTCLTC_PREVIOUS_VERSIONS
#define TTCLTC_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCLTC_VERSION_MAJOR,TTCLTC_VERSION_MINOR,TTCLTC_VERSION_PATCH)
#else
#define TTCLTC_FULL_VERSION_LIST  TTCLTC_VERSION_MAJOR "," TTCLTC_VERSION_MINOR "," TTCLTC_VERSION_PATCH
#endif

namespace ttcltc {
  const std::string package  = "ttcltc";
  const std::string versions = TTCLTC_FULL_VERSION_LIST;
  const std::string description = "Local Trigger Control XDAQ application";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "LTC XDAQ application";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
