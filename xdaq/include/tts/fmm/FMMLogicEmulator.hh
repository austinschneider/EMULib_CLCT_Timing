#ifndef _FMMLOGICEMULATOR_H
#define _FMMLOGICEMULATOR_H
/**
 *     @class FMMLogicEmulator
 *
 *     @short A class emulating the FMM's merging logic 
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
#include "tts/fmm/FMMConfiguration.hh"

#include <vector>
#include <stdint.h>

namespace tts {

  class FMMLogicEmulator {

  public:
    /// c-tor 
    FMMLogicEmulator(bool isDual=false, uint32_t mask=0, uint32_t threshold20=0, uint32_t threshold10A=0, uint32_t threshold10B=0) 
      : _cfg(isDual, mask, threshold20, threshold10A, threshold10B) {};

    /// c-tor 
    FMMLogicEmulator(tts::FMMConfiguration const& cfg)
      : _cfg(cfg) {};

    /// d-tor
    virtual ~FMMLogicEmulator() {};


    /// set the configuration
    /// 
    /// @param cfg is the FMM configuration
    void setConfig(tts::FMMConfiguration const& cfg) { _cfg = cfg; };

    /// get the configuration
    tts::FMMConfiguration getConfig() { return _cfg; }

    /// get the output state after merging for the first half-FMM
    /// (identical to getResultB() in single-FMM mode)
    /// 
    /// @param states is th std::vector of input states
    TTSState getResultA(std::vector<tts::TTSState> states) const;

    /// get the output state after merging for the second half-FMM
    /// (identical to getResultA() in single-FMM mode)
    /// 
    /// @param states is the std::vector of input states
    TTSState getResultB(std::vector<tts::TTSState> states) const;

    /// get the func value (input to the priority encoder)  for the first half-FMM
    /// (identical to getFuncB() in single-FMM mode)
    /// 
    /// @param states is the std::vector of input states
    uint32_t getFuncA(std::vector<tts::TTSState> states) const;

    /// get the func value (input to the priority encoder)  for the second half-FMM
    /// (identical to getFuncA() in single-FMM mode)
    /// 
    /// @param states is the std::vector of input states
    uint32_t getFuncB(std::vector<tts::TTSState> states) const;

  private:
    void merge(std::vector<tts::TTSState> states, uint32_t mask, uint32_t threshold, 
	       uint32_t from, uint32_t to,
	       tts::TTSState& outstate, uint32_t& func) const;

    tts::FMMConfiguration _cfg;
  };

}
#endif
