/**
*     @class ByteBlasterJTAGController
*
*     @short JTAG Controller implementation for a ByteBlaster cable connected to the parallel port.
*
*            ByteBlasterJTAGController implements all methods defined in JTAGController.
*            The implementation servers as an example how the JTAG Access Library can be used over the
*            parallel port. The implementation works and has been tested with a ByteBlaster cable,
*            but is not very sophisticated. The implementation currently works on Linux, only and
*            the resulting executable has to be run with permissions to access the parport device.      
*            (as root or as member of the lp gourp)
*
*            To be done: include delays in order to work at the desired frequency
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:06 $
*
*
**/

#ifndef jal_BYTEBLASTERJTAGCONTROLLER_H
#define jal_BYTEBLASTERJTAGCONTROLLER_H

#include "jal/jtagController/JTAGController.h"

#include <stdint.h>

namespace jal {

  class ByteBlasterJTAGController : public JTAGController {

  public:    
    /**
     * the constrcutor needs to be passed a ByteBlasterAdapter which is used to access the ByteBlaster registers 
     */
    ByteBlasterJTAGController();
    virtual ~ByteBlasterJTAGController();
  
    /// return the number of JTAG chains supportes by the JTAG controller. A ByteBlaster JTAG Controller supports 1 chain
    virtual uint32_t numberOfChains() { return 1; }; 

    /// select the JTAG chain active for subsequent commands. This just returns, 
    /// since the controller only supports one chain.
    virtual void selectChain(int ichain) 
      throw(jal::HardwareException,
	    jal::OutOfRangeException) { return; }; 

    /// Set the desired TCK frequency (in Hz) for subsequent commands.
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
     * @param doRead specifies that data is to be read back form the chain
     * @param autoTMS specifies that TMS should automatically go high while shifting 
     *        the last bit in order to move the JTAG state machine to the EXIT1 state
     *
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

    /// get frequency of the JTAG System Clock in Hz.
    /// may be needed by the chain in order to convert microseconds into cycles
    virtual double getSCKFrequency()    
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) { return _desiredTCKfrequency; };

    /// set debug flag (0..3 no debug, 4: debug, 5: debug & no hardware access)
    virtual void setDebugFlag (int f) { _debug_flag = f; };

    /// initialize the ByteBlaster JTAG Controller.
    /// this method is automatically called by the constructor
    virtual void init()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException); 

  private:
    /// return a (negated) byte from the parallel port status register
    uint8_t readJTAG();
  
    /// write a byte to the parallel port.
    void writeJTAG(uint8_t data);

    /// tri-state control: state = true: go to high impedance, state = false: normal operation 
    void trst(bool state);

    double _desiredTCKfrequency;
    int _debug_flag;

    uint8_t _perm_bits, _port_value;

    bool _initialized;
    int _fd;
  };

}
#endif //jal_BYTEBLASTERJTAGCONTOLLER_H
