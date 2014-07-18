/**
*     @class CMSDAQJTAGController
*
*     @short JTAG Controller implementation used in the PCI cards for the CMD DAQ group.
*
*            The CMSDAQJTAGController is similar to the ByteBlaster Interface. There is
*            one single register with three writable bits (TDI, TMS and CLK) amd one 
*            readable bit (TDO). TMS and TDI sequences are produced by writing bit after
*            bit to the register. If the TDO ist to be read it has to be read after writing a 
*            bit to the TDI.
*
*            Clock behavior: When writing a bit to TMS and/or TDI, the bits are first written
*            with the clock low and then written a second time with the clock high. The clock then 
*            remains high until the next bit is shifted. TDO is read after the second write 
*            command.
*
*            Timing: No delays are inserted between successive write commands to the register. 
*            It is assumed that the overhead of software and PCI access is large in order 
*            enough not exceed tha maximum JTAG speed. 
* 
*            Performance measurements on a PIII-800 using an external Mini-PCI crate:
*
*                                                                    max frequency w/o HAL   
*                                          with HAL    w/o HAL     (writes only)  (write/read)
*              Memory space - PCI read        4.3 us    2.9 us                       260 kHz
*              Memory spcae - PCI write       1.8 us    0.5 us         1 MHz
*
*              Config space - PCI read        9.8 us    6.7 us                        50 kHz
*              Config spcae - PCI write      10.2 us    6.7 us         75 kHz
*
*       @see ---
*    @author Hannes Sakulin
* $Revision: 1.1 $
*     $Date: 2007/03/27 07:59:06 $
*
*
**/

#ifndef jal_CMSDAQJTAGCONTROLLER_H
#define jal_CMSDAQJTAGCONTROLLER_H
#include "jal/jtagController/JTAGController.h"
#include "jal/jtagController/Timer.h"

#include <string>
#include <stdint.h>

namespace HAL {
class PCIDevice;
}

namespace jal {

  class CMSDAQJTAGController : public JTAGController {

  public:    
    /// the constructor 
    ///
    /// @param device is the reference to the HAL HardwareDevice (PCIDevice).
    ///
    /// @param jtag_reg_prefix is the prefix of the JTAG registers in the
    ///        HAL address table. The registers "ENABLE", "TDI_TMS_CLK" and "TDO",
    ///        prefixed with the jtag_reg_prefix must be defined 
    ///
    /// @param simulatePulsing is true if a time delay should be used instead of
    ///        actually pulsing the JTAG clock in the pulseTCK command. This option may give
    ///        more accurate delays, since the time neede for a clock pulse is determined by
    ///        the speed of the PCI accesses and therefore not exactly needed. 
    ///
    /// @param SCKFrequency indicates the speed of the CMSDAQJTAGController in hardware.
    ///        This speed is given by the speed of PCI accesses as two PCI accesses are
    ///        needed to complete one JTAG clock cycle. This parameter only
    ///        needs to be set if simulatePulsing is false, so that the number of requested 
    ///        pulses can be properly scaled in a pulseTCK command. 
    CMSDAQJTAGController(HAL::PCIDevice& device, 
			 std::string const& jtag_reg_prefix,
			 bool simulatePulsing = true,
			 double SCKFrequency = -1.)
      throw(jal::HardwareException);

    /// destructor
    virtual ~CMSDAQJTAGController();
  
    /// return the number of JTAG chains supportes by the JTAG controller. A CMSDAQJTAGController supports 1 chain
    virtual uint32_t numberOfChains() { return 1; }; 

    /// select the JTAG chain active for subsequent commands. This just returns, 
    /// since the controller only supports one chain.
    virtual void selectChain(int ichain)     
      throw(jal::HardwareException,
	    jal::OutOfRangeException) { return; }; 

