/**
 *     @class JTAGSVFCommandRunTest
 *
 *     @short JTAG SVF RUNTEST command.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandRunTest_H
#define jal_JTAGSVFCommandRunTest_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFChain.h"
#include "jal/jtagChain/JTAGState.h"

#include <vector>
#include <stdint.h>


namespace jal {

  class JTAGSVFCommandRunTest : public JTAGSVFCommand {
  public:

    /// constructor
    ///
    /// note: if both nclk and mintime are specified, then both conditions must be met before the 
    ///       command finishes.
    ///
    /// note: if maxtime is specified, the command finishes after maxtime, even if the number of clocks 
    ///       was not reached.
    ///
    /// @param nclk number of clocks to stay in runtest mode (or 0 if not specified)
    /// @param runstate state in which to perfrom runtest (or JTAGState::UNDEF if not specified)
    /// @param endstate state to which to change after runtest (or JTAGState::UNDEF if not specified)
    /// @param mintime minimum time to perform RUNTEST in seconds (or -1.0 if not specified)
    /// @param maxtime maximum time to perform RUNTEST in seconds (or -1.0 if not specified)
    /// @param sysclock is true ie sysclock is to be used instead of test clock 
    ///

 
    JTAGSVFCommandRunTest(uint32_t nclk, JTAGState runstate, JTAGState endstate, 
			  double mintime, double maxtime, bool sysclock)
      : _nclk(nclk), _runstate(runstate), _endstate(endstate), 
      _mintime(mintime), _maxtime(maxtime), _sysclock(sysclock) {};

    virtual ~JTAGSVFCommandRunTest() {};

    /// execute the command. returns true if successful, false if not.
    virtual bool execute (JTAGSVFChain& svf_ch) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      svf_ch.runTest(_nclk, _runstate, _endstate, _mintime, _maxtime, _sysclock);
      return true;

    };
 
    /// execute the command in stages. returns true if successful, false if not.
    virtual bool executeStage (JTAGSVFChain& svf_ch, jal::CommandStage stage) const
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException) {
    
      if (stage == jal::CMDSTAGE_PRE)
	svf_ch.runTest(_nclk, _runstate, _endstate, _mintime, _maxtime, _sysclock, jal::RTSTAGE_PRE);
      else if (stage == jal::CMDSTAGE_PAUSE)
	svf_ch.runTest(_nclk, _runstate, _endstate, _mintime, _maxtime, _sysclock, jal::RTSTAGE_PAUSE);
      else if (stage == jal::CMDSTAGE_POST)
	svf_ch.runTest(_nclk, _runstate, _endstate, _mintime, _maxtime, _sysclock, jal::RTSTAGE_POST);

      return true;

    };
 
  protected:
    virtual std::ostream& display(std::ostream& os) const {

      os << "Command RUNTEST RUNSTATE=" << _runstate
	 << " nclk=" << _nclk << (_sysclock?" SCK":" TCK")
	 << " mintime= " << _mintime << " SEC" 
	 << " maxtime= " << _maxtime << " SEC" 
	 << " ENDSTATE=" << _endstate << std::endl;
      return os;

    }

  private:
    uint32_t _nclk;
    JTAGState _runstate, _endstate;
    double _mintime, _maxtime;
    bool _sysclock;
  
  };

}
#endif

