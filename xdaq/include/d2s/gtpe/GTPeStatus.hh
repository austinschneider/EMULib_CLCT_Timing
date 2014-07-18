#ifndef _GTPESTATUS_H
#define _GTPESTATUS_H

/**
 *     @class GTPeStatus
 *
 *     @short Data class representing a snapshot of the GTPeStatus.
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:33 $
 *
 *
 **/

#include "tts/ttsbase/TTSState.hh"

#include "xcept/Exception.h"

#include <stdint.h>

namespace d2s {


  class GTPeStatus {

  public:
    /// c-tor
    ///
    /// the parameters are the 3 registers that define the GTPe Status
    GTPeStatus( uint32_t reg_tts_status, uint32_t partstat);

    /// d-tor
    ~GTPeStatus();
    
    /// get the sTTS Input state for Det partition 
    ///
    /// @param part_idx is the detector partition index 0..8
    tts::TTSState getDetPartitionInputState(uint32_t part_idx)
      throw (xcept::Exception);
    
    /// get the aTTS Input state for DAQ partition 
    ///
    /// @param part_idx is the DAQ partition index 0..8
    tts::TTSState getDAQPartitionInputState(uint32_t part_idx)
      throw (xcept::Exception);

    /// get the current TCS state for a trigger partition 
    ///
    /// This state is sent to the aTTS output unless the output 
    /// is controlled by software
    ///
    /// @param part_idx is the Trigger partition index 0..8
    tts::TTSState getTCSPartitionState(uint32_t part_idx)
      throw (xcept::Exception);

    /// is the TCS Partition Active ?
    bool isTCSPartitionActive(uint32_t part_idx)
      throw (xcept::Exception);

    /// is the SLINK Down
    bool isLinkDown();
    
    /// is the SLINK Full
    bool isLinkFull();
    
    /// is the internal buffer full
    bool isBufferFull();    

  private:
    tts::TTSState ttsStateFromGTPeInputState(uint32_t gtpestate);
    tts::TTSState ttsStateFromGTPeOutputState(uint32_t gtpestate);

    uint32_t _reg_tts_status, _partstat;
  };

}


#endif
