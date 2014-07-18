/**
 *     @class JTAGSVFCommandGotoStateByPath
 *
 *     @short JTAG SVF STATE command.
 *            (If path is specified)
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandGotoStateByPath_H
#define jal_JTAGSVFCommandGotoStateByPath_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"
#include "jal/jtagChain/JTAGState.h"

#include <vector>

namespace jal {

  class JTAGSVFCommandGotoStateByPath : public JTAGSVFCommand {
  public:
    JTAGSVFCommandGotoStateByPath(std::vector<JTAGState> const& statepath) : 
      _statepath(statepath) {};

    virtual ~JTAGSVFCommandGotoStateByPath() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      svf_ch.gotoStateByPath( _statepath );
      return true;

    };
 
  protected:
    virtual std::ostream& display(std::ostream& os) const {

      os << "Command STATE";

      std::vector<JTAGState>::const_iterator it = _statepath.begin();
      for (; it != _statepath.end(); it++ )
	os << " " << (*it);

      os << std::endl;
      return os;
    }

    std::vector<JTAGState> _statepath;
  };

}
#endif
