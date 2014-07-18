#ifndef _ttc_utils_VMEReadCache_hh_
#define _ttc_utils_VMEReadCache_hh_


#include <map>


namespace HAL
{
class VMEDevice;
}


namespace ttc
{

class Address;

/**
 * A class implementing a cache for read access to VME items.
 *
 * This can e.g. be used when the overall status of a board is
 * printed and the code is (for convenience) organized in a way
 * that multiple reads to the same register are done
 * (e.g. when reading individual bits separately).
 *
 * Note that this cache is NOT here for increasing performance in this case
 * (by grouping multiple identical reads into one VME access)
 * but rather for reasons of consistency, i.e. that when
 * printing the raw register value and the verbose interpretation  of it,
 * one uses the same value read from the register.
 */
class VMEReadCache
{
public:

  VMEReadCache(HAL::VMEDevice& _vme);

  /**
   * enables the cache, using an int instead of a bool flag,
   * for usage with recursvie calls? TODO clarify
   */
  void EnableReadCache();

  /**
   * disables the cache, using an int instead of a bool flag,
   * for usage with recursvie calls? TODO clarify
   */
  void DisableReadCache();

  /**
   * Reads a register value through the cache.
   * Similar to Read(add, index, was_cached), but without was_cached.
   */
  uint32_t Read(const Address& add, const uint32_t index);

private:

  /**
   * mapping between the address identifier (register name, index)
   * and the cached register value
   */
  std::map<std::pair<const std::string, uint32_t>, uint32_t> cache;

  /**
   * int flag telling the level of "enabledness" of the cache -
   * used in place of a bool flag, for ease of use with recursive calls?
   * Each call to EnableReadCache() increments this.
   * Each call to DisableReadCache() decrements this. When 0 is reached, the cache is cleared.
   */
  int enabled_level;

  //! reference to VMEDevice for which read accesses are cached
  HAL::VMEDevice& vme;

  /**
   * If the cache is enabled, tries to get the value from the cache,
   * if not (or if it wasn't cached), accesses the hardware.
   *
   * @param was_cached on return this will contain information
   * whether the return value came from the cache or not.
   */
  uint32_t Read(const Address& add, const uint32_t index, bool& was_cached);

  /**
   * reads a register (identified by @param add and @param index) from the hardware,
   * locking the vme_mutex while doing so
   */
  uint32_t ReadFromHardware(const Address& add, const uint32_t index);
};

}


#endif
