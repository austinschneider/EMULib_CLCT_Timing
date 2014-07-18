/**
 *     @class JTAGSVFCommandEnddr
 *
 *     @short JTAG SVF ENDDR command.
 *            (Set the endstate for data register scans.)
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandEnddr_H
#define jal_JTAGSVFCommandEnddr_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"
#include "jal/jtagChain/JTAGState.h"

namespace jal {

class JTAGSVFCommandEnddr : public JTAGSVFCommand {
 public:
  JTAGSVFCommandEnddr(JTAGState s) : 
    _endstate(s) {};

  virtual ~JTAGSVFCommandEnddr() {};

  /// execute the command. returns true if successful, false if not.
  virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
    return svf_ch.ENDDR( _endstate );

  };
 
 protected:
  virtual std::ostream& display(std::ostream& os) const {

    os << "Command ENDDR " << _endstate << std::endl;
    return os;

  }
  JTAGState _endstate;
};

}

#endif
