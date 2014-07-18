#ifndef _ttc_rf2ttc_version_h_
#define _ttc_rf2ttc_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCRF2TTC_VERSION_MAJOR 1
#define TTCRF2TTC_VERSION_MINOR 6
#define TTCRF2TTC_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCRF2TTC_VERSION_CODE PACKAGE_VERSION_CODE(TTCRF2TTC_VERSION_MAJOR,TTCRF2TTC_VERSION_MINOR,TTCRF2TTC_VERSION_PATCH)
#ifndef TTCRF2TTC_PREVIOUS_VERSIONS
#define TTCRF2TTC_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCRF2TTC_VERSION_MAJOR,TTCRF2TTC_VERSION_MINOR,TTCRF2TTC_VERSION_PATCH)
#else
#define TTCRF2TTC_FULL_VERSION_LIST  TTCRF2TTC_VERSION_MAJOR "," TTCRF2TTC_VERSION_MINOR "," TTCRF2TTC_VERSION_PATCH
#endif

namespace ttcrf2ttc {
  const std::string package  = "ttcrf2ttc";
  const std::string versions = TTCRF2TTC_FULL_VERSION_LIST;
  const std::string description = "Radio-Frequency (group) to Trigger Timing and Control format conversion XDAQ application";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "TTC RF2TTC XDAQ Application";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
