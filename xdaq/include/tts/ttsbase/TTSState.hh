#ifndef _tts_ttsbase_TTSSTATE_H
#define _tts_ttsbase_TTSSTATE_H

/**
 *     @class TTSState
 *
 *     @short State in the the Trigger Throttling System (TTS) 
 *
 *            It represents the state of a Front-End Driver (FED) or the 
 *            merged state of multiple FEDs.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:35 $
 *
 *
 **/

#include <string>
#include <iostream>
#include <vector>

namespace tts {

  /// Helper class for extensible enumerations
  class enumeration
  {
  public:
    // convert to/from int
    operator int() const { return _val; }
    enumeration& operator = (int i) { _val = i; return *this; }
    // Operators ==, !=, <, etc. can be implemented using int conversion
  protected:
    enumeration(int i = 0) { _val = i; }
    int _val;
  };


  class TTSState : public tts::enumeration {

  public:
    enum { 
      DISCONNECT1 = 0x0, // the FMM is sending this disconnect code
      WARNING     = 0x1,
      OUTOFSYNC   = 0x2,
      INVALID     = 0x3, // defined by Attila
      BUSY        = 0x4,
      READY       = 0x8,
      IDLE        = 0xA, // only for aTTS from Trigger Control System
      ERROR       = 0xC, // READY and BUSY
      DISCONNECT2 = 0xF,
      _next
    };
  
    /// c-tor from int
    TTSState(int i) : enumeration(i) {};

    /// get the name of the state
    std::string getName() const;

    /// get the long name of the state (name + hex code)
    std::string getLongName() const;

    /// get the short name of the state
    std::string getShortName() const;

    //     /// initialize TTS state 
    //     TTSState(std::string const& text);

    /// Assignment operator
    TTSState& operator = (int i) { _val = i; return *this; };


  };

}

/// output operator
std::ostream& operator<< (std::ostream& os, const tts::TTSState& state);

/// output operator
std::ostream& operator<< (std::ostream& os, const std::vector<tts::TTSState> & states);

#endif



  
