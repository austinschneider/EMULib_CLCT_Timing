#ifndef _ttc_utils_GenericTTCModule_hh_
#define _ttc_utils_GenericTTCModule_hh_


#include "ttc/utils/VMEHistoryEntry.hh"
#include "ttc/utils/Sequence.hh"
#include "ttc/utils/Address.hh"
#include "ttc/utils/VME64xDeviceInfo.hh"
#include "ttc/utils/LockMutex.hh"

#include "hal/VMEDevice.hh"
#include "log4cplus/logger.h"

#include <iostream>
#include <string>


namespace HAL
{
class VMEBusAdapterInterface;
}


//! ttc::exception::UndeclaredSequence for undefined sequence in GetSequence
XCEPT_DEFINE_EXCEPTION(ttc, UndeclaredSequence);


namespace ttc
{

class VMEReadCache;

//! This class is the base for classes representing the various TTC hardware modules.
class GenericTTCModule
{
  friend class GenericTTCModuleConfiguration; // TODO get rid of this friend

// static

public:

  //! mutex used to avoid concurrent VME access from different threads
  static Mutex vme_mutex;

  //! nominal LHC orbit time in seconds
  static const double nominal_orbit_time_in_sec;

  //! converts orbit counter value to time since orbit counter reset, in seconds
  static unsigned OrbitCounterToSeconds(uint32_t orbit_count_value);

  //! returns time elapsed since orbit counter reset, in format "hh:mm:ss"
  static std::string OrbitCounterToSecondsString(uint32_t orbit_count_value);

// members

public:

  GenericTTCModule(
      Address::ModuleType _module_type,
      HAL::VMEBusAdapterInterface& bus,
      const VME64xDeviceInfo& _info,
      bool enable_vme_writes_);

  virtual ~GenericTTCModule();

  log4cplus::Logger& getLogger();

  //! abstract method to return string identifying firmware (and maybe module) version
  virtual std::string firmwareVersionString() = 0;

  const VME64xDeviceInfo& GetInfo() const;

  //! prints the VME operations history to file or logger (default)
  void PrintVMEHistory(const std::string& filename = "") const;

  //! Searches for registered sequence identified by @param identifier, and returns it if found, or NULL else.
  Sequence* GetSequence(const std::string &identifier);

  //! Returns a vector with the names of registered sequences.
  std::vector<std::string> GetSequenceNames() const;

  /**
   * Adds an empty sequence by name.
   * Throws an exception iff sequence name too short (less than two characters) or sequence already exists.
   */
  void AddSequence(std::string &name);

  /**
   * Removes sequence given by @param name .
   * Throws exception iff sequence does not exist or cannot be removed since it's "permanent".
   */
  void DeleteSequence(std::string &name);

  /**
   * Executes sequence given by @param identifier .
   * Default implementation calls virtual ExecuteSequenceLine.
   */
  virtual void ExecuteSequence(const std::string& identifier);

  /**
   * Reads the register given by @param add , via the VMEReadCache;
   * adds an entry to the VME operations history, with the given @param comment ;
   * returns read value.
   * Throws std::invalid_argument if register is not readable.
   */
  uint32_t Read(const ttc::Address& add, const std::string& comment = "") const;

  //! Same as Read(add, comment), but reads the register corresponding to the ttc::Address element indexed by @param index .
  uint32_t Read(const Address& add, const uint32_t index, const std::string& comment = "") const;

  //! Calls Read(add, comment) forwarding the ttc::Address corresponding to the register given by @param register_name .
  uint32_t Read(const std::string& register_name, const std::string& comment = "") const;

  //! Same as Read(register_name, comment), but reads the register corresponding to the ttc::Address element indexed by @param index .
  uint32_t Read(const std::string& register_name, const uint32_t index, const std::string& comment = "") const;

  /**
   * Returns without action if VME writing is disabled.
   * Writes @param value to the register given by @param add ;
   * adds an entry to the VME operations history, with the given @param comment ;
   * Throws std::invalid_argument if register is not writable.
   */
  void Write(const Address& add, uint32_t value, const std::string &comment = "");

