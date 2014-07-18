/**
 *     @class JTAGSVFCommandScan
 *
 *     @short JTAG SVF command for scan operations and header/trailer commands.
 *            SDR, SIR, HDR, HIR, TDR, TIR 
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandScan_H
#define jal_JTAGSVFCommandScan_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"

namespace jal {

  class JTAGSVFCommandScan : public JTAGSVFCommand {
  public:
    enum CmdType { SDR, SIR, HDR, HIR, TDR, TIR};

    JTAGSVFCommandScan(JTAGSVFData const& d, CmdType type) : 
      _d(d), _type(type) {};

    virtual ~JTAGSVFCommandScan() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {

      switch (_type) {
      case SDR : return svf_ch.SDR(_d); break;
      case SIR : return svf_ch.SIR(_d); break;
      case HDR : svf_ch.HDR(_d); return true; break;
      case HIR : svf_ch.HIR(_d); return true; break;
      case TDR : svf_ch.TDR(_d); return true; break;
      case TIR : svf_ch.TIR(_d); return true; break;
      default: return false;
      }

    };
 
  protected:
    virtual std::ostream& display(std::ostream& os) const {

      char* cmd_txt[] = { "SDR", "SIR", "HDR", "HIR", "TDR", "TIR" };
      os << "Command " << cmd_txt[_type] << " " << _d;
      return os;

    }

    JTAGSVFData _d;
    CmdType _type;
  };

}
#endif
