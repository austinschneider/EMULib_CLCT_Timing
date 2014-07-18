/**
 *     @class JTAGSVFCommand
 *
 *     @short Abstract base class for a JTAG SVF command. Objects of this class or
 *            its derived classes store one SVF command. The objects provide
 *            an execute method that plays the command on a JTAGSVFChain.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommand_H
#define jal_JTAGSVFCommand_H

#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/TimeoutException.h"
#include "jal/jtagController/OutOfRangeException.h"
#include "jal/jtagSVFSequencer/SVFSyntaxException.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <iostream>

namespace jal {

  enum CommandStage { CMDSTAGE_PRE, CMDSTAGE_PAUSE, CMDSTAGE_POST };

  class JTAGSVFChain;

  class JTAGSVFCommand {
  public: 
    JTAGSVFCommand() {};
    virtual ~JTAGSVFCommand() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) = 0;

    /// execute the command in stages. returns true if successful, false if not.
    virtual bool executeStage (JTAGSVFChain& svf_ch, jal::CommandStage stage) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) { 
    
      if (stage == CMDSTAGE_PRE)
	return execute (svf_ch);
      else
	return true;

    };

    /// print the object
    friend std::ostream& operator<<(std::ostream &os, const JTAGSVFCommand& d) {
      return d.display(os);
    };

  protected:
    virtual std::ostream& display(std::ostream& os) const = 0;
  };

}
#endif
