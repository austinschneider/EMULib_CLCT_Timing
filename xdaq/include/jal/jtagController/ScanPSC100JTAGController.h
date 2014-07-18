/**
*     @class ScanPSC100JTAGController
*
*     @short JTAG Controller implementation for National Semiconductor ScanPSC 100.
*            The implementation implements all methods defined in JTAGController.
*                  
*            The ScanPSC100JTAGController accesses the registers of
*            the controller through a ScanPSC100Adapter object which
*            has to be passed to the constructor.  After construction,
*            the user may set the JTAG clock frequency and the debug
*            level of the ScanPSC100JTAGController. All other
*            functions are usually used by JTAGChain objects, only.
*
*            Possible future features: auto-detect frequency of chain.
*
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/

#ifndef jal_SCANPSC100JTAGCONTROLLER_H
#define jal_SCANPSC100JTAGCONTROLLER_H

#include "jal/jtagController/JTAGController.h"

#include <stdint.h>

namespace jal {

  class ScanPSC100Adapter;

  class ScanPSC100JTAGController : public JTAGController {

  public:    
    /**
     * the constructor. Creates a new ScanPSC100JTAGController object. 
     *
     * @param adapter is a reference to a ScanPSC100Adapter which is used to access the ScanPSC100 registers.
     *
     * @param SCKfrequency is the (fixed) system clock frequency of the Scanpsc100 in Hz. A default of 10 MHz 
     *        is used, corresponding to the fastest possible (?) JTAG clock. It is better to err on the side 
     *        of higher frequncies in this parameter: specifying a higher frequency than actually used in hardware, 
     *        causes pulseTCK commands to run longer than intended (which does not cause any harm). 
     *
     */
    ScanPSC100JTAGController(ScanPSC100Adapter& adapter, double SCKfrequency = 10.e6);

    virtual ~ScanPSC100JTAGController() {};
  
    /// return the number of JTAG chains supportes by the JTAG controller. A ScanPSC100 supports 2 chains
    virtual uint32_t numberOfChains() { return 2; }; 

    /// select the JTAG chain active for subsequent commands (@param ichain = 0 or 1)
    virtual void selectChain(int ichain)
      throw(jal::HardwareException,
	    jal::OutOfRangeException);

    /// Set the desired TCK frequency (in Hz) for subsequent commands.
    /// The ScanPSC100JTAGController remembers the desired
    /// frequency in order to scale subsequent cycle numbers in the pulseTCK commnd.
    /// @param f is the desired frequency in Hz or -1. if the default frequency is to be used.
    virtual void setDesiredTCKFrequency (double f) 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { _desiredTCKfrequency = f; };

    /// send a sequence on the TMS line of the active chain (max. 16 bits)
    virtual void sequenceTMS(uint32_t bitcount, uint32_t sequence)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /** shift bits through the active JTAG chain
     *
     * @param bitcount is the number of bits to shift
     * @param data_out contains the bits. The first bit to be shifted is the LSB of the first byte in the vector.
     *           if the vector contains less bits than specified by bitcount, then bits of zeros are shifted for the missing bits.
     *           Attention: In this implementation, if data_out.size() is zero, no data will be written to the TDO shifter/buffer 
     *           and therefore the bit value from the previous TDO operation will be shifted into the target chain.
     *           
     * @param data_in is filled with the bits read from the JTAG chain, if the parameter doRead is true. If the vector 
     *           is too small to contain all the bits, it is resized to contain all the bits. If bitcount is not a multiple of 8, 
     *           then the last bit(s) scanned through the chain will be stored in the lowermost bits of the last byte in in_data.
     * @param doRead specifies that data is to be read back form the chain
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
    ///
    /// @parma num_tcks is the number of JTAG clock cycles.
    /// @param tmshigh is ignored since TMS is set by the last sequenceTMS command. 
    /// @param stage : full operation on jal::PULSESTAGE_ALL and jal::PULSESTAGE_PRE. 
    ///                No operation on jal::PULSESTAGE_PAUSE
    virtual void pulseTCK(uint32_t num_tcks, 
			  bool tmshigh = false, 
			  jal::PulseStage stage = jal::PULSESTAGE_ALL)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// lock the controller
    virtual void lock();

    /// unlock the controller
    virtual void unlock();

    /// set Frequency of the ScanPSC100 system clock (in Hz)
    void setSCKFrequency(double f) { _SCK_frequency = f; };

    /// get Frequency of the ScanPSC100 system clock (in Hz)
    virtual double getSCKFrequency() 
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { return _SCK_frequency; }; 
  
    /// set debug flag (0..3 no debug, 4: debug, 5: debug & no hardware access)
    virtual void setDebugFlag (int f) { _debug_flag = f; };

    /// initialize the ScanPSC100 JTAG Controller.
    virtual void init()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

  protected:
    virtual uint32_t readTCKCounter()
      throw(jal::HardwareException,
	    jal::OutOfRangeException);

    virtual void writeTCKCounter(uint32_t count)
      throw(jal::HardwareException,
	    jal::OutOfRangeException);

    virtual void waitForPSC(uint8_t status_mask, uint32_t times_to_check = 1)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    /// check if the controller is initialized. if not, initialize it
    virtual void init_check()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException);

    ScanPSC100Adapter& _adapter;
    int _currentChain;

    double _SCK_frequency; // the actual SCK frequency
    double _desiredTCKfrequency;
    int _debug_flag;         
    bool _initialized;
  };

}

#endif //jal_SCANPSC100JTAGCONTOLLER_H
