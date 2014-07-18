#ifndef _ttc_utils_LHCStatus_hh_
#define _ttc_utils_LHCStatus_hh_


#include <string>


namespace ttc
{

/**
 * Class holding static information about the list of LHC status.
 * Used by BOBR and RF2TTC.
 */
class LHCStatus
{
// types
public:

  enum Status
  {
    LHC_NOMODE = 1,
    LHC_SETUP = 2,
    LHC_INJPILOT = 3,
    LHC_INJINTR = 4,
    LHC_INJNOMN = 5,
    LHC_PRERAMP = 6,
    LHC_RAMP = 7,
    LHC_FLATTOP = 8,
    LHC_SQUEEZE = 9,
    LHC_ADJUST = 10,
    LHC_STABLE = 11,
    LHC_UNSTABLE = 12,
    LHC_BEAMDUMP = 13,
    LHC_RAMPDOWN = 14,
    LHC_RECOVERY = 15,
    LHC_INJDUMP = 16,
    LHC_CIRCDUMP = 17,
    LHC_ABORT = 18,
    LHC_CYCLING = 19,
    LHC_WBDUMP = 20,
    LHC_NOBEAM = 21
  };

// static
public:

  //! return given @param status as string
  static std::string GetVerboseStatus(Status status);

  //! returns true iff given @param status is defined by BST language
  static bool IsDefinedMode(Status status);

};

}


#endif
