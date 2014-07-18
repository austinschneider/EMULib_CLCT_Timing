/**
*     @class JTAGController
*
*     @short JTAG Controller abstract base class
*
*            A JTAG Controller provides access to one or more JTAG
*            chains in the hardware.  It provides basic
*            functionalities such as sequencing the TMS line shifting
*            data into and/or out of the chain and pulsing the
*            clock. A JTAG Controller is used by one or more JTAGChain
*            objects. Typically, the user will not need to call any
*            functions of the JTAGController except its constructor.
*
*            The controller provides a setDesiredTCKFrequency() method
*            to set the intended test clock frequency. If the
*            controller is able to control the frequency, it changes
*            to the correct frequency. The frequency is
*            then used for all operatiuons on TDI / TMS / ...
*            
*            If the controller is not able to control the frequency,
*            then it scales the number of clock cycles in a pulseTCK
*            command to achieve the intended delay time. This way the
*            chain can treat any controller as if the frequency was
*            configurable. The chain remembers its frequency and
*            always switches the controller to the right frequency
*            before issuing any command.
*            
*            Default frequency values:
*            
*            If a chain has not requested a certain frequency it will
*            run with the default frequency of the controller, i.e. no
*            scaling will be performed. For a controller with
*            configurable frequency, a default frequency has to be
*            defined (e.g. in the constructor ).
*            
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:07 $
*
*
**/


#ifndef jal_JTAGCONTROLLER_H
#define jal_JTAGCONTROLLER_H

#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/TimeoutException.h"
#include "jal/jtagController/OutOfRangeException.h"

#include <vector>
#include <stdint.h>

namespace jal {

  enum PulseStage { PULSESTAGE_ALL, PULSESTAGE_PRE, PULSESTAGE_PAUSE };

  class JTAGController {
  public:

    JTAGController() {};
    virtual ~JTAGController() {};

    /// returns the number of JTAG chains supported by the JTAG controller
    virtual uint32_t numberOfChains() = 0;

    /// select one of the chains of the JTAG controller as active chain for subsequent commands
    virtual void selectChain(int ichain)
      throw(jal::HardwareException,
	    jal::OutOfRangeException) = 0;

    /// Set the desired TCK frequency (in Hz) for subsequent commands.
    /// The controller either changes to the desired TCK frequency or remembers the desired
    /// frequency in order to scale subsequent cycle numbers in the pulseTCK commnd.
    ///
    /// @param f is the desired frequency in Hz or -1. if the default frequency is to be used.
    virtual void setDesiredTCKFrequency (double f)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) = 0;

    /// send a TMS seqence on the active JTAG chain (max. 16 bits)
    ///
    /// @param bitcount is the number of bits (max 16)
    /// @param sequence contain the sequence to be shifted (in the lowermost bits). Shifting starts with the LSB. 
    virtual void sequenceTMS(uint32_t bitcount, uint32_t sequence)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) = 0;

    /** shift bits through the active JTAG chain
     * 
     * @param bitcount is the number of bits to shift
     * @param data_out contains the bits. The first bit to be shifted is the LSB of the first byte in the vector.
     *           if the vector contains less bits than specified by bitcount, then bits of zeros are shifted for the missing bits.
     * @param data_in is filled with the bits read from the JTAG chain, if the parameter doRead is true. If the vector 
     *           is too small to contain all the bits, it is resized to contain all the bits. If bitcount is not a multiple of 8, 
     *           then the last bit(s) scanned through the chain will be stored in the lowermost bits of the last byte in in_data.
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
	    jal::OutOfRangeException) = 0;

    /// pulse the JTAG clock for a number of clock cycles
    ///
    /// @parma num_tcks is the number of JTAG clock cycles.
    /// @param tmshigh indicates whether TMS should be held high while clocking. 
    ///        (this is only needed for byteblaster style controllers which 
    ///        steer TMS and CLK with a single register).
    /// @param stage gives the stages to perform. 
    ///        It is in the range (jal::PULSESTAGE_ALL, jal::PULSESTAGE_PRE, jal::PULSESTAGE_PAUSE).
    ///
    ///        If stage = jal::RTSTAGE_ALL, then the full command should be performed. 
    ///        For the other stage options the behavior depends on the implementation:
    ///        If the implementation performs the pulseTCK by doing some preparation and then 
    ///        executing a pause, then only the preparation should be performed when called with jal::PULSESTAGE_PRE
    ///        and only the pause should be performed when called with jal::PULSESTAGE_PAUSE.
    ///
    ///        If the implementation does not separate the pulseTCK into two operations, then all operations
    ///        should be performed when called with jal::PULSESTAGE_PRE, 
    ///        and nothing should be done when called with jal::PULSESTAGE_PAUSE.
    ///
    virtual void pulseTCK(uint32_t num_tcks, bool tmshigh = false, jal::PulseStage stage = jal::PULSESTAGE_ALL)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) = 0;

    /// get the actual frequency of the JTAG System Clock in Hz.
    /// may be needed by the chain in order to convert microseconds into cycles
    virtual double getSCKFrequency()
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException) = 0;

    /// lock the JTAG controller software interface (needed if multiple threads use the same controller)
    virtual void lock() = 0;

    /// unlock the JTAG controller software interface (needed if multiple threads use the same controller)
    virtual void unlock() = 0;

    /// set the debug level
    virtual void setDebugFlag (int f) = 0;
  };

}

#endif //jal_JTAGCONTROLLER_H
