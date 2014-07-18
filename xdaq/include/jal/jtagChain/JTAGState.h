/**
 *     @class JTAGState
 *
 *     @short JTAG State class
 *
 *            An enumeration of possible JTAG states. The first four states are stable:
 *            JTAGState::RESET, JTAGState::IDLE, JTAGState::PAUSEDR, JTAGState::PAUSEIR
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:05 $
 *
 *
**/

#ifndef jal_JTAGSTATE_H
#define jal_JTAGSTATE_H

#include <string>

namespace jal {

  /// Helper class for extensible enumerations
  class jalenumeration
    {
    public:
      // convert to/from int
      operator int() const { return _val; }
      jalenumeration& operator = (int i) { _val = i; return *this; }
      // Operators ==, !=, <, etc. can be implemented using int conversion
    protected:
      jalenumeration(int i = 0) { _val = i; }
      int _val;
    };


  class JTAGState : public jalenumeration {
  public:
    enum { RESET = 0, IDLE = 1, PAUSEDR = 2 ,PAUSEIR = 3,
	   SEDR =  4, CPDR =  5, SHDR =  6, E1DR =  7, E2DR =  8, UPDR = 9,
	   SEIR = 10, CPIR = 11, SHIR = 12, E1IR = 13, E2IR = 14, UPIR = 15, UNDEF = 16, _next };
    JTAGState(int i) : jalenumeration(i) {};

    /// initialize JTAG state with string TAP state name according to SVF specification
    JTAGState(std::string const& text);

    /// Assignment operator
    JTAGState& operator = (int i) { _val = i; return *this; }; 
  
    /// is the state one of the four stable states (not counting the shift states) 
    bool isStable() { return _val <= PAUSEIR; };
  };

}

#endif //jal_JTAGSTATE_H