    /// Set the desired TCK frequency (in Hz) for subsequent commands.
    ///
    /// This command has to be used (by the JTAGChain) before the first pulseTCK command
    /// so that the controller knows how to scale the number ot pulses or to convert
    /// them into a time delay.
    ///
    /// The other commands (shift, sequenceTMS) ignore the desired frequency as it is assumed
    /// that this implementation is always slower than the desired speed.
    ///
    /// @param f is the desired frequency in Hz.
    virtual void setDesiredTCKFrequency (double f)     
      throw(jal::HardwareException,
	    jal::OutOfRangeException) { _desiredTCKfrequency = f; };

    /// send a sequence on the TMS line of the active chain (max. 16 bits)
    ///
    /// @param bitcount is the number of bist (max 16).
    /// @param sequence contains teh bits. The LSB is shifted first.
    virtual void sequenceTMS(uint32_t bitcount, uint32_t sequence)
      throw(jal::HardwareException,
	    jal::TimeoutException,
	    jal::OutOfRangeException); 

    /// shift bits through the active JTAG chain
    ///
    /// @param bitcount is the number of bits to shift.
    /// @param data_out is the date to shift to teh chain.
    /// @param data_in is a reference to the data read from the chain (if doRead is true)
    /// @param doRead specifies that data is to be read back form the chain.
    /// @param autoTMS specifies that TMS should automatically go high while shifting 
    ///        the last bit in order to move the JTAG state machine to the EXIT1 state
    ///
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
    /// If the controller was instantiated in simulatepulsing mode, only one pulse is 
    /// actually written to the chain an the computer then sleeps for the time 
    /// corresponding to the number of ticks.
    ///
    /// If the controller is not in simulatepulsing mode, then the number of pulses is
    /// scaled accordind to the ratio of the clock frequency of the controller (PC/PCI)
    /// and the desired clock frequency of the chain (or the SVF file).
    ///
    /// @param num_tcks is the number of ticks
    /// @param tmshigh indicates whether TMS should be high while pulsing the clock.
    ///        needed for running a RUNTEST command in RESET state
    /// @param stage gives the stages to perform. 
    ///        It is in the range (jal::PULSESTAGE_ALL, jal::PULSESTAGE_PRE, jal::PULSESTAGE_PAUSE).
    ///
    ///        If stage = jal::RTSTAGE_ALL, then the full command is performed. 
    ///        For the other stage options the behavior depends the simulatepulsing optin in the constuctor.
    ///        If simulatepulsing is true, then only two JTAG clocks are pulsed when called with jal::PULSESTAGE_PRE
    ///        and only a pause statemant is issued  when called with jal::PULSESTAGE_PAUSE.
    ///
    ///        If simulatepulsing is false, then all operations
    ///        are performed when called with jal::PULSESTAGE_PRE, 
    ///        and nothing is donewhen called with jal::PULSESTAGE_PAUSE.
    ///
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
	    jal::OutOfRangeException) { return _sck_frequency; };

    /// set debug flag (0..3 no debug, 4: debug, 5: debug & no hardware access)
    virtual void setDebugFlag (int f) { _debug_flag = f; };

    /// initialize the CMSDAQJTAGController 
    /// this method is automatically called by all methods if not done before
    virtual void init()
      throw(jal::HardwareException);


  private:
    /// return a bit from the TDO
    ///
    /// the TDO bit is returned in the LSB
    uint8_t readJTAG()
      throw(jal::HardwareException);
  
    /// write three bits to the "TDI_TMS_CLK" register
    ///
    /// @param data is written to the JTAG register. 
    ///        TDI is in bit 6, TMS in bit1, CLK in bit 0 
    void writeJTAG(uint8_t data)
      throw(jal::HardwareException);

    HAL::PCIDevice & _device;
    std::string _jtag_reg_prefix;
    bool _simulatepulsing;
    double _sck_frequency;

    uint32_t _jtdo_addr;
    uint32_t _jtag_addr;
    bool _use_fast_access;

    double _desiredTCKfrequency;
    int _debug_flag;
    bool _initialized;

    jal::Timer _timer;
  };

}
#endif 
