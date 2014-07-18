#ifndef FMMHISTORYCONSUMER_H
#define FMMHISTORYCONSUMER_H

/**
 *     @class FMMHistoryConsumer
 *
 *     @short Abstract base class for classes that consume FMM History Items
 *
 *            Concrete impementations are a logger or an online analyzer
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:31 $
 *
 *
 **/
#include <string>
#include <stdint.h>

namespace tts {

  class FMMHistoryItem;

  class FMMHistoryConsumer {

  public:
    /// start the history consumer
    virtual void beforeMonitorStart() = 0;

    /// stop the history consumer
    virtual void afterMonitorStop( uint64_t extendedTimeStamp ) = 0;

    /// callback to process a new item
    virtual void processItem( tts::FMMHistoryItem const& hi, uint32_t address ) = 0;

    /// callback to process a new warning message (e.g. may be added to log)
    virtual void processWarning( std::string const& warn_string ) {};

    virtual ~FMMHistoryConsumer() {};
  };

}

#endif
