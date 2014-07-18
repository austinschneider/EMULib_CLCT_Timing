#ifndef _ttc_bobr_version_h_
#define _ttc_bobr_version_h_

#include "config/PackageInfo.h"

// !!! Edit these lines to reflect the latest package version !!!
#define TTCBOBR_VERSION_MAJOR 1
#define TTCBOBR_VERSION_MINOR 6
#define TTCBOBR_VERSION_PATCH 2
#undef TTCUTILS_PREVIOUS_VERSIONS

#define TTCBOBR_VERSION_CODE PACKAGE_VERSION_CODE(TTCBOBR_VERSION_MAJOR,TTCBOBR_VERSION_MINOR,TTCBOBR_VERSION_PATCH)
#ifndef TTCBOBR_PREVIOUS_VERSIONS
#define TTCBOBR_FULL_VERSION_LIST  PACKAGE_VERSION_STRING(TTCBOBR_VERSION_MAJOR,TTCBOBR_VERSION_MINOR,TTCBOBR_VERSION_PATCH)
#else
#define TTCBOBR_FULL_VERSION_LIST  TTCBOBR_VERSION_MAJOR "," TTCBOBR_VERSION_MINOR "," TTCBOBR_VERSION_PATCH
#endif

namespace ttcbobr {
  const std::string package  = "ttcbobr";
  const std::string versions = TTCBOBR_FULL_VERSION_LIST;
  const std::string description = "TTC BOBR package";
  const std::string authors = "CMS DAQ group";
  const std::string summary = "Package to control the Beam Observation system Beam synchronous timing Receiver";
  const std::string link = "https://twiki.cern.ch/twiki/bin/view/CMS/TTCManual";
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
}

#endif


