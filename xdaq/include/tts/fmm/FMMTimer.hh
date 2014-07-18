#ifndef _FMMTIMER_H
#define _FMMTIMER_H

/**
 *     @class FMMTimer
 *
 *     @short A timer utility for the FMM
 *
 *            This is yet another timer class. It uses a 64-bit
 *            uint64_t to store the time tag.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include <stdint.h>

namespace tts {

  class FMMTimer {
  
  public:
    /// c-tor
    FMMTimer() {};

    /// d-tor
    virtual ~FMMTimer() {};

    /// return the current time in microseconds
    ///
    /// the 64-bit time won't overrun in the next 584000 years
    /// (but a 32-bit value would overrun after 71 minutes)
    static uint64_t getMicroTime();
  };

}
#endif
