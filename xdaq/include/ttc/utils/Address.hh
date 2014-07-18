#ifndef _ttc_utils_Address_hh_
#define _ttc_utils_Address_hh_


#include "hal/VMEHardwareAddress.hh"

#include <stdint.h>


namespace ttc
{

//! class representing TTC-specialized version of HAL::VMEHardwareAddress
class Address : public HAL::VMEHardwareAddress
{

// enum/types

public:

  enum ModuleType
  {
    NOMODULE = 0,
    LTC = 1,
    TTCci = 2,
    RF2TTC = 3,
    RFRXD = 4,
    BOBR = 5
  };

  enum ReadWrite
  {
    NONE = 0,
    RO = 1,
    WO = 2,
    RW = 3
  };

// static

public:

  //! returns ttc::Address for a given module and register name
  static Address& findByName(ModuleType module_type, const std::string &name);

  //! returns all registered ttc::Addresses for a given module
  static std::vector<Address*> getAllAddresses(ModuleType module_type);

private:

  //! dummy register name (used by default constructor)
  static const std::string dummy_register_name;

  //! returns reference to local static vector (managed in other places); TODO do this better
  static std::vector<Address*>& GetAllKnownAddresses();

// members

public:

  //! constructs ttc::Address with default values
  Address();

  /**
   * Construct ttc::Address.
   * @param add is the base address
   * @param am is the Address Modifier.
   * @param rw specifies whether we can read and/or write this VME item.
   * @param width is the data width in number of bytes.
   */
  Address(
      ModuleType _module_type,
      const std::string& name,
      uint32_t add,
      uint32_t am,
      ReadWrite rw,
      uint32_t width,
      uint32_t nelem = 1,
      uint32_t step = 4);

  /**
   * Construct ttc::Address.
   * The address is taken to be the base's address + the offset.
   * The read/write properties and width are inherited from the given base.
   */
  Address(
      ModuleType _module_type,
      const std::string& name,
      const Address& base,
      uint32_t offset,
      uint32_t nelem = 1,
      uint32_t step = 4);

  /**
   * Construct ttc::Address by copying from given base.
   * A new name is assigned.
   */
  Address(const std::string& name, const Address& base);

  bool operator==(const Address& add2) const;

  bool operator!=(const Address& add2) const;

  //! Returns true iff VME item is readable
  bool isReadable() const;

  //! Returns true iff VME item is writable
  bool isWriteable() const;

  //! Returns the name of this VME item
  std::string GetName() const;

  //! Returns the ModuleType of this VME item
  ModuleType GetModuleType() const;

  /**
   * Returns the VMEHardwareAddress for the VME item's element given by index.
   * Throws std::out_of_range if index is out of range
   */
  HAL::VMEHardwareAddress VMEAddress(uint32_t index) const;

  //! Returns a string description of the module type.
  std::string GetModuleDescription() const;

  //! Returns description for VME item (name, RW property, number of elements)
  std::string GetDescription() const;

  //! Returns "RW", "R ", "W ", or "NONE", depending on the read/write properties of this VME item
  std::string GetRWStatus() const;

  //! Returns the number of elements this VME item is composed of.
  uint32_t GetNum() const;

private:

  //! Name of this VME item.
  std::string name;

  //! Specifies the possible operations (read and/or write).
  ReadWrite rw;

  //! Number of elements this object represents.
  uint32_t nelements;

  //! Step size between individual elements of this ttc::Address, in Byte (e.g. 4 for 32 bit registers).
  uint32_t step;

  //! The type of VME module this address is valid for.
  ModuleType module_type;

  //! registers this VME item in a static vector (called in constructors)
  void registerMe();
};

}


#endif
