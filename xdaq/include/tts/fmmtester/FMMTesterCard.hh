#ifndef _FMMTESTERCARD_H
#define _FMMTESTERCARD_H

/**
 *     @class FMMTesterCard
 *
 *     @short Class representing the basic functions of the FMMTester
 *
 *            Higher-level classes use this class to read and write
 *            data to/from the FMMTester and to perform basic functions
 *            such as a reset.
 *
 *            The tts::FMMTesterCard class is using a HAL PCIDevice in order to 
 *            access the tts::FMMTester.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:34 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "tts/ttsbase/TTSState.hh"
#include "tts/cpcibase/CPCICard.hh"

#include <vector>
#include <stdint.h>

namespace tts {

  class FMMTesterCard : public tts::CPCICard {
  
  public:
    /// c-tor
    ///
    /// @param fmmtdevice is a pinter to the HAL::PCIDevice used to access the hardware. 
    /// The FMMTesterCard becomes the owner of the HAL::PCIDevice  and is responsible for its destruction. 
    FMMTesterCard( HAL::PCIDevice* device, ipcutils::SemaphoreArray& cratelock) ;

    /// d-tor
    virtual ~FMMTesterCard();

    /// reset the test input fifo
    void resetTFIFO()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// reset the RAMS address generator 
    void resetSimuRAMAddr()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);
  
    /// Reset the FMMTester
    void resetAll()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// Reset the FMMTester
    void reset()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// toggle between TestReg and RAM mode
    ///
    /// @param rammode is true for RAM mode, false for Test Register mode.
    ///        toggling to RAM mode starts the sequence.
    void toggleRAMMode(bool rammode)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// are we in RAM mode?
    ///
    /// returns true for RAM mode, false for test register mode
    bool isRAMMode()
      throw (HAL::HardwareAccessException);

    /// set a test output
    ///
    /// @param ch is the channel number (0 to 19)
    /// @param state is the state to simulate
    void setTestOutput(uint32_t channel, tts::TTSState const& state)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// set all test outputs 
    ///
    /// This function is used to set the test outputs in test register mode.
    ///
    /// @param states is the std::vector of 20 states to simulate
    void setTestOutputs(std::vector<tts::TTSState> const& states)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// read back the test outputs
    ///
    /// To be used in test register mode.
    ///
    /// @param states is the std::vector of 20 states. it is resized to a length of 20.
    void readTestOutputs(std::vector<tts::TTSState> & states)
      throw (HAL::HardwareAccessException);

    /// read the current test inputs
    ///
    /// To be used in test register mode.
    ///
    /// @param states is a std::vector into which the 4 test input staes will be read
    void readTestInputs(std::vector<tts::TTSState> & states)
      throw (HAL::HardwareAccessException);

    /// write a test entry to the test RAMs
    ///
    /// @param addr is the address (0 to 2k) in units of 80-bit blocks
    /// @param states is the std::vector of states to simulate
    void writeTestEntry(uint32_t addr, std::vector<tts::TTSState> const& states)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException,
	     xcept::Exception);

    /// read a test entry from the test RAMs
    ///
    /// @param addr is the address (0 to 2k) in units of 80-bit blocks
    /// @param states is the std::vector of states into which teh states are read
    void readTestEntry(uint32_t addr, std::vector<tts::TTSState> & states)
      throw (HAL::HardwareAccessException,
	     xcept::Exception);

    /// read from the test input FIFOs
    ///
    /// returns true if there was enything to read, false if not
    ///
    /// @param states is a std::vector into which the 4 test input staes will be read
    bool readTestInputFIFOs(std::vector<tts::TTSState>& states)
      throw (HAL::HardwareAccessException);

    /// set the number of sequences to generate
    ///
    /// @param num_seq is the number of sequences (0 to 127) or -1 for an
    ///        indefinite number of sequences.
    void setNumberOfSequences(int num_seq)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException,
	     xcept::Exception);
  
    /// read back the number of sequences to generate
    ///
    /// returns the number of sequences (0 to 127) or -1 for an
    /// indefinite number of sequences.
    int readNumberOfSequences()
      throw (HAL::HardwareAccessException);
  
    /// select the sequence clock
    ///
    /// The frequency at which the sequence is generated can be controlled
    /// in hardware through a clock divider.
    ///
    /// @param clk_sel indicates which clock freuqency to use (0..31).
    ///        0= 20     MHz, 
    ///        1= 10     MHz, 
    ///        2=  5     MHz, 
    ///        3=  2.5   MHz,
    ///        4=  1.25  MHz,
    ///        5=625     kHz,
    ///        6=312.5   kHz,
    ///        7=156.25  kHz,
    ///        8= 78.125 kHz,
    ///        9= 39.06  kHz,
    ///       10= 19.53  kHz,
    ///       11=  9.77  kHz,
    ///       12=  4.88  kHz,
    ///       13=  2.44  kHz,
    ///       14=  1.22  kHz,
    ///       15=610      Hz,
    ///       16=305      Hz,
    ///       17=153      Hz,
    ///       18= 76.3    Hz,
    ///       19= 38.2    Hz,
    ///       20= 19.7    Hz,
    ///       21=  9.54   Hz,
    ///       22=  4.77   Hz,
    ///       23=  2.38   Hz,
    ///       24=  1.19   Hz,
    ///       25=  0.596  Hz,
    ///       26=  0.298  Hz,
    ///       27=  0.149  Hz,
    ///       28=  0.075  Hz,
    ///       29=  0.037  Hz,
    ///       30=  0.019  Hz,
    ///       31=  0.009  Hz, (100 sec period)
    void selectSequenceClock(uint32_t clk_sel)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException,
	     xcept::Exception);
  
    /// read back the sequence clock selection
    ///
    /// return value is the clock selection as in selectSequenceClock().
    uint32_t readSequenceClockSelection()
      throw (HAL::HardwareAccessException);

  
    /// set the delay for the input FIFO
    ///
    /// @param delay is the delay in 40 MHz cycles (0..15) 
    ///
    /// A value of 12 works fine with FMMTester firmware 051031_00 and FMM Firmware 051010_00
    /// using short (50 cm) cables between Tester and FMM.
    void setInputFIFODelay(uint32_t delay)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException,
	     xcept::Exception);

    /// read back the delay for the input FIFO
    ///
    /// returns the delay in 40 MHz cycles (0..15) 
    uint32_t readInputFIFODelay()
      throw (HAL::HardwareAccessException);  

    /// start the sequence
    void startSequence()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// is a sequence in progress ?
    bool sequenceRunning()
      throw (HAL::HardwareAccessException);

    /// stop the sequence
    ///
    /// used to stop a sequence before it ended or to stop and indefinite seqeunce.
    void stopSequence()
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    /// read ID of the FMMTester board
    uint32_t readID()
      throw (HAL::HardwareAccessException);

    /// read the Revision of the FMM Tester Firmware (XILINX)
    ///
    /// The std::string contains 9 characters in the format "YYMMDD_RR",
    /// where YY is the year since 2000, MM, the month (1-12), DD the day (1-31) and RR the revision in this day (00-99)
    std::string readFirmwareRev()
      throw (HAL::HardwareAccessException);

    /// set front panel LEDs
    ///
    /// @param led_setting[3:0] contains 1 bit each for the front panel LEDs 4 to 1 
    ///
    void setLEDs(uint32_t led_setting)
      throw (tts::exception::NoWriteLock,
	     HAL::HardwareAccessException);

    enum { RAMSsize = 0x400 }; // in units of 80-bit (16byte) blocks (1k)
  private: 
    void decodeTestInputs(uint32_t input, std::vector<tts::TTSState> & states);
    std::string BCDtoString(uint32_t num, uint32_t ndigit = 2);
  };

}
#endif
