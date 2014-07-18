#ifndef _ttc_monitoring_version_h_
#define _ttc_monitoring_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCMONITORING_VERSION_MAJOR 1
#define TTCMONITORING_VERSION_MINOR 6
#define TTCMONITORING_VERSION_PATCH 2
#undef TTCMONITORING_PREVIOUS_VERSIONS

#define TTCMONITORING_VERSION_CODE PACKAGE_VERSION_CODE(TTCMONITORING_VERSION_MAJOR,TTCMONITORING_VERSION_MINOR,TTCMONITORING_VERSION_PATCH)
#ifndef TTCMONITORING_PREVIOUS_VERSIONS
#define TTCMONITORING_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCMONITORING_VERSION_MAJOR,TTCMONITORING_VERSION_MINOR,TTCMONITORING_VERSION_PATCH)
#else
#define TTCMONITORING_FULL_VERSION_LIST  TTCMONITORING_VERSION_MAJOR "," TTCMONITORING_VERSION_MINOR "," TTCMONITORING_VERSION_PATCH
#endif

namespace ttcmonitoring {
  const std::string package  = "ttcmonitoring";
  const std::string versions = TTCMONITORING_FULL_VERSION_LIST;
  const std::string description = "Library of monitoring classes for TTC";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "Library of monitoring classes for TTC";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
