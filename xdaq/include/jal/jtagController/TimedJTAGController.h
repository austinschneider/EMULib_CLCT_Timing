/**
*     @class TimedJTAGController
*
*     @short JTAGController with benchmarking functions.
*
*
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/

#ifndef jal_TIMEDJTAGCONTROLLER_H
#define jal_TIMEDJTAGCONTROLLER_H

#include "jal/jtagController/JTAGController.h"
#include "hal/linux/StopWatch.hh"

#include <string>
#include <stdint.h>

namespace jal {

  class TimedJTAGController : public JTAGController {


  public:    
    ///
    /// the constructor 
    ///
    /// @param jc is a pointer to a JTAGController which has to exist for teh entire lifetime of the TimedJTAGController
    ///
    TimedJTAGController( JTAGController *jc ) : 
      _jc(jc), _sw(1), _time_pulse(0), _time_shift(0), _time_TMS(0), 
      _ticks_pulse(0), _nshift(0), _nshift_wrbits(0), _nshift_rwbits(0), _desiredClockFrequency(1.e6) {};

    virtual ~TimedJTAGController() { };
  
    /// send a sequence on the TMS line of the active chain (max. 16 bits)
    virtual void sequenceTMS(uint32_t bitcount, uint32_t sequence) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) {

      _sw.start();
      _jc->sequenceTMS(bitcount, sequence);
      _sw.stop();
      _time_TMS += _sw.read();
    }; 

    /** shift bits through the active JTAG chain
     *
     * @param doRead specifies that data is to be read back form the chain
     * @param autoTMS specifies that TMS should automatically go high while shifting 
     *        the last bit in order to move the JTAG state machine to the EXIT1 state
     *
     */
    virtual void shift(uint32_t bitcount, std::vector<uint8_t> const & data_out, std::vector <uint8_t> & data_in, bool doRead, bool autoTMS = true) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) {

      _sw.start();
      _jc->shift(bitcount, data_out, data_in, doRead, autoTMS);
      _sw.stop();
      _time_shift += _sw.read();
      _nshift++;
      if (doRead)
	_nshift_rwbits += bitcount;
      else
	_nshift_wrbits += bitcount;
    };

    /// pulse the JTAG clock num_tck times
    ///
    /// @param tmshigh indicates whether TMS should be high while pulsing the clock.
    ///        needed for RUNTEST in RESET state
    virtual void pulseTCK(uint32_t num_tcks, bool tmshigh = false, jal::PulseStage stage = jal::PULSESTAGE_ALL) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) {

      _sw.start();
      _jc->pulseTCK(num_tcks, tmshigh, stage);
      _sw.stop();
      _time_pulse+=_sw.read();
      _ticks_pulse+=num_tcks;
    };



    virtual uint32_t numberOfChains() { return _jc->numberOfChains(); };

    virtual void selectChain(int ichain)
      throw(jal::HardwareException,
	    jal::OutOfRangeException) { _jc->selectChain(ichain); };

    virtual void setDesiredTCKFrequency (double f)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { _jc->setDesiredTCKFrequency(f); if (f>0.) _desiredClockFrequency = f;}

    virtual double getSCKFrequency()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { return _jc->getSCKFrequency(); }

    virtual void lock() { _jc->lock(); }

    virtual void unlock() { _jc->unlock(); }

    virtual void setDebugFlag (int f) { _jc->setDebugFlag(f); } 

    void printTimingStats() {
      std::cout << "Time spent in pulseTck:    " << (_time_pulse / 1.e6) << " sec "
		<< "(" << _ticks_pulse << " or " << (_ticks_pulse / _desiredClockFrequency) << " sec given by SVF file)" << std::endl << std::endl;
      std::cout << "Time spent in shift:       " << (_time_shift / 1.e6) << " sec " 
		<< "(" << _nshift << " calls, " 
		<< _nshift_wrbits << " bit writes, " 
		<< _nshift_rwbits << " bit write/reads)" << std::endl;
      std::cout << "Time spent in sequenceTMS: " << (_time_TMS / 1.e6) << " sec " << std::endl;
    };

  private:
    JTAGController* _jc;
    HAL::StopWatch _sw;
    uint32_t _time_pulse;
    uint32_t _time_shift;
    uint32_t _time_TMS;
    uint64_t _ticks_pulse;
    uint64_t _nshift;
    uint64_t _nshift_wrbits;
    uint64_t _nshift_rwbits;

    double _desiredClockFrequency;
  };

}
#endif 
