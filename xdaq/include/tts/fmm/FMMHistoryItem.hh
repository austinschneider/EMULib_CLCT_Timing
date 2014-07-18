#ifndef _FMMHISTORYITEM_H
#define _FMMHISTORYITEM_H

/**
 *     @class FMMHistoryItem
 *
 *     @short An item in the FMM history includes all input states and a timestamp
 *
 *            This class stores the FMM history in a compact format. It provides 
 *            methods for easy access to the data.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "tts/ttsbase/TTSState.hh"

#include <vector>
#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMHistoryItem {

  public:
    /// c-tor 
    FMMHistoryItem();

    /// c-tor from uint32_t
    ///
    /// @param histdata is the history data as read from the FMM buffer
    FMMHistoryItem( uint32_t histdata[4], uint32_t wrapcount = 0 );

    /// c-tor from timestamp and std::vector<tts::TTSState> >
    ///
    /// @param extendedTimeStamp is the extended timestamp
    /// @param states is a vector of 20 states
    /// @param transitionMissBit is the transition miss bit 
    FMMHistoryItem( uint64_t extendedTimeStamp, std::vector<tts::TTSState> const& states, bool transitionMissBit );

    /// copy c-tor
    FMMHistoryItem( tts::FMMHistoryItem const & item );

    /// d-tor
    virtual ~FMMHistoryItem();

    /// set the history item
    ///
    /// @param histdata is the history data as read from the FMM buffer
    void set( uint32_t histdata[4], uint32_t wrapcount = 0 );

    /// retrieve the std::vector of 20 input states
    std::vector<tts::TTSState> getInputStates() const;

    /// retrieve the 40-bit timestamp
    ///
    /// the return value indicates the number of bunch crossings since the last reset
    uint64_t getTimestamp() const;

    /// retrieve the 64-bit timestamp
    /// 
    /// 40-bit timestamp + wrap count
    ///
    /// the return value indicates the number of bunch crossings since the last reset
    uint64_t getExtendedTimestamp() const;

    /// retrieve the timestamp as a std::string
    ///
    std::string getTimestampString() const;

    /// get the transition miss bit
    ///
    bool getTransitionMissBit() const;

    /// reurn a tring representation
    std::string toString() const;

    // set the wrap count (number of timer wraps)
    void setWrapCount(uint32_t wrapcount) { _wrapcount = wrapcount; }

    /// return the wrap count (number of timer wraps)
    uint32_t getWrapCount() const { return _wrapcount; };

  private:
    /// the history is stored as four 32-bit words
    uint32_t _histdata[4];
    uint32_t _wrapcount;

  };

}
#endif
