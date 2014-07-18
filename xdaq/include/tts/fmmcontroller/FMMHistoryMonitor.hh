#ifndef _FMMHISTORYMONITOR_H
#define _FMMHISTORYMONITOR_H

/**
 *     @class FMMHistoryMonitor
 *
 *     @short This class monitors the transition history memory of the FMM
 *
 *            There are 2 MB of history memory on an tts::FMM. Each history entry 
 *            uses 16 bytes. There are therefore 128k entries int the history.
 *            The theoretic maximum speed at which the history memory is filled
 *            up is 4 byte / 25 ns, i.e. it could be full after 13 ms. In real
 *            operation a much lower rate of transitions is expected. 
 *
 *            The update method checks the write counter and the
 *            current system time. If new data is available,
 *            new history data is read form the FMM and stored in a
 *            buffer.
 *            Using the extended history address write counter, the
 *            software can detect history memory overwrites, if the
 *            the update method is called at least every 107 seconds;
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:06:23 $
 *
 *
 **/

#include "tts/fmm/FMMCard.hh"
#include "tts/fmm/FMMHistoryItem.hh"

#include "toolbox/task/Action.h"
#include "toolbox/lang/Class.h"
#include "xcept/Exception.h"

#include "toolbox/BSem.h"

// for logging
#include "log4cplus/logger.h"
#include <deque>
#include <vector>
#include <list>
#include <stdint.h>

namespace toolbox {
  namespace task {	
    class WorkLoop;
  };
};

namespace tts {

  class FMMHistoryConsumer;

  class FMMHistoryMonitor : public toolbox::lang::Class {
  
  public:
    /// c-tor
    FMMHistoryMonitor( tts::FMMCard& card,
		       double cacheDepthSeconds,
		       bool selfUpdate = false,
		       log4cplus::Logger* logger = 0);

    /// d-tor
    virtual ~FMMHistoryMonitor();

    /// start periodically monitoring the History memory
    ///
    /// this method will spawn a new thread only if selfUpdate is true
    ///
    /// @param resetHW. if true, reset the counters;
    ///        if false counters have to be reset after calling start
    void start( bool resetHW )
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock,
	     xcept::Exception);

    /// stop periodically monitoring the history memory
    void stop()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// update the history
    /// 
    /// in selfUpdate mode, this method is called by autoUpdate,
    /// otherwise it has to be called periodically.
    ///
    /// At the maximum transition rate of 10 MHz update() would have to
    /// be called every 13ms (the time for the history memory to fill
    /// up). However, readout of the full history memory withing 13ms is
    /// not possible.
    ///
    /// Since transition rates are usually much lower, a longer interval
    /// between sucessive calls to update() may be chosen.
    ///
    /// Even at very low transition rares, update() has to be called at
    /// least every 107 seconds in order to be able to determine where
    /// the history memory has been overwritten.
    /// 
    long update()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// register a new consumer
    void registerConsumer( tts::FMMHistoryConsumer* consumer );

    /// unregister a consumer
    void unRegisterConsumer( tts::FMMHistoryConsumer* consumer );

    /// retrieve new History
    void retrieveCachedHistory( std::vector<tts::FMMHistoryItem> & items);

  private: 
    enum { FMMHistMemSize = 0x20000 }; // in units of 16-byte blocks
    enum { FMMWrapCounterLength = 32768 };

    /// the real update job
    long doUpdate()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// check if the maximum time between updates has been exceeded
    void checkElapsedTime(uint64_t t_now, uint64_t t_last);

    /// check for history memory overwrites
    void checkOverwrite(uint32_t newAddress, 
			uint32_t newWrapCount,
			uint32_t oldAddress, 
			uint32_t oldWrapCount, 
			bool duringReadout);

    /// update the time counter
    void updateTimeCounter() 
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// update the history
    ///
    /// this method is run in an other thread
    bool autoUpdate(toolbox::task::WorkLoop* wl);

    tts::FMMCard& _card;
    double _cacheDepthSeconds;
    bool _selfUpdate;
    log4cplus::Logger* _logger;
  
    std::list<tts::FMMHistoryConsumer*> _consumers;

    /// the workloop (if in selfUpdate mode) 
    toolbox::task::WorkLoop* _wl;  
    toolbox::task::ActionSignature* _signature;

    // these vars belong to the update process
    uint64_t _t_start;
    uint64_t _t_lastUpdate;

    /// history memory write counter at last update
    uint32_t _lastAddress;
    uint32_t _lastWrapCount;

    /// time counter at last update
    uint64_t _lastTimeCounter;

    std::deque<tts::FMMHistoryItem> _cache;
    toolbox::BSem _deque_semaphore;
  };
}

#endif
