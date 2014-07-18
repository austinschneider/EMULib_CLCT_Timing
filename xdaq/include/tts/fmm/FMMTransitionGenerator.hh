#ifndef _FMMTRANSITIONGENERATOR_H
#define _FMMTRANSITIONGENERATOR_H

/**
 *     @class FMMTransitionGenerator
 *
 *     @short Abstract interface for Transition Generators used for testing the FMM 
 *
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

namespace tts {

  class FMMTransitionGenerator {

  public:
    /// c-tor 
    FMMTransitionGenerator() {};

    /// d-tor
    virtual ~FMMTransitionGenerator() {};

    /// get the new input states
    virtual void getNewStates(std::vector<tts::TTSState> &states) = 0;

  };

}
#endif
