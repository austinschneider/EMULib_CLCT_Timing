/**
 *     @class JTAGSVFCommandFrequency
 *
 *     @short JTAG SVF Frequency command.
 *            Sets the maximum frequency in Hz.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFrequency_H
#define jal_JTAGSVFCommandFrequency_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"

namespace jal {

  class JTAGSVFCommandFrequency : public JTAGSVFCommand {
  public:
  
    /// constructor
    /// @param f is the frequency in Hz or -1. if the frequency should be set back to the default.

    JTAGSVFCommandFrequency(double f) : 
      _frequency(f) {};

    /// destructor.
    virtual ~JTAGSVFCommandFrequency() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      svf_ch.setFrequency ( _frequency );
      return true;

    };
 
  protected:
    virtual std::ostream& display(std::ostream& os) const {

      if (_frequency != -1.)
	os << "Command FREQUENCY " << _frequency << " Hz" << std::endl;
      else
	os << "Command FREQUENCY. (return to original frequency) " << std::endl;      

      return os;

    }

    double _frequency;
  };

}
#endif
