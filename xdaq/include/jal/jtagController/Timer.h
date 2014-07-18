#ifndef jal_TIMER_H
#define jal_TIMER_H
/**
 *     @class Timer
 *
 *     @short Timer to provide accurate delays
 *
 * 
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:07 $
 *
 *
**/

#include <stdint.h>

namespace jal {

  class Timer {
    
  public:
    Timer();

    ~Timer();

    /// sleep a number of microseconds
    ///
    void sleepMicros(uint32_t musec);

    /// calibrate the timer
    ///
    /// this takes about half a second
    static void calibrate();

  private:
    static uint64_t _clocks_per_sec;
    static uint32_t _overhead_musec;
  }; 

}

#endif

