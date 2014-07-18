#ifndef _FMMDEADTIMEMONITOR_H
#define _FMMDEADTIMEMONITOR_H

/**
 *     @class FMMDeadTimeMonitor
 *
 *     @short This class monitors the dead time counters of the FMM
 *
 *            The dead time counter are 32 bit wide and count in units of bunch
 *            crossings. The counter need to be read by software at least 
 *            every 107 seconds ( 2^32 / 40 000 000 ).
 *            
 *            The update method reads the dead time counters and updates the 
 *            counters in software. It needs to be called periodically, at least
 *            every 107 seconds.
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:06:23 $
 *
 *
 **/

#include "tts/fmm/FMMCard.hh"
#include "tts/fmm/FMMDeadTime.hh"

#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"

#include "toolbox/BSem.h"
#include "toolbox/TimeVal.h"

#include <stdint.h>

namespace tts {

  class FMMDeadTimeMonitor  {
  
  public:
    enum { NumCounters = 110 };

    /// c-tor
    FMMDeadTimeMonitor( tts::FMMCard& fmm );

    /// d-tor
    virtual ~FMMDeadTimeMonitor();

    /// reset and start monitoring dead times.
    ///
    /// @param resetHW. if true, reset the counters;
    ///        if false counters have to be reset after calling start
    ///
    void start( bool resetHW = true )
      throw (HAL::HardwareAccessException);

    /// stop monitoring dead times
    ///
    /// counters are read for a last time and kept in memeory.
    void stop()
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// retrieve dead time counters and time tag
    ///
    /// if doUpdate==true internally calls updateCounters before returning the counters.
    /// a std::vector of 44 counters is returned:
    ///
    /// counters 0 to 21 count for each input channel and two output functions the time spent in busy state
    /// counters 22 to 43 count for each input channel and two output functions the time spent in warning state
    ///
    /// the dead time is counted in units of 25 ns
    ///
    void readCounters(std::vector<tts::FMMDeadTime> & counters, uint64_t& timetag, bool doUpdate=true)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// read one counter
    ///
    /// no update is done.
    /// internally, no lock is used. Lock has to be used by calling lock() before calling readCounterNoUpdateNoLock()
    tts::FMMDeadTime readCounterNoUpdateNoLock(uint32_t icounter)
      throw (xcept::Exception) {

      if (icounter >= NumCounters) {
	XCEPT_RAISE(xcept::Exception, "counter index out of range");
      }
      return _counters[icounter];
    };

    /// read one dead time fraction
    ///
    /// no update is done.
    /// internally, no lock is used. Lock has to be used by calling lock() before calling readCounterNoUpdateNoLock()
    double readDeadTimeFractionLastIntervalNoUpdateNoLock(uint32_t icounter)
      throw (xcept::Exception) {

      if (icounter >= NumCounters) {
	XCEPT_RAISE(xcept::Exception, "counter index out of range");
      }

      if (_counters[icounter].getTimeBX() == _counters_old[icounter].getTimeBX()) // avoid some rounding errors
	  return 0.;
      else
	return (_counters[icounter].getSeconds() - _counters_old[icounter].getSeconds()) * 1.e6 / (double) _t_interval;
    };

    /// read the time tag
    uint64_t readTimeTagNoUpdateNoLock() {
      return _timetag;
    }

    /// read the time stamp
    toolbox::TimeVal readTimeStampNoUpdateNoLock() {
      return _timestamp;
    }

    /// retrieve the dead time counters as a fractions of the time over which they are measured
    ///
    /// if doUpdate==true internally calls doUpdateCounters before returning the counters.
    /// a std::vector of 44 fractions is returned:
    ///
    /// fractions 0 to 21 count for each input channel and two output functions the fraction of time spent in busy state
    /// fractions 22 to 43 count for each input channel and two output functions the fraction of time spent in warning state
    ///
    void readDeadTimeFractions(std::vector<double> & deadTimeFractions, bool doUpdate=true)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// retrieve the dead time counters as a fractions of the time over which they are measured
    /// for the interval between the last two calls to doUpdateCounters()
    ///
    /// Note that readCounters and readDeadTimeFractions  also call doUpdateCounters() when called with default arguments
    ///
    /// a std::vector of 110 fractions is returned:
    ///
    /// fractions 0 to 21 count for each input channel and two output functions the fraction of time spent in busy state
    /// fractions 22 to 43 count for each input channel and two output functions the fraction of time spent in warning state
    /// fractions 44 to 65 count for each input channel and two output functions the fraction of time spent in ready state
    /// fractions 66 to 87 count for each input channel and two output functions the fraction of time spent in oos state
    /// fractions 88 to 109 count for each input channel and two output functions the fraction of time spent in error state
    ///
    void readDeadTimeFractionsLastInterval(std::vector<double> & deadTimeFractions)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// update the software counters
    ///
    /// needs to be called periodically (at least every 107s)
    /// before the hardware counters wrap around. The method is thread safe and may be called 
    /// periodically from a second thread.
    /// 
    /// it does not access hardware if the FMMDeadTimeMonitor is not running
    ///
    void updateCounters()
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// lock the FMMDeadTimeMonitor
    ///
    /// Use this in order to retrieve several Counters / Fractions in a row
    /// The retrieval function will lock the lock again but this is ok since we use a recursive lock
    ///
    /// Attention: this makes sense only if the non-updating versions of the retrieval are used.
    void lock();

    /// unlock the FMMDeadTimeMonitor
    ///
    void unlock();


  private: 
    /// reset the dead time monitors
    ///
    /// the monitors start counting immediately as they are always running
    ///
    void doReset( bool resetHW )
      throw (HAL::HardwareAccessException);

    /// internal method to update the software counters
    ///
    void doUpdateCounters()
      throw (HAL::HardwareAccessException, xcept::Exception);

    tts::FMMCard& _fmm;
    bool _running;

    uint64_t _t_reset;
    uint64_t _t_lastread;
    uint64_t _timetag;
    toolbox::TimeVal _timestamp;
    std::vector<tts::FMMDeadTime> _counters;  

    uint64_t _t_lastread_old;
    uint64_t _timetag_old;
    uint64_t _t_interval; // difference between time tag old and time tag (pre-computed for more efficient retrieval)
    std::vector<tts::FMMDeadTime> _counters_old;  

    toolbox::BSem _update_semaphore;
  };

}

#endif
