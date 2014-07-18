#ifndef _ttc_bobr_BOBR_hh_
#define _ttc_bobr_BOBR_hh_


#include "ttc/utils/GenericTTCModule.hh"

#include <ctime>
#include <string>


namespace HAL
{
class VMEBusAdapterInterface;
}


namespace ttc
{

class BOBRReceiverBlock;
class Address;

/**
 * Class BOBR represents a BOBR card,
 * and all the operations that may be performed on it.
 */
class BOBR : public GenericTTCModule
{
public:

  /**
   * The constructor.
   * @param bus a reference to a bus adapter to communicate with the BOBR.
   * Note that we don't have a location parameter here as the BOBR has fixed base addresses.
   */
  BOBR(HAL::VMEBusAdapterInterface& bus);

  BOBRReceiverBlock *blocks[2];

  /**
   * This defines the convention of the numbering of the two blocks
   * (whether it starts at 0 or at 1).
   */
  static const unsigned FIRST_BLOCK = 1;
  static const unsigned LAST_BLOCK = 2;

  virtual std::string firmwareVersionString();

  /**
   * Get block by number.
   * num should be 1 or 2
   */
  BOBRReceiverBlock *GetBlock(unsigned num);

  // a few methods for block 0...

  //! read identification (firmware version)
  unsigned GetGlobalIdentification();

  unsigned GetGlobalControlByte();

  unsigned GetGlobalStatusByte();

  bool IsFpgaBst1Ok();

  bool IsFpgaBst2Ok();

  bool IsEpldMuxoutOk();

  bool IsLocal40MHzOk();

  bool IsTTC1MezzaninePresent();

  bool IsTTC2MezzaninePresent();

  bool Is3V3RegulatorOk();

  bool Is2V5RegulatorOk();
};


/**
 * Corresponds to one of the two receiver blocks on the BOBR.
 */
class BOBRReceiverBlock
{

public:

  static std::string GetVerboseParticleType(unsigned particle_type);

private:

  unsigned number; // 1 or 2
  BOBR *bobr;
  const Address *message_ram_base_addr;

public:

  BOBRReceiverBlock(BOBR* _bobr, unsigned _number);

  unsigned char ReadMessageRam(unsigned offset) const;

  unsigned GetControlByte();

  unsigned GetStatusByte();

  unsigned GetConfigVersion();

  unsigned GetBlockNumberFromRegister();

  // status register bits
  // note: I do not fully understand status bits 6 and 7, so I don't include them here */

  bool IsTTCRXReady();

  bool IsLocal40MHzSigPresent();

  bool IsLocalOrbitPresent();

  bool IsTTCSerialBSignalPresent();

  bool HasTTCFrameError();

  bool IsMessageRecordingEnabled();

  // Control register bits
  // note: bit 4 and 5 are IRQ stuff
  // note: bit 7 is probably meant to be written only

  bool IsInternalMode();

  bool IsSingleShotMode();

  bool IsDPRAMWritingEnabled();

  bool IsHardwareBytesOutputEnabled();

  bool IsSPS();


  //! This is actually NOT ON after power up
  void EnableDPRAMWriting(bool enable = true);

  //! This is actually NOT ON after power up
  void EnableHardwareBytesOutput(bool enable = true);

  unsigned GetBstMasterNumber();

  //! Seconds since 1.1.1970 UTC.
  std::time_t GetUnixTime() const;

  //! Returns only the fractional part, does not include seconds etc.
  unsigned GetMicroSeconds() const;

  std::string GetPosixTime() const;

  //! @param counter_num can be 0 or 1
  unsigned long GetOrbitCounter(unsigned counter_num);

  unsigned long GetTurnCount();

  unsigned long GetLHCFillNumber();

  unsigned GetNumericBeamMode();

  //! @param beam must be 1 or 2
  unsigned GetNumericBeamParticleType(unsigned beam);

  //! get beam momentum in GeV/c
  unsigned GetBeamMomentum();

  /**
   * @param beam must be 1 or 2
   * @return beam intensity in units of 10e10 charges
   */
  unsigned GetBeamIntensity(unsigned beam);
};

}


#endif
