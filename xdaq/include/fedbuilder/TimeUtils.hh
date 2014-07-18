#ifndef __TimeUtils_
#define __TimeUtils_

#include <stdint.h>
#include <vector>
#include <sys/time.h>
#include <string>

namespace fedbuilder {

class TimeUtils {
public:
  TimeUtils( uint32_t laps = 50 );
  
  void start();
  void stop();
  void lap();
  void reset();
  uint32_t read();
  uint32_t readLap( uint32_t lapIndex, std::string &err );

  /*
   * Retrieve number of mircroseconds since last call to this method.
   * 
   * The TimeUtils has to be started beforehand.
   */
  uint32_t getDeltaTime();

private:
  uint32_t subtractTime( timeval& stopTime, timeval& startTime );
  double startStopOffset;
  double lapOffset;
  uint32_t lapCounter;
  uint32_t maxLaps;
  timeval startTime;
  timeval stopTime;
  timeval deltaTime1;
  timeval deltaTime2;
  timeval *lastTime;
  timeval *newTime;
  std::vector< timeval > lapVector;
};

} /* namespace HAL */

#endif /* __TimeUtils */
