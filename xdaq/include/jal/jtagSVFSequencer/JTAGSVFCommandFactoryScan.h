/**
 *     @class JTAGSVFCommandFactoryScan
 *
 *     @short JTAG SVF Command Factory for Scan Commands.
 *            
 *            Parses the SDR, SIR, HDR, HIR, TDR, or TIR
 *            commands and creates a scan command object.
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryScan_H
#define jal_JTAGSVFCommandFactoryScan_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommandScan.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <stdint.h>
#include <string>

namespace jal {

  class JTAGScanData;

  class JTAGSVFCommandFactoryScan : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryScan(JTAGSVFCommandScan::CmdType cmdtype) :
      _my_cmdtype(cmdtype), _previous_length(0), _first(true) {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryScan() {};

    /// create a command
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);

    /// reset the command factory
    virtual void reset() { _first = true; _previous_length = 0;}
 
  private:
    JTAGSVFCommandScan::CmdType _my_cmdtype;
    uint32_t _previous_length;
    bool _first;  
  };

}

#endif
