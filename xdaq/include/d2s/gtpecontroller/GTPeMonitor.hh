#ifndef d2s_GTPEMONITOR_H
#define d2s_GTPEMONITOR_H

/**
 *     @class GTPeMonitor
 *
 *     @short Monitor for the GTPe
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:38 $
 *
 *
 **/

#include <utility>
#include <stdint.h>
#include <string>

namespace d2s {

  class GTPeMonitor {


  public:
    GTPeMonitor() {};
    virtual ~GTPeMonitor() {};

    /// set the counter ID to be monitored
    virtual void setCounterItem(std::string counter_item) = 0;
    
    /// start the GTPeMonitor
    virtual void start() = 0;

    /// stop the GTPeMonitor
    virtual void stop() = 0;

    /// update the counters and add a point to the history plot
    ///
    /// has to be called periodically to sample the trigger rate
    ///
    virtual void update() = 0;

    /// generate a history plot
    virtual void generateHistoryPlot(char* filename) = 0;

    /// get the last computed time, rate pair
    virtual std::pair<double, double> getLastComputedRate() = 0;
  };


}
#endif
