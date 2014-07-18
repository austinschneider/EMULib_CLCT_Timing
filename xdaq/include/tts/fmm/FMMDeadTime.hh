#ifndef _FMMDEADTIME_H
#define _FMMDEADTIME_H

/**
 *     @class FMMDeadTime
 *
 *     @short This class stores the dead time measured by the FMM
 *
 *            Dead time is stores as a low and a high 32-bit word.
 *            The unit of measurement is 25ns
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:26 $
 *
 *
 **/

#include <stdint.h>

namespace tts {

  class FMMDeadTime  {
  
  public:
    uint32_t tlow;
    uint32_t thigh;

    /// c-tor
    FMMDeadTime() {
      tlow = 0;
      thigh = 0;
    }

    /// d-tor
    ~FMMDeadTime() {};

    /// return the dead time as an uint64_t (64-bit)
    /// 
    /// the unit is 25 ns (the bunch crossing) 
    uint64_t getTimeBX() {
      return (((uint64_t) thigh) << 32 ) + tlow;
    };

    /// get the time in seconds
    double getSeconds() {
      return ( (double) getTimeBX() ) / 40.e6;
    };
  
  };
}

#endif
