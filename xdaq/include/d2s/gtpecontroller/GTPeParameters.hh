#ifndef GTPEPARAMETERS_H
#define GTPEPARAMETERS_H

/**
 *     @class GTPeParameters
 *
 *     @short Structure for parameters of one GTPe
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:38 $
 *
 *
 **/

// to repesent data as XDATA
#include "xdata/Boolean.h"
#include "xdata/Double.h"
#include "xdata/UnsignedShort.h"

namespace d2s {

  struct GTPeParameters {
    xdata::UnsignedShort daqPartitionId;
    xdata::UnsignedShort detPartitionEnableMask;
    xdata::Double triggerRate;
    xdata::Boolean autoDAQPartitionId;   // if true, assign a free DAQ partition ID, automatically (default = false)

    xdata::Boolean enableATTSInput;      // if false, simulate a ready at the input (default = true)

    xdata::Boolean clockedMode;          // must be false to run multiple partitions
    xdata::Double clockedModeFrequency;  // only relevant if clockedMode == true
    xdata::Boolean SLINKRequired;        // must be same in every partition
  };

}

#endif
