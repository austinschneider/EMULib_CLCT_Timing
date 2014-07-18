#ifndef d2s_GTPEROOTMONITOR_H
#define d2s_GTPEROOTMONITOR_H

/**
 *     @class GTPeROOTMonitor
 *
 *     @short Monitor for the GTPe based on ROOT
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:53:52 $
 *
 *
 **/

// for logging
#include "d2s/gtpecontroller/GTPeRateHistoryMonitor.hh"
#include "log4cplus/logger.h"

#include "toolbox/BSem.h"

#include <stdint.h>
#include <deque>
#include <utility>


namespace d2s {
  // to control the hardware
  class GTPeCard;
  class GTPeCounterMonitor;

  class GTPeROOTMonitor : public d2s::GTPeRateHistoryMonitor {

  public:
    GTPeROOTMonitor( GTPeCard& gtpe, 
		     std::string counter_item,
		     log4cplus::Logger& logger, 
		     uint32_t historydepth=50);
    virtual ~GTPeROOTMonitor();

    /// generate a history plot
    virtual void generateHistoryPlot(char* filename);

  };


}
#endif
