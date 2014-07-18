#ifndef _ttc_utils_VME64xDeviceInfo_hh_
#define _ttc_utils_VME64xDeviceInfo_hh_


#include "hal/VMEDevice.hh"

#include <vector>
#include <string>
#include <ostream>


namespace HAL
{
class VMEAddressTable;
class VMEBusAdapterInterface;
class VMEConfigurationSpaceHandler;
}


namespace ttc
{

extern HAL::VMEAddressTable& DummyAddressTable;

class VME64xDeviceInfo
{

// static

public:

  /// Manufacturer IDs (IEEE OUI)

  static const uint32_t MF_ANY = 0xFFFFFFFF;
  static const uint32_t MF_CERN = 0x080030;

  static const int SLOT_ANY = 0;

  // Board ids

  static const uint32_t BOARD_ID_LTC = 0x00000161;
  static const uint32_t BOARD_ID_TTCCI = 0x00000162;

  static const uint32_t BOARD_ID_RF2TTC = 0x0000016B;
  static const uint32_t BOARD_ID_RFRX_D = 0x0000016C;
  static const uint32_t BOARD_ID_RFTX_D = 0x0000016D;

  static const uint32_t EDA_ID_RFRX_D = 0x1382;

// members

public:

  VME64xDeviceInfo();

  VME64xDeviceInfo(
      uint32_t ManufacturerID,
      uint32_t BoardID,
      int Location = SLOT_ANY,
      const char* RevisionID = 0,
      const char* SerialNumber = 0,
      const char* Description = 0);

  VME64xDeviceInfo(HAL::VMEConfigurationSpaceHandler&, int slot);

  bool operator==(const VME64xDeviceInfo& rhs) const;

  bool operator!=(const VME64xDeviceInfo& rhs) const;

  bool isValid() const;

  bool isEnabled() const;

  int location() const;

  uint32_t& address(int i);

  std::vector<uint32_t>& addresses();

  HAL::VMEDevice MakeVMEDevice(HAL::VMEBusAdapterInterface& bus, HAL::VMEAddressTable& = DummyAddressTable);

  //! Dumps the variables contained in this instance on the stream out.
  void print(std::ostream& out) const;

private:

  bool Valid_;
  uint32_t ManufacturerId_;
  uint32_t BoardId_;
  std::string RevisionId_;
  std::string SerialNumber_;
  std::string Description_;
  bool hasBoardId_;
  bool hasRevisionId_;
  bool hasSerialNumber_;
  bool hasDescription_;

  int Location_;
  bool Enabled_;
  std::vector<uint32_t> Addresses_;
  HAL::VMEDevice* Device_;
};


std::ostream& operator<<(std::ostream& out, const VME64xDeviceInfo& info);

}


#endif
