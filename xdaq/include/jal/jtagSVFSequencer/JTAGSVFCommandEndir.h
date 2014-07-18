/**
 *     @class JTAGSVFCommandEndir
 *
 *     @short JTAG SVF ENDIR command.
 *            (set the endstate for instruction register scans)
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandEndir_H
#define jal_JTAGSVFCommandEndir_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"
#include "jal/jtagChain/JTAGState.h"

namespace jal {

  class JTAGSVFCommandEndir : public JTAGSVFCommand {
  public:
    JTAGSVFCommandEndir(JTAGState s) : 
      _endstate(s) {};

    virtual ~JTAGSVFCommandEndir() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      return svf_ch.ENDIR( _endstate );

    };
 
  protected:
    virtual std::ostream& display(std::ostream& os) const {

      os << "Command ENDIR " << _endstate << std::endl;
      return os;

    }

    JTAGState _endstate;
  };

}

#endif
