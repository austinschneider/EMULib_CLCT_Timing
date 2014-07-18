#ifndef _FMMCONFIGURATION_H
#define _FMMCONFIGURATION_H
/**
 *     @class FMMConfiguration
 *
 *     @short Stores the FMM configuration
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:26 $
 *
 *
 **/

#include "tts/ttsbase/TTSState.hh"
#include <iostream>
#include <stdint.h>

namespace tts {

  class FMMConfiguration {

  public:
    /// c-tor 
    FMMConfiguration(bool isDual=false, uint32_t mask=0, uint32_t threshold20=0, uint32_t threshold10A=0, uint32_t threshold10B=0) 
      : _isDual(isDual), 
	_mask(mask & 0xfffff), 
	_threshold20(threshold20 & 0x1f), 
	_threshold10A(threshold10A & 0xf), 
	_threshold10B(threshold10B & 0xf) {};

    /// d-tor
    virtual ~FMMConfiguration() {};

    /// toggle dual FMM mode
    ///
    /// @param dual is true for dual-FMM mode, false for single-FMM mode
    void toggleDualMode(bool dual) { _isDual = dual; };
  
    /// are we in dual FMM mode?
    bool isDualMode() const { return _isDual; };

    /// set the mask
    ///
    /// @param mask[19:0] is the mask for the 20 input channels. 
    ///        Setting a bit to 1 means that the channel is masked (switched off).
    void setMask(uint32_t mask) { _mask = mask & 0xfffff; };

    /// read back the mask
    uint32_t getMask() const { return _mask; };

    /// set the threshold for the out-of-sync merging function (20->1 mode)
    ///
    /// @param threshold[4:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold20(uint32_t threshold) { _threshold20 = threshold & 0x1f; };

    /// read back the threshold
    uint32_t getThreshold20() const { return _threshold20; };

    /// set the threshold A (merging of first 10 inputs) for 10-input (dual-FMM) mode
    ///
    /// @param threshold[3:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold10A(uint32_t threshold)  { _threshold10A = threshold & 0xf; };

    /// read back the threshold
    uint32_t getThreshold10A() const { return _threshold10A; };

    /// set the threshold B (merging of second 10 inputs) for 10-input (dual-FMM) mode
    ///
    /// @param threshold[3:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold10B(uint32_t threshold)  { _threshold10B = threshold & 0xf; };

    /// read back the threshold
    uint32_t getThreshold10B() const { return _threshold10B; };

  private:
    bool _isDual;
    uint32_t _mask;
    uint32_t _threshold20;
    uint32_t _threshold10A;
    uint32_t _threshold10B;
  };
}

std::ostream& operator<< (std::ostream& os, tts::FMMConfiguration const& conf); 
#endif
