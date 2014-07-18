/**
*     @class DTTFJTAGController
*
*     @short JTAG Controller implementation for the built-in CMS Drift Tube Track Finder (DTTF) JTAG Controller.
*
*            The CMS Drift Tube Track Finder (DTTF) JTAG Controller is implemented as firmware in an Altera FPGA. 
*            Most operations are compatible to the ones of a National Semiconductor ScanPSC 100, but there are 
*            some differences: write only mode, read only mode, double buffernig and loop back tests are not 
*            supported.
*
*            The DTTFJTAGController class implements these differences.
*                  
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/

#ifndef jal_DTTFJTAGCONTROLLER_H
#define jal_DTTFJTAGCONTROLLER_H

#include "jal/jtagController/JTAGController.h"
#include "jal/jtagController/ScanPSC100JTAGController.h"
#include "jal/jtagController/Timer.h"

#include <stdint.h>

namespace jal {

  class ScanPSC100Adapter;

  class DTTFJTAGController : public ScanPSC100JTAGController {

  public:    
    /**
     * the constructor. Creates a new DTTFJTAGController object. 
     *
     * @param adapter is a reference to a ScanPSC100Adapter which is used to access the ScanPSC100 registers.
     * @param SCKfrequency is the (fixed) system clock frequency of the DTTF JTAG controller in Hz. A default of 10 MHz 
     *        is used, corresponding to the fastest possible (?) JTAG clock. SIt is better to err on the side 
     *        of higher freuqncies in this parameter: specifying a higher frequency than actually used in hardware, 
     *        causes pulseTCK commands to run longer than intended (which does not cause any harm). 
     *
     */
    DTTFJTAGController(ScanPSC100Adapter& adapter, double desiredTCKfrequency = 10.e6);

    /// d-tor
    virtual ~DTTFJTAGController() {};
   
    /** shift bits through the active JTAG chain
     *
     * the method differs from ScanPSC100JTAGController::shift() as the DTTF controller does not support
     * write only mode, read only mode and double buffering.
     * 
     * @param bitcount is the number of bits to shift
     * @param data_out contains the bits. The first bit to be shifted is the LSB of the first byte in the vector.
     *           if the vector contains less bits than specified by bitcount, then bits of zeros are shifted for the missing bits.
     *           Attention: In this implementation, if data_out.size() is zero, only bits of zero will be shifted into the chain.
     *           
     * @param data_int is filled with the bits read from the JTAG chain, if the parameter doRead is true. If the vector 
     *           is too small to contain all the bits, it is resized to contain all the bits. If bitcount is not a multiple of 8, 
     *           then the last bit(s) scanned through the chain will be stored in the lowermost bits of the last byte in in_data.
     * @param doRead is ignored by the DTTF JTAG controller. The DTTF JTAG controller always 
     *        performs a read
     * @param autoTMS specifies that TMS should automatically go high while shifting 
     *        the last bit in order to move the JTAG state machine to the EXIT1 state
     */

    virtual void shift(uint32_t bitcount, 
		       std::vector<uint8_t> const & data_out, 
		       std::vector <uint8_t> & data_in,
		       bool doRead, 
		       bool autoTMS = true)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// pulse the JTAG clock num_tck times
    /// @param tmshigh is ignored since TMS is set by the last sequenceTMS command.
    /// @param stage: on jal::PULSESTAGE_ALL perform full operation, on jal::PULSESTAGE_PRE only do two pulses
    ///        on jal::PULSESTAGE_PAUSE, perform a wait
    virtual void pulseTCK(uint32_t num_tcks, bool tmshigh = false, jal::PulseStage stage = jal::PULSESTAGE_ALL)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// initialize the DTTF JTAG Controller. This method differs from ScanPSC100JTAGController::init()
    /// as the DTTF JTAG Controller does not support loopback testing.
    virtual void init()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

  private:
    jal::Timer _timer;
  };

}

#endif //jal_DTTFJTAGCONTOLLER_H
