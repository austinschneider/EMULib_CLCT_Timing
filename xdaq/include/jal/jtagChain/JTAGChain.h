/**
 *     @class JTAGChain
 *
 *     @short A JTAG chain. Implements high-level commands such as scanDR, scanIR on a JTAG chain. 
 *
 *            The JTAG chain uses a JTAG Controller to access a JTAG chain in hardware. 
 *            The JTAG chain provides all high-level functions that can be performed on a JTAG chain. 
 *            This class can be the basis for any JTAG access needed in the online software.
 *            
 *            Specifically, this class encapsulates the handling of the JTAG state machine.
 *            A JTAGChain object 'knows' about the current (stable) state of the hardware state machine.
 *            Therefore, only one JTAGChain object may be instantiated for each JTAG chain in the hardware. 
 *
 *            Multiple JTAG chains may be handled by the same JTAG Controller. In order to uses these
 *            chains concurrently from different threads, the JTAGChain locks the controller and switches 
 *            it to the right chain number before each operation.
 *
 *            It may be desirable that a JTAGChain can be shared by multiple threads. In this special
 *            case the threads should use the lock() and unlock() methods of the JTAGChain to arbitrate 
 *            access to the chain.
 * 
 *            This class corresponds to the NI scanlib.c with the difference that it does not remember the end states.  
 *            
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:05 $
 *
 *
**/

#ifndef jal_JTAGCHAIN_H
#define jal_JTAGCHAIN_H

#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/TimeoutException.h"
#include "jal/jtagController/OutOfRangeException.h"

#include "jal/jtagChain/JTAGState.h"

#include <vector>
#include <iomanip>
#include <stdint.h>

namespace jal {

  enum RunTestStage { RTSTAGE_ALL, RTSTAGE_PRE, RTSTAGE_PAUSE, RTSTAGE_POST };

  class JTAGScanData;
  class JTAGController;

  class JTAGChain {
  public:


    /** constructor. Creates a new JTAGChain object. 
     *
     * @param ctrl is a reference to a JTAG Controller which it used to access the JTAG Chain.
     * @param ichain is the number of the chain on the given Controller. The default chain number is 0
     *        (to be used for example with controllers that only support one chain).
     * @param desiredTCKfrequency is the desired TCK frequency in Hz. 
     *        It is passed to the controller before issuing a command so that the
     *        controller can cange the frequency or scale the number of clock cycles.
     *        The default value is -1., indicating that the controller's default frequency 
     *        is to be used.
     */
    JTAGChain(JTAGController& ctrl, uint32_t ichain = 0, double desiredTCKfrequency = -1.);

    /// Set the desired TCK frequency (in Hz) for subsequent commands. 
    ///
    /// This frequency is passed to the controller before a command is executed using
    /// the JTAGController::setDesiredTCKFrequency() method. 
    ///
    /// @param f is the desired clock frequency in Hz or -1. if the default frequency is to be used.
    void setDesiredTCKFrequency (double f) { _desiredTCKfrequency = f; };

    /// Do a JTAG data register scan. Then go to endstate. Read back the response only if doRead is true. 
    void scanDR(uint32_t numBits, 
		JTAGScanData const& input, 
		JTAGScanData & response, 
		bool doRead = true, 
		JTAGState endstate = JTAGState::IDLE)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// Do a JTAG instruction register scan. Then go to endstate. Read back the response only if doRead is true. 
    void scanIR(uint32_t numBits, 
		JTAGScanData const& input, 
		JTAGScanData & response, 
		bool doRead = true, 
		JTAGState endstate = JTAGState::IDLE)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// Move the JTAG Test Access Port to a (stable !) JTAG state 
    /// If the state of the hardware is unknown (after contructing the chain), 
    /// the method does a reset (send 8 bits of 1 on the TMS line).
    void gotoState(JTAGState state)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// run the JTAG clock for a number of cycles in state runstate, then go to endstate
    ///
    /// @param nclk number of cycles to run (or 0 if only mintime is specified)
    /// @param mintime is the minimum time in seconds
    /// @param maxtime is the maximum time in seconds (not implemented)
    /// @param stage allows to split execution of RUNTEST into stages.
    ///        on jal::RTSTAGE_ALL, the full command is executed.
    ///        on jal::RTSTAGE_PRE, only the commands preceding a possible pause are executed.
    ///        on jal::RTSTAGE_PAUSE, a possible pause is executed (the state of the JTAGChain remains constant).
    ///        on jal::RTSTAGE_POST, only the commands after a possible pause are executed.
    ///        
    ///        when programming multiple chains in parallel, the jal::RTSTAGE_PAUSE stage needs to be executed only on one of the chains
    void runTest(uint32_t nclk, 
		 JTAGState runstate = JTAGState::IDLE, 
		 JTAGState endstate = JTAGState::IDLE,
		 double mintime = -1., 
		 double maxtime = -1.,
		 jal::RunTestStage stage = jal::RTSTAGE_ALL)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// reset the Test Access Port (resulting TAP state = JTAGState::RESET)
    /// sends 8 bits of 1 on the TMS line regardless of the state the chain is in 
    void resetTAP()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// Move the JTAG Test Access Port to a (stable !) JTAG state on a specified path.
    /// The statepath must specify a valid path through the JTAG state machine. The 
    /// last element in statepath has to be a stable JTAG state.
    /// This rarely used function is implemented since it is defined in the SVF language.
    void gotoStateByPath(std::vector<JTAGState> statepath)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// lock the chain; foreseen for the (unlikely) case that multiple threads use the same JTAG chain concurrently
    void lock();

    /// unlock the chain; foreseen for the (unlikely) case that multiple threads use the same JTAG chain concurrently
    void unlock();

  private:
    void toState(JTAGState state)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    void doScan(bool irscan, 
		uint32_t numBits, 
		JTAGScanData const& input, 
		JTAGScanData & response, 
		bool doRead, 
		JTAGState endstate)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    JTAGController& _controller;
    int _chainNumber;

    /** current state of the chain. */
    JTAGState _current_chain_state;
    double _desiredTCKfrequency;
  };

}
#endif //jal_JTAGCHAIN_H
