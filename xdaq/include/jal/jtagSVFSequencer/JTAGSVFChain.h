/**
 *     @class JTAGSVFChain
 *
 *     @short A JTAG SVF chain. A JTAG Chain with header and trailer commands. 
 *
 *            Header and Trailer commands remember their states as       
 *            ENDIR, ENDDR and RUNTEST also remember their states according to 
 *            the SVF specifications.
 *            
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCHAIN_H
#define jal_JTAGSVFCHAIN_H

#include "jal/jtagChain/JTAGState.h"
#include "jal/jtagChain/JTAGChain.h"
#include "jal/jtagSVFSequencer/JTAGSVFData.h"

#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/TimeoutException.h"
#include "jal/jtagController/OutOfRangeException.h"
#include "jal/jtagSVFSequencer/SVFSyntaxException.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
                
#include <vector>
#include <stdint.h>
#include <iomanip>

namespace jal {

  class JTAGSVFChain {
  public:

    /// constructor. 
    // do not need to initialize SVFData: it will be empty using default constructors.
    JTAGSVFChain(JTAGChain& ch) :
      _ch(ch),
      _endstate_dr  (JTAGState::IDLE),
      _endstate_ir  (JTAGState::IDLE),
      _runstate     (JTAGState::IDLE),
      _endstate_run (JTAGState::IDLE),
      _executionProgress(0) {};

    ~JTAGSVFChain() {};

    /// set the desired frequency in Hz.
    ///
    /// This command is used by the SVFSequencer, if a FREQUENCY command
    /// is encountered in the SVF file. The JTAGSVFChain passes this command 
    /// to the JTAGChain.
    ///
    /// @param f is the frequency in Hz.
    void setFrequency(double f) { _ch.setDesiredTCKFrequency(f);} ;

    /// set data register scan header
    void HDR(JTAGSVFData const& d) 
      throw(jal::SVFSyntaxException) { _header_dr.update(d); };

    /// set instruction register scan header
    void HIR(JTAGSVFData const& d) 
      throw(jal::SVFSyntaxException) { _header_ir.update(d); };
  
    /// set data register scan trailer
    void TDR(JTAGSVFData const& d) 
      throw(jal::SVFSyntaxException) { _trailer_dr.update(d); };
  
    /// set instruction register scan trailer
    void TIR(JTAGSVFData const& d) 
      throw(jal::SVFSyntaxException) { _trailer_ir.update(d); };

    /// do an instruction register scan. Return true is successful, false if compare error.
    bool SIR(JTAGSVFData const& d)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException);

    /// do a data register scan. Return true is successful, false if compare error.
    bool SDR(JTAGSVFData const& d)      
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException,
	    jal::SVFSyntaxException);


    /// set dr scan endstate. Return true is successful, false if not a valid state.
    bool ENDDR(JTAGState s);


    /// set ir scan endstate. Return true is successful, false if not a valid state.
    bool ENDIR(JTAGState s);

    /// Move the JTAG Test Access Port to a stable JTAG state 
    void gotoState(JTAGState state) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { _ch.gotoState(state); };

    /// Move the JTAG Test Access Port to a stable JTAG state on a specified path.
    /// The statepath must specify a valid path through the JTAG state machine. The 
    /// last element in statepath has to be a stable JTAG state.
    void gotoStateByPath(std::vector<JTAGState> const& statepath) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { _ch.gotoStateByPath(statepath); };


    /// run the JTAG clock for a number of cycles in state runstate, then go to endstate
    void runTest(uint32_t nclk, 
		 JTAGState runstate, 
		 JTAGState endstate, 
		 double mintime, 
		 double maxtime, 
		 bool sysclock=false,
		 jal::RunTestStage stage = jal::RTSTAGE_ALL)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);


    /// reset the TAP
    void resetTAP() 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { _ch.resetTAP(); };

    /// control the test reset signal.
    //  bool TRST();

    /// lock the chain
    void lock() { _ch.lock(); };
  
    /// unlock the chain
    void unlock() { _ch.unlock(); };

    /// execute an SVF sequence
    ///
    /// returns true on success
    bool executeSequence(std::vector<jal::JTAGSVFCommand *> const& sequence, 
			 bool quietMode = false,
			 bool overrideErrors = false)
      throw (jal::HardwareException,
	     jal::TimeoutException,
	     jal::OutOfRangeException,
	     jal::SVFSyntaxException);

    /// get the execution process in per cent
    uint32_t getExecutionProgress() const { return _executionProgress; };


  private:
    /// check if response matched the expected response and the mask in data.
    bool check_response(JTAGScanData const& reponse, JTAGSVFData const& data);

    JTAGChain& _ch;

    /// current header and trailer settings
    JTAGSVFData _header_dr, _header_ir, _trailer_dr, _trailer_ir;
    JTAGSVFData _last_dr, _last_ir;

    JTAGState _endstate_dr, _endstate_ir;
    JTAGState _runstate, _endstate_run;

    uint32_t _executionProgress;
  };

}
#endif 
