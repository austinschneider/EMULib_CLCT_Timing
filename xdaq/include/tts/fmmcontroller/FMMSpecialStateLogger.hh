#ifndef _FMMSPECIALSTATELOGGER_H
#define _FMMSPECIALSTATELOGGER_H

/**
 *     @class FMMSpecialStateLogger
 *
 *     @short This class logs special FMM history states to a set of special log files
 *
 *            It is an tts::FMMHistoryConsumer which can be registered with the tts::FMMHistoryMonitor       
 *   
 *            It logs transitions to and from a configurable list of special states such as ERROR or OUT OF SYNC.
 *            The log file is kept across runs.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:31 $
 *
 *
 **/
#include "tts/fmm/FMMHistoryItem.hh"
#include "tts/fmmcontroller/FMMHistoryConsumer.hh"
#include "tts/ttsbase/TTSState.hh"

#include "xcept/Exception.h"
#include "log4cplus/logger.h"

#include <fstream>
#include <set>
#include <stdint.h>

namespace tts {

  class FMMSpecialStateLogger : public tts::FMMHistoryConsumer {
  
  public:
    /// c-tor
    FMMSpecialStateLogger( std::set<tts::TTSState> statesToLog,
			   std::string const& logFileBaseName,
			   uint32_t logFileSizeLimitBytes,
			   log4cplus::Logger* logger);

    /// d-tor
    virtual ~FMMSpecialStateLogger();

    /// set the runNumber
    void setRunNumber( uint32_t runNumber );

    /// set the inoutEnabelMask
    void setInputEnableMask( uint32_t inputEnableMask );

    /// start logging
    virtual void beforeMonitorStart();

    /// stop logging
    virtual void afterMonitorStop( uint64_t extendedTimeStamp );
  
    /// process an item
    virtual void processItem( tts::FMMHistoryItem const& hi, uint32_t address );

  private: 
    /// make a new log file name
    std::string makeFileName();
  
    /// print the header of teh log file
    void printLogHeader(bool starting);
  
    /// check the log file size and open a new log file if necessary
    void checkFileSize();

    std::set<tts::TTSState> _statesToLog;
    std::string _logFileBaseName;
    uint32_t _logFileSizeLimitBytes;
    log4cplus::Logger* _logger;    

    tts::FMMHistoryItem _previous_hi;

    std::ofstream _of;
    uint32_t _runNumber;
    uint32_t _inputEnableMask; 
    bool _justStarted;
  };

}
#endif
