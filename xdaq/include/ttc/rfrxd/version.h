#ifndef _ttc_rfrxd_version_h_
#define _ttc_rfrxd_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCRFRXD_VERSION_MAJOR 1
#define TTCRFRXD_VERSION_MINOR 6
#define TTCRFRXD_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCRFRXD_VERSION_CODE PACKAGE_VERSION_CODE(TTCRFRXD_VERSION_MAJOR,TTCRFRXD_VERSION_MINOR,TTCRFRXD_VERSION_PATCH)
#ifndef TTCRFRXD_PREVIOUS_VERSIONS
#define TTCRFRXD_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCRFRXD_VERSION_MAJOR,TTCRFRXD_VERSION_MINOR,TTCRFRXD_VERSION_PATCH)
#else
#define TTCRFRXD_FULL_VERSION_LIST  TTCRFRXD_VERSION_MAJOR "," TTCRFRXD_VERSION_MINOR "," TTCRFRXD_VERSION_PATCH
#endif

namespace ttcrfrxd {
  const std::string package  = "ttcrfrxd";
  const std::string versions = TTCRFRXD_FULL_VERSION_LIST;
  const std::string description = "XDAQ application to control the Radio-frequency Receiver (digital version)";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "TTC RFRXD XDAQ application";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif
