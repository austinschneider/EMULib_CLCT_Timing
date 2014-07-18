#ifndef _tts_atts_ATTSINTERFACECARD_H
#define _tts_atts_ATTSINTERFACECARD_H

/**
 *     @class ATTSInterfaceCard
 *
 *     @short Class representing the basic functions of the ATTSInterface
 *
 *            Higher-level classes use this class to read and write
 *            data to/from the ATTSInterface and to perform basic functions
 *            such as a reset. The ATTSInterface provides 12 outputs and 12 inputs.
 *            In the final system only the first 8 will be used.      
 *
 *            The ATTSInterfaceCard class is using a HAL PCIDevice in order to 
 *            access the ATTSInterface.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:25 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "tts/ttsbase/TTSState.hh"
#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"

#include <string>
#include <vector>
#include <stdint.h>

namespace tts {

  class ATTSInterfaceCard {
  
  public:
    /// c-tor
    /// 
    /// @param atts is a reference to the HAL PCIDevice. The ATTSInterfaceCard takes ownership of this device
    ///        and deletes it in its destructor
    ATTSInterfaceCard( HAL::PCIDevice* atts );

    /// d-tor
    virtual ~ATTSInterfaceCard();

    /// reset the ATTSInterface
    ///
    void reset()
      throw (HAL::HardwareAccessException);


    /// read the GeoSlot
    ///
    /// GeoSlots in a Compact PCI crate range from 0 (rightmost slot) to 20 (leftmost slot)
    /// The rightmost slot (0) is usually occupied by the controller (connection to the PC) 
    /// An FMM occupies two slots and has its connector in the left one of the two slots.
    ///
    /// Note: GeoSlots are only available in Compact PCI crates with a custom CMSDAQ backplane.
    ///
    uint32_t getGeoSlot()
      throw (HAL::HardwareAccessException);


    /// read the Revision of the FMM Firmware
    ///
    /// The std::string contains 9 characters in the format "YYMMDD_RR",
    /// where YY is the year since 2000, MM, the month (1-12), DD the day (1-31) and RR the revision in this day (00-99)
    std::string readFirmwareRev()
      throw (HAL::HardwareAccessException);

    /// read the Revision of the Firmware of the Altera (Bridge)
    ///
    /// The std::string contains 9 characters in the format "YYMMDD_RR",
    /// where YY is the year since 2000, MM, the month (1-12), DD the day (1-31) and RR the revision in this day (00-99)
    std::string readFirmwareRevAltera()
      throw (HAL::HardwareAccessException);

    /// read the serial number
    ///
    /// the reurned std::string contains the 19 digits of the serial number
    std::string getSerialNumber()
      throw (HAL::HardwareAccessException);

  
    /// set front panel LEDs
    ///
    /// @param led_setting[2:0] contains 1 bit each for the front panel LEDs 4 to 2 
    ///
    void setLEDs(uint32_t led_setting)
      throw (HAL::HardwareAccessException);

    /// Set the state of the DAQ Partition to be signalled to the Global Trigger TCS System
    ///
    /// @param ipartition is the DAQ partiton index (0..7 (11) )
    /// @param state is the state to be signalled. 
    ///
    /// Only states Ready, Busy, Warning should be signalled this way. 
    /// States Error and Out of Sync should be signalled as a pulse using pulseDAQPartitionState(),
    /// because they must not exceed a certain pulse length.
    ///
    void setDAQPartitionState(uint32_t ipartition, tts::TTSState const& state)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// Set the state of the DAQ Partition state for a certain time, then return to the previous state
    ///
    /// @param ipartition is the DAQ partiton index (0..7 (11) )
    /// @param state is the state to be signalled for a certain time. 
    ///
    /// States Error and Out of Sync should be signalled this way.  For
    /// the TCS system to recognize the error or out-of-sync state, the
    /// pulse needs to be at least 5 bunch crossings long but must not
    /// be longer than a few orbits. The ATTSInterface firmware
    /// therefore generates a pulse of 5 bx length and then goes back to
    /// the previous state.
    ///
    void pulseDAQPartitionState(uint32_t ipartition, tts::TTSState const& state)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// Read back the DAQ partition state set by setDAQPartitionState
    ///
    /// @param ipartition is the DAQ partiton index (0..7 (11) )
    tts::TTSState readbackDAQPartitionState(uint32_t ipartition)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// Read the state of the Global Trigger TCS System for all DAQ Partitions
    ///
    /// returns the state signalleds by the TCS system
    std::vector<tts::TTSState> readTCSPartitionStates()
      throw (HAL::HardwareAccessException);

    /// Read the state of the Global Trigger TCS System for a given DAQ Partition
    ///
    /// @param ipartition is the DAQ partiton index (0..7 (11) )
    ///
    /// returns the state signalled by the TCS system
    tts::TTSState readTCSPartitionState(uint32_t ipartition)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// are we in simulation mode?
    bool isSimuMode()
      throw (HAL::HardwareAccessException); 

    /// toggle simu mode
    ///
    /// @param simu_mode is true for input simulation mode, false for normal operation 
    void toggleSimuMode(bool simu_mode)
      throw (HAL::HardwareAccessException);


    /// set the simulated input states
    ///
    /// @param states contains the 12 input states to be simulated
    void setSimulatedInputStates(std::vector <tts::TTSState> const& states)
      throw (HAL::HardwareAccessException);

    /// set the simulated input state
    ///
    /// @param channel is the channel number (0..11) 
    /// @param state contains input state to be simulated
    void setSimulatedInputState(uint32_t channel, tts::TTSState const& state)
      throw (HAL::HardwareAccessException, xcept::Exception);

    /// read back the simulated input states
    ///
    /// returns a std::vector of 12 TTSStates
    std::vector<tts::TTSState> readbackSimulatedInputStates()
      throw (HAL::HardwareAccessException);

    /// get a referene to the HAL::PCIDevice
    HAL::PCIDevice& device() { return *_atts; };

  private: 
    std::string BCDtoString(uint32_t num, uint32_t ndigit = 2);

    HAL::PCIDevice* _atts;
    std::string _serialnumber;
    uint32_t _geoslot;
  };

}
#endif