  //! Same as Write(add, value, comment), but writes to the register corresponding to the ttc::Address element indexed by @param index .
  void Write(const Address& add, const uint32_t index, const uint32_t value, const std::string &comment = "");

  //! Calls Write(add, value, comment) forwarding the ttc::Address corresponding to the register given by @param register_name .
  void Write(const std::string &register_name, uint32_t value, const std::string &comment = "");

  //! Same as Write(register_name, value, comment), but writes to the register corresponding to the ttc::Address element indexed by @param index .
  void Write(const std::string &register_name, const uint32_t index, const uint32_t value, const std::string &comment = "");

  /**
   * Retrieves all registered ttc::Addresses with access mode given by @param access :
   *   pass Access::RW if you want registers that are readable and writable;
   *   pass Access::RO if you want registers that are readable, no matter if they are writable or not;
   *   pass Access::WO if you want registers that are writable, no matter if they are readable or not;
   * Fills vectors @param addr_name and @param addr_title with names and descriptions, respectively, for these registers.
   */
  void GetVMEAddresses(
      std::vector<std::string>& addr_name,
      std::vector<std::string>& addr_title,
      Address::ReadWrite access = Address::NONE) const;

  /**
   * Returns vector with pointers to registers having access mode given by @param access :
   * For @param access, see GetVMEAddresses(addr_name, addr_title, access).
   */
  std::vector<Address*> GetVMEAddresses(Address::ReadWrite access) const;

  //! enables the VMEReadCache
  void EnableReadCache();

  //! disables the VMEReadCache
  void DisableReadCache();


  //! enables VME writing
  void EnableVMEWrites(bool enable);

  //! disables VME writing
  bool GetVMEWritesEnabledStatus() const;

protected:

  mutable log4cplus::Logger logger_;

  //! the ModuleType for this TTC module
  Address::ModuleType module_type;

  //! the vector containing the history of VME operations
  mutable std::vector<VMEHistoryEntry> vmehist;

  //! total count of VME operations since startup (can be greater then the size of the shortened vector)
  mutable int32_t nvmehist;

  /**
   * vector of registered Sequences for this TTC module
   * (as defined in configuration file tokens embraced by BEGINSEQUENCE and ENDSEQUENCE tokens)
   */
  std::vector<Sequence> _sequences;

  //! the ttc::VME64xDeviceInfo for the TTC module managed by this class
  VME64xDeviceInfo info;

  //! the VMEDevice corresponding to the TTC module managed by this class
  HAL::VMEDevice vme;

  //! the cache for VME reads
  VMEReadCache* vme_read_cache;

  /**
   * This flag, iff false, disables write requests to the TTC module
   * (apart from initialization writes to the configuration space).
   */
  bool enable_vme_writes;

  /**
   * Configures the TTC module with configuration data from stream @param in.
   * To be implemented in subclass.
   */
  virtual void Configure(std::istream &in);

  /**
   * Writes current configuration in configuration file format to the given ostream @param out .
   * To be implemented in subclass.
   */
  virtual void WriteConfiguration(std::ostream &out, const std::string& comment);

  //! Executes the commands corresponding to a single @param line of a sequence of a configuration file.
  virtual void ExecuteSequenceLine(const std::string& line);

  /**
   * Returns vector of pointers to write-only ttc::Addresses that are to be excluded from register dumps.
   * (This was introduced for the RF2TTC having registers which would cause bus errors on attempts to read.)
   * To be implemented in subclass. Default implementation returns empty vector.
   * Note that his is only called once, hence dynamic changes of registers to be excluded are not supported.
   */
  virtual std::vector<const Address*> GetExcludedVMEAddressesForDump() const;

private:

  //! adds entry to history of VME operations, shortens history if it becomes too long
  void AddVMEEntry(const VMEHistoryEntry& entry) const;
};

}


#endif
