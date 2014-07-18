#ifndef _FMMCARD_H
#define _FMMCARD_H

/**
 *     @class FMMCard
 *
 *     @short Class representing the basic functions of the FMM
 *
 *            Higher-level classes use this class to read and write
 *            data to/from the FMM and to perform basic functions
 *            such as a rest.
 *
 *            The tts::FMMCard class is using a HAL PCIDevice in order to 
 *            access the tts::FMM.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/03/28 12:06:23 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "tts/ttsbase/TTSState.hh"
#include "tts/fmm/FMMHistoryItem.hh"
#include "tts/fmm/FMMConfiguration.hh"

#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"

#include "tts/cpcibase/CPCICard.hh"

#include "toolbox/BSem.h"

#include <vector>
#include <utility>
#include <stdint.h>

namespace tts {

  class FMMCard : public tts::CPCICard {
  
  public:
    enum { NumCounters = 110 };

    /// c-tor
    ///
    /// @param device is a pointer to the HAL::PCIDevice used to access the hardware. 
    /// The FMMCard becomes the owner of the HAL::PCIDevice  and is responsible for its destruction. 
    ///
    /// @param cratelock is a reference to the cratelock object. 
    FMMCard( HAL::PCIDevice* device, ipcutils::SemaphoreArray& cratelock) ;

    /// d-tor
    ///
    /// releases the write lock if not done before
    ///
    virtual ~FMMCard();

    /// reset the dead-time monitors
    void resetDeadTimeMonitors()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);
  
    /// reset the transition miss counter
    void resetTransitionMissCounter()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);
  
    /// reset the time tag counter
    void resetTimeTag()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// reset history write counter
    void resetHistoryAddress()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);
  
    /// Reset the FMM
    ///
    /// This reset clears state machines, fifos and registers for which individual reset
    /// functions exist.
    /// Does not reset control register, mask and threshold registers.
    void resetAll()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read the history memory write address (17 bit) in unites of 16-byte blocks
    uint32_t readHistoryAddress()
      throw (HAL::HardwareAccessException);

    /// read the history memory write address (17 bit) in unites of 16-byte blocks (first in pair), 
    /// and the wrap counter for the History Address counter (second in pair) 
    std::pair<uint32_t, uint32_t> readHistoryAddressAndWrapCount()
      throw (HAL::HardwareAccessException);

    /// read transition miss counter
    uint32_t readTransitionMissCounter()
      throw (HAL::HardwareAccessException);

    /// read the Revision of the FMM Firmware
    ///
    /// The std::string contains 9 characters in the format "YYMMDD_RR",
    /// where YY is the year since 2000, MM, the month (1-12), DD the day (1-31) and RR the revision in this day (00-99)
    std::string readFirmwareRev()
      throw (HAL::HardwareAccessException);

    /// toggle dual FMM mode
    ///
    /// In single-FMM mode, Inputs 0 to 19 are merged with the FMM's merging
    /// function and the output is sent to all four outputs (unless output-
    /// testing is enabled). The threshold applied to the merging of out-of-synch
    /// inputs is defined by setThreshold20().
    ///
    /// In dual-FMM mode, Inputs 0 to 9 and Inputs 10 to 19 are merged by two
    /// separate merging functions. The output of the first merging function is sent 
    /// sent to outputs IO20 and IO21, the output of the second merging function is
    /// sent to output IO22 and IO23 (unless output-testing is enabled). The thresholds 
    /// used for the merging of out-of-synch signals are defined bu setThreshold10A() 
    /// and setThreshold10B().
    ///
    /// @param dual is true for dual-FMM mode, false for single-FMM mode
    void toggleDualMode(bool dual)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// are we in dual FMM mode?
    bool isDualMode()
      throw (HAL::HardwareAccessException);

    /// set the mask
    ///
    /// @param mask[19:0] is the mask for the 20 input channels. 
    ///        Setting a bit to 1 means that the channel is masked (switched off).
    void setMask(uint32_t mask)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the mask
    uint32_t getMask()
      throw (HAL::HardwareAccessException);

    /// set the threshold for 20-input (single-FMM) mode
    ///
    /// @param threshold[4:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold20(uint32_t threshold)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the threshold
    uint32_t getThreshold20()
      throw (HAL::HardwareAccessException);

    /// set the threshold A (merging of first 10 inputs) for 10-input (dual-FMM) mode
    ///
    /// @param threshold[3:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold10A(uint32_t threshold)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the threshold
    uint32_t getThreshold10A()
      throw (HAL::HardwareAccessException);

    /// set the threshold B (merging of second 10 inputs) for 10-input (dual-FMM) mode
    ///
    /// @param threshold[3:0] is the threshold for the merging of out-of-sync inputs.
    ///        more than threshold inputs have to be out-of-sync for the resulting 
    ///        state to be out-of-sync. The default value of 0(zero) corresponds to a logical OR.
    void setThreshold10B(uint32_t threshold)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the threshold
    uint32_t getThreshold10B()
      throw (HAL::HardwareAccessException);

    /// set the configuration
    /// 
    /// This sets dualmode, mask and the three thesholds at the same time
    ///
    /// @param cfg is the FMM configuration
    void setConfig(tts::FMMConfiguration const& cfg)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the configuration
    tts::FMMConfiguration readConfig()
      throw (HAL::HardwareAccessException);

    /// are we in simulation mode?
    bool isSimuMode()
      throw (HAL::HardwareAccessException); 

    /// toggle simu mode
    ///
    /// @param simu_mode is true for input simulation mode, false for normal operation 
    void toggleSimuMode(bool simu_mode)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// are we in DMA History mode?
    bool isDMAMode()
      throw (HAL::HardwareAccessException); 

    /// toggle DMA mode
    ///
    /// @param dma_mode is true for DMA mode, false for ZBT (normal) mode
    void toggleDMAMode(bool dma_mode)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// toggle enable bit for time tag reset from backplane
    ///
    /// @param enabled is true if tim e tag reset from the backplane is enabled
    void toggleTimeTagExtResetEnable(bool enable)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// is time tag reset from backplane enabled?
    bool timeTagExtResetEnabled()
      throw (HAL::HardwareAccessException);

    /// set front panel LEDs
    ///
    /// @param led_setting[2:0] contains 1 bit each for the front panel LEDs 4 to 2 
    ///
    void setLEDs(uint32_t led_setting)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// set the simulated input states
    ///
    /// @param states contains the 20 input states to be simulated
    void setSimulatedInputStates(std::vector <tts::TTSState> const& states)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// set the simulated input state
    ///
    /// @param channel is the channel number (0..19) 
    /// @param state contains input state to be simulated
    void setSimulatedInputState(uint32_t channel, tts::TTSState const& state)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock,
	     xcept::Exception);

    /// read back the simulated input states
    ///
    std::vector<tts::TTSState> getSimulatedInputStates()
      throw (HAL::HardwareAccessException);
  
    /// read the current inputs from the spy registers
    ///
    std::vector<tts::TTSState> readInputs()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);
  

    /// read an item from the history memory
    ///
    /// @param addr is the address of the item (in units of 16-byte blocks)
    /// @param hi is a reference to the history item to be filled
    void readHistoryItem(uint32_t addr, tts::FMMHistoryItem& hi)
      throw (HAL::HardwareAccessException);

    /// clear the history memory
    ///
    /// @param pattern is the 32-bit pattern to write to each word in the history memory
    void clearHistoryMemory(uint32_t pattern = 0x00000000)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);


    /// retrieve dead-time counters
    ///
    /// does the necessary unfreezing and freezing. 
    /// synchronized with readDeadTimeCountersAndTimeTag() and readTimeTag();
    ///
    /// @param counters is a reference to the dead-time counters.
    ///        The first 22 counters count the time spent in busy state,
    ///        the second 22 count the time spent in warning state.
    ///        In a set of 22 counters, the first 20 corresponf to the 20 inputs, 
    ///        the next two to the two possible outputs (FuncA, FuncB)
    void readDeadTimeCounters(std::vector<uint32_t> & counters )
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);


    /// retrieve dead-time counters and time tag in one operation
    ///
    /// does the necessary unfreezing and freezing.
    /// synchronized with readDeadTimeCounters() and readTimeTag();
    ///
    /// @param counters is a reference to the dead-time counters.
    ///        The first 22 counters count the time spent in busy state,
    ///        the second 22 count the time spent in warning state.
    ///        In a set of 22 counters, the first 20 corresponf to the 20 inputs, 
    ///        the next two to the two possible outputs (FuncA, FuncB)
    /// @param tt is the 40-bit time tag
    void readDeadTimeCountersAndTimeTag(std::vector<uint32_t> & counters, uint64_t& tt )
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);


    /// read the time tag counter read register
    ///
    /// does the necessary unfreezing and freezing.
    /// synchronized with readDeadTimeCounters() and readDeadTimeCountersAndTimeTag();
    /// 
    uint64_t readTimeTag()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// retrieve the current result of half-FMM A (sent to IO20 and IO21)
    tts::TTSState readResultA()
      throw (HAL::HardwareAccessException);

    /// retrieve the current result of half-FMM B (sent to IO22 and IO23)
    tts::TTSState readResultB()
      throw (HAL::HardwareAccessException);

    /// read the func value A (input to the priority encoder of first half-FMM)
    uint32_t readFuncA()
      throw (HAL::HardwareAccessException);

    /// read the func value B (input to the priority encoder of second half-FMM)
    uint32_t readFuncB()
      throw (HAL::HardwareAccessException);
  
    /// toggle output test mode
    ///
    /// @param test_output_enable[3:0] switches outputs 23:20 to test mode (when the corresponding bit is set)
    void enableTestOutputs(uint32_t test_output_enable)
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// read back the test output enable bits
    ///
    /// the returned value[3:0] indicates which of outputs 23:20 are in test mode
    uint32_t readTestOutputEnables()
      throw (HAL::HardwareAccessException);

    /// set the state of one of the four outputs (if in the output is in test mode)
    ///
    /// @param output_idx is the index of the output (0..3)
    /// @param state is the state to set
    void setTestOutputValue(uint32_t output_idx, tts::TTSState const& state )
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock,
	     xcept::Exception);

    /// read back the test-state of an output 
    ///
    /// note: the output is set to this state only if the output is in test mode
    ///
    /// @param output_idx is the index of the output (0..3)
    tts::TTSState readTestOutputValue(uint32_t output_idx)
      throw (HAL::HardwareAccessException, 
	     xcept::Exception);

    enum { FMMHistMemSize = 0x20000 }; // in units of 16-byte blocks
    enum { FMMWrapCounterLength = 32768 };

  protected:
  
    void doReadDeadTimeCounters(std::vector<uint32_t> & counters )
      throw (HAL::HardwareAccessException);

    uint64_t doReadTimeTag()
      throw (HAL::HardwareAccessException);


    /// freeze the dead time counter and time tag read registers
    ///
    /// the actual counters keep running. Use this before redaing the dead tim counters and the time tag.
    /// unFreezeTimes() has to be called after reading.
    void freezeTimes()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);

    /// un freeze the dead time counter and time tag read registers
    ///
    /// the actual counters keep running. Use this before redaing the dead tim counters and the time tag.
    /// unFreezeTimes() has to be called after reading.
    void unFreezeTimes()
      throw (HAL::HardwareAccessException,
	     tts::exception::NoWriteLock);


  private: 
    std::string BCDtoString(uint32_t num, uint32_t ndigit = 2);
    toolbox::BSem _ctrl_reg_semaphore;
    toolbox::BSem _timers_semaphore;

    std::string _fwRevXilinx;
  };

}

#endif
