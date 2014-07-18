#ifndef _FMMTRANSITIONANALYZER_H
#define _FMMTRANSITIONANALYZER_H

/**
 *     @class FMMTransitionAnalyzer
 *
 *     @short This class analyzes FMM transitions and makes them available to the monitoring
 *
 *            It is an tts::FMMHistoryConsumer which can be registered with the tts::FMMHistoryMonitor       
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:06:23 $
 *
 *
 **/
#include "tts/fmm/FMMHistoryItem.hh"
#include "tts/fmmcontroller/FMMHistoryConsumer.hh"
#include "tts/ttsbase/TTSState.hh"

#include "xcept/Exception.h"
#include "log4cplus/logger.h"

#include "toolbox/BSem.h"

#include <fstream>
#include <set>
#include <stdint.h>

namespace tts {

  class FMMTransitionAnalyzer : public tts::FMMHistoryConsumer {
  
  public:
    /// c-tor
    FMMTransitionAnalyzer(log4cplus::Logger* logger);

    /// d-tor
    virtual ~FMMTransitionAnalyzer();

    /// start logging
    virtual void beforeMonitorStart();

    /// stop logging
    virtual void afterMonitorStop( uint64_t extendedTimeStamp );
  
    /// process an item
    virtual void processItem( tts::FMMHistoryItem const& hi, uint32_t address );

    /// get all the transition counters: 1st dimension: 20 io,/s , 2nd dimension: 16 states
    std::vector<std::vector<uint64_t> > getTransitionCounters();

    /// get all the times in ticks spent in each state. 1st dimension: 20 io,/s , 2nd dimension: 16 states
    std::vector<std::vector<uint64_t> > getTimesPerState();

    /// get all the transition counter
    ///
    /// @param io is the io
    /// @param state is the state
    uint64_t getTransitionCounter(uint32_t io, tts::TTSState state);

    /// get the transition frequency for transitions into a state
    ///
    /// @param io is the io
    /// @param state is the state
    double getTransitionFrequency(uint32_t io, tts::TTSState state);

    /// get time in ticks spent in a state (up to the last transition that occured on this input)
    ///
    /// @param io is the io
    /// @param state is the state
    uint64_t getTimeInState(uint32_t io, tts::TTSState state);

    
    /// get time in ticks spent in a state (up to the current time stamp)
    ///
    /// @param io is the io
    /// @param state is the state
    /// @param timestamp is the current extended timestamp
    uint64_t getTimeInStateCorrected(uint32_t io, tts::TTSState state, uint64_t timestamp);

    /// inline version without locking
    uint64_t getTransitionCounterNoLock(uint32_t io, tts::TTSState state) { return _transitionCounters[io][state]; }

    /// inline version without locking
    double getTransitionFrequencyNoLock(uint32_t io, tts::TTSState state) { return _transitionFrequencies[io][state]; }

    /// inline version without locking
    uint64_t getTimeInStateNoLock(uint32_t io, tts::TTSState state) { return _timesPerState[io][state]; }

    /// update the transition frequency measurement
    ///
    /// has to be called at regular intervals
    void updateTransitionFrequencies();

    /// lock updates before calling multiple counter retrieve methods
    ///
    /// the retrival functions may acquire the lock a second time but this is ok since we use a recursive lock.
    void lock();

    /// unlock 
    void unlock();

  private: 
    log4cplus::Logger* _logger;    

    tts::FMMHistoryItem _previous_hi;

    std::vector<std::vector<uint64_t> > _transitionCounters;
    std::vector<std::vector<uint64_t> > _timesPerState;    

    std::vector<std::vector<uint64_t> > _transitionCountersOld;
    std::vector<std::vector<double> > _transitionFrequencies;

    std::vector<uint64_t> _timestamp_lasttransition;
    uint64_t _t_lastupdate;

    toolbox::BSem _countersSema;
  };

}
#endif
