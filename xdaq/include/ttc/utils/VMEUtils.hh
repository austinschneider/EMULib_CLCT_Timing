#ifndef _ttc_utils_VMEUtils_hh_
#define _ttc_utils_VMEUtils_hh_


#include "ttc/utils/Singleton.hh"

#include "hal/AddressTableReader.hh"
#include "hal/VMEAddressTable.hh"


namespace HAL
{
class VMEConfigurationSpaceHandler;
}


namespace ttc
{

//! class collecting static utility functions used in conjunction with VME access
class VMEUtils
{
// types

  class DummyAddressTableReader : public HAL::AddressTableReader
  {
  public:
    DummyAddressTableReader();
  };

  //! class specializing the VMEAddressTable to be initialized with a dummy reader; TODO clarify
  class DummyVMEAddressTable : public HAL::VMEAddressTable
  {
  public:
    DummyVMEAddressTable();
  };

// static

public:

  static Singleton<DummyAddressTableReader> DummyReader;

  static Singleton<DummyVMEAddressTable> DummyAddressTableTemp;

  //! reads and returns value for an item of the VME configuration space
  static uint32_t configread(
      HAL::VMEConfigurationSpaceHandler& handler,
      uint32_t slot,
      std::string item,
      uint32_t offset = 0);

  /**
   * Returns ROM block of VME configuration space as a string of characters.
   * The @param start and @param end variables denote the delimiters of the block to be read,
   * in terms of the corresponding configuration space items.
   * TODO check and add more details
   */
  static std::string configreadstr(
      HAL::VMEConfigurationSpaceHandler& handler,
      uint32_t slot,
      const std::string& start,
      const std::string& end);

  //! TODO check
  static std::string configreadzstr(
      HAL::VMEConfigurationSpaceHandler& handler,
      uint32_t slot,
      const std::string& start);

  /**
   * Reinterprets an 32 bit integer as a string (which might be 0-terminated) and returns it.
   * The maximum string length we can get here is 4 characters.
   */
  static std::string make_str(uint32_t src);

  //! Makes a 32 bit integer from a string.
  static uint32_t make_ulong(const std::string& src);
};

}


#endif
