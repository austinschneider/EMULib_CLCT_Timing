#ifndef d2s_GTPERATEHISTORYMONITOR_H
#define d2s_GTPERATEHISTORYMONITOR_H

/**
 *     @class GTPeRateHistoryMonitor
 *
 *     @short Monitor for the GTPe based on RateHistory
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
#include "d2s/gtpecontroller/GTPeMonitor.hh"
#include "log4cplus/logger.h"

#include "toolbox/BSem.h"

#include <stdint.h>
#include <deque>
#include <utility>


namespace d2s {
  // to control the hardware
  class GTPeCard;
  class GTPeCounterMonitor;

  class GTPeRateHistoryMonitor : public d2s::GTPeMonitor {

  public:
    GTPeRateHistoryMonitor( GTPeCard& gtpe, 
			    std::string _counter_item,
			    log4cplus::Logger& logger, 
			    uint32_t historydepth=50);
    virtual ~GTPeRateHistoryMonitor();


    virtual void setCounterItem(std::string counter_item){
      _counter_item = counter_item;
    };

    /// start the GTPeRateHistoryMonitor
    ///
    /// this method requires exclusive access to the GTPe as it latches the counters
    virtual void start();

    /// stop the GTPeRateHistoryMonitor
    virtual void stop();

    /// update the counters and add a point to the history plot
    ///
    /// has to be called periodically to sample the trigger rate
    ///
    /// this method requires exclusive access to the GTPe as it latches the counters
    ///
    virtual void update();

    /// generate a history plot
    virtual void generateHistoryPlot(char* filename);

    /// get the last computed time, rate pair
    virtual std::pair<double, double> getLastComputedRate();



  private:

    GTPeCard& _gtpe;
    std::string _counter_item;
    uint32_t _distr_counter_idx;
    log4cplus::Logger& _logger;

    uint32_t _historydepth;
    uint64_t _distrtrig_old;
    uint64_t _ticks_lastread;

  protected:
    std::deque<std::pair<double, double> > _ratehistory;
    toolbox::BSem _deque_semaphore ;
  };


}
#endif
