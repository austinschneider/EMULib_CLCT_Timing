#ifndef _FMMHISTORYLOGGER_H
#define _FMMHISTORYLOGGER_H

/**
 *     @class FMMHistoryLogger
 *
 *     @short This class logs FMM history items to a set of log files
 *
 *            It is an tts::FMMHistoryConsumer which can be registered with the tts::FMMHistoryMonitor       
 *   
 *            The class creates up to two log files per run which are used alternately.
 *
 *            Logs are kept for 10 runs (i.e. old logs for a runs with the same run number
 *            modulo 10 are deleted).
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

#include "xcept/Exception.h"
#include <fstream>
#include <stdint.h>

namespace tts {

  class FMMHistoryLogger : public tts::FMMHistoryConsumer {
  
  public:
    /// c-tor
    FMMHistoryLogger( std::string const& logFileBaseName,
		      uint32_t logFileSizeLimitBytes,
		      bool enableLogRotation);

    /// d-tor
    virtual ~FMMHistoryLogger();

    /// set the runNumber
    void setRunNumber( uint32_t runNumber );

    /// start logging
    virtual void beforeMonitorStart();

    /// stop logging
    virtual void afterMonitorStop( uint64_t extendedTimeStamp );
  
    /// process an item
    virtual void processItem( tts::FMMHistoryItem const& hi, uint32_t address );

    /// process an item
    virtual void processWarning( std::string const& warn_string );

  private: 
    /// remove old logfiles with same run number mod 10
    void removeOldLogFiles();

    /// make a new log file name
    std::string makeFileName();
  
    /// print the header of teh log file
    void printLogHeader(bool starting);
  
    /// check the log file size and open a new log file if necessary
    void checkFileSize();

    std::string _logFileBaseName;
    uint32_t _logFileSizeLimitBytes;
    bool _enableLogRotation;

    std::ofstream _of;
    uint32_t _runNumber;
    uint32_t _filenum;
  };

}
#endif
