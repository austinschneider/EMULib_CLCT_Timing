#ifndef _FMMPOISSONTRANSITIONGENERATOR_H
#define _FMMPOISSONTRANSITIONGENERATOR_H

/**
 *     @class FMMPoissonTransitionGenerator
 *
 *     @short Generates random states transitions according to a poissonian model
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
#include "tts/fmm/FMMTransitionGenerator.hh"

#include "xcept/Exception.h"

#include <vector>
#include <stdint.h>

namespace tts {

  class FMMPoissonTransitionGenerator : public tts::FMMTransitionGenerator {

  public:
    /// c-tor 
    FMMPoissonTransitionGenerator(uint32_t numstates=20);

    /// d-tor
    virtual ~FMMPoissonTransitionGenerator();

    /// get the new input states
    ///
    /// @param states is a std::vector of states into which the input states will be filled.
    ///        thsi std::vector is resized to the number of states given in the constructor.
    virtual void getNewStates(std::vector<tts::TTSState> &states);

  private:
    uint32_t _num;

    double _frac_dis;   
    double _frac_err;   
    double _frac_oos;   
    double _frac_busy;  
    double _frac_warn;  
    double _frac_inv;   
  };

}

#endif
