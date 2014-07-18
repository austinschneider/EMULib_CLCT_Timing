/**
 *     @class JTAGSVFCommandGotoState
 *
 *     @short JTAG SVF STATE command.
 *            (if no path is specified)
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandGotoState_H
#define jal_JTAGSVFCommandGotoState_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"
#include "jal/jtagChain/JTAGState.h"

#include <vector>

namespace jal {

  class JTAGSVFCommandGotoState : public JTAGSVFCommand {
  public:
    JTAGSVFCommandGotoState(JTAGState state) : 
      _state(state) {};

    virtual ~JTAGSVFCommandGotoState() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      svf_ch.gotoState( _state );
      return true;

    };
 
  protected: 
    virtual std::ostream& display(std::ostream& os) const {

      os << "Command STATE " << _state << std::endl;
      return os;

    }

    JTAGState _state;
  };

}
#endif
