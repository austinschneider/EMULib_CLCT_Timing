#ifndef _ttc_utils_BGOMap_hh_
#define _ttc_utils_BGOMap_hh_


#include <stdint.h>
#include <vector>


namespace ttc
{

class GenericTTCModule;
class Address;

/**
 * A class for the LTC and TTCci dealing with the BGO Map
 * (remapping/disabling of certain BGO channels).
 *
 * Traditionally, in the LTC class, the BGO map was read from the
 * hardware whenever one of these function was called,
 * while for the TTCci class, always the value in the memory was taken.
 */
class BGOMap
{

// static

private:

  //! number of BGO channels
  static const int8_t nchannels;

  static const uint32_t BGOMAP_RESYNC_OFFS; // channel 5
  static const uint32_t BGOMAP_RESYNC_WDTH;
  static const uint32_t BGOMAP_HARDRESET_OFFS; // channel 6
  static const uint32_t BGOMAP_HARDRESET_WDTH;
  static const uint32_t BGOMAP_ECRST_OFFS; // channel 7
  static const uint32_t BGOMAP_ECRST_WDTH;
  static const uint32_t BGOMAP_OCRST_OFFS; // channel 8
  static const uint32_t BGOMAP_OCRST_WDTH;
  static const uint32_t BGOMAP_START_OFFS; // channel 9
  static const uint32_t BGOMAP_START_WDTH;
  static const uint32_t BGOMAP_STOP_OFFS_TTCCI; // channel 10
  static const uint32_t BGOMAP_STOP_OFFS_LTC; // channel 10
  static const uint32_t BGOMAP_STOP_WDTH;

// members

public:

  BGOMap(GenericTTCModule& _module, const Address& _bgo_map_address, bool _is_ltc);

  //! refreshes the BGO map register from the hardware, and returns the value
  uint32_t GetBGOMap() const;

  //! checks @param val for consistency, and updates memory cache and hardware register
  void SetBGOMap(const uint32_t val);

  //! BGO channel names (no spaces, for use in configuration files)
  std::vector<std::string> getChannelNames();

  //! returns vector of alternative values for a given BGO channel (accepted in configuration files)
  std::vector<std::string> getChannelNameAlternatives(int8_t channel);

  int8_t Get_Resynch_BGOCh() const;

  int8_t Get_HardReset_BGOCh() const;

  int8_t Get_ECntReset_BGOCh() const;

  int8_t Get_OCntReset_BGOCh() const;

  int8_t Get_Start_BGOCh() const;

  int8_t Get_Stop_BGOCh() const;

private:

  //! reference to the TTCci or LTC module
  GenericTTCModule& module;

  const Address& bgo_map_address;

  //! Cache of the current value of the BGO map register in the hardware.
  mutable uint32_t bgomap;

  //! There are some differences in the BGO map between LTC and TTCci. This flag identifies the type of module.
  bool is_ltc;

  void Set_Resynch_BGOCh(const uint32_t val);

  void Set_HardReset_BGOCh(const uint32_t val);

  void Set_ECntReset_BGOCh(const uint32_t val);

  void Set_OCntReset_BGOCh(const uint32_t val);

  void Set_Start_BGOCh(const uint32_t val);

  void Set_Stop_BGOCh(const uint32_t val);

  void readBgoMapFromHardware() const;

  void writeBGOMapToHardware() const;

  /**
   * Returns the channel number for a given channel action
   * (which is identified by the position and number of bits in the BGO mapping register).
   * @param num_bits is the number of bits this mask uses.
   * @param offset is the offset at which the mapping for this channel starts in the register in the module.
   */
  int8_t GetBgoChannel(uint32_t num_bits, uint32_t offset) const;

  //! Sets the mapping for a certain BGO channel. See GetBgoChannel().
  void SetBGOChannel(uint32_t val, uint32_t num_bits, uint32_t offset);
};

}


#endif
