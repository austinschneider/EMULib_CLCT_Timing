#ifndef d2s_GTPECOUNTERMONITOR_H
#define d2s_GTPECOUNTERMONITOR_H

/**
 *     @class GTPeCounterMonitor
 *
 *     @short Monitor for the GTPe Counters in order to extend 32 bit counters to 64 bit.
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
#include "log4cplus/logger.h"

#include "hal/HardwareAccessException.hh"
#include "toolbox/BSem.h"

#include <stdint.h>
#include <vector>

namespace d2s {
  // to control the hardware
  class GTPeCard;

  class GTPeCounterMonitor {

  public:

    /// constructor
    ///
    /// There should be one GTPeCounterMonitor for each GTPe. Update should be called 
    /// periodically at least every hour.
    ///
    /// All classes which need to access the GTPe Counters (GTPeWebInterface, GTPeMonitor) 
    /// should use d2s::GTPeCounterMonitor::readCounters() 
    ///
    GTPeCounterMonitor( GTPeCard& gtpe, log4cplus::Logger& logger);
    ~GTPeCounterMonitor();

    /// start the GTPeCounterMonitor
    ///
    /// should be called just before starting the GTPe
    void start();

    /// stop the GTPeCounterMonitor
    ///
    /// should be called after stopping the GTPe but before resetting the counters
    void stop()
      throw (HAL::HardwareAccessException);

    /// update all the counters
    ///
    /// has to be called periodically. 
    /// At the maximum rate of 123 kHz, the 32-bit counter overrun after about 9 1/2 hours.
    /// For 8 partitions at 123 kHz => 1 hour;
    ///
    void update()
      throw (HAL::HardwareAccessException);

    /// read the counters
    ///
    /// calls update before
    void readCounters(std::vector<uint64_t>& counters)
      throw (HAL::HardwareAccessException);

  private:
    
    /// do the real update
    void do_update()
      throw (HAL::HardwareAccessException);

    /// read the time in seconds
    uint32_t getTime();


    GTPeCard& _gtpe;
    log4cplus::Logger& _logger;

    bool _running;
    uint32_t _t_lastread;
    std::vector<uint64_t> _counters;

    toolbox::BSem _update_semaphore;
  };
}
#endif
