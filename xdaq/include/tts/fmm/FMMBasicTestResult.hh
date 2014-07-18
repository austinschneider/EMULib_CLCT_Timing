#ifndef _FMMBASICTESTRESULT_H
#define _FMMBASICTESTRESULT_H

#include <stdint.h>

namespace tts {

  struct FMMBasicTestResult {
    std::string testname;
    std::string testversion;
    std::string testparameters;
    uint64_t nloops;
    uint64_t nerrors;
    uint64_t nusecs;
    std::string errlog;
  };

}
#endif
