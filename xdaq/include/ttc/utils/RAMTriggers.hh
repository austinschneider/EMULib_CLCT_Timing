#ifndef _ttc_utils_RAMTriggers_hh_
#define _ttc_utils_RAMTriggers_hh_


#include <vector>


namespace ttc
{

class GenericTTCModule;
class Address;

//! A class to handle (random or regular) RAM triggers for TTCci and LTC.
class RAMTriggers
{
// static

public:

  //! maximum number of entries in the trigger pattern RAM
  static const size_t RAM_TRIG_PATTERN_MAX_LENGTH;

  //! Value written to the trigger pattern RAM to stop the sequence.
  static const unsigned RAM_TRIG_PATTERN_STOP;

  /**
   *  Value written to the trigger pattern RAM to repeat the sequence
   *  (before reaching the end of the RAM where the sequence
   *  appears to be repeated anyway if no stop flag is found).
   */
  static const unsigned RAM_TRIG_PATTERN_REPEAT;

  /**
   * This value, if written to the trigger pattern RAM,
   * causes the maximally possible delay and does not produce a trigger after it
   * (i.e. the next entry in the RAM can be a shorter delay causing a trigger,
   * or this value again, which will delay even more).
   */
  static const unsigned RAM_TRIG_MAX_DELAY;

// members

public:

  bool DirectlyWriteTriggerDPRAM;

  double triggerFrequency;

  bool randomTrigger;

  //! vector holding the trigger RAM pattern
  std::vector<uint32_t> triggerdelay;

  RAMTriggers(
      GenericTTCModule& _module,
      const Address& _start_trig_dpram_addr);

  /**
   * Loads the TTCci's trigger RAM with a corresponding to given parameters:
   *   @param frequency specifies the desired trigger frequency.
   *   @param random determines whether a random or regular trigger pattern should be generated.
   */
  void SetInternalTriggerFrequency(const double frequency, bool random = false);

  //! Same as SetInternalTriggerFrequency, but for the LTC.
  void SetInternalTriggerFrequencyLTC(const double frequency, bool random = false);

  //! returns reference to the vector of trigger delays (cached in memory) determining the trigger pattern
  std::vector<unsigned>& GetTriggerDelays();

  bool CanSetInternalTriggerFrequency() const;

  double GetInternalTriggerFrequency() const;

  bool GetInternalTriggerRandom() const;

  //! clears the vector with the trigger RAM pattern
  void ClearTriggerDelays();

  //! writes the delay pattern to the TTCci trigger RAM
  void WriteTriggerDelaysToTTCci(bool repeat_sequence = true);

  //! writes the delay pattern to the LTC trigger RAM
  void WriteTriggerDelaysToLTC(bool repeat_sequence = true);

  /**
   * sets the trigger RAM pattern to 'no trigger'
   * by directly writing a stop flag to the beginning of the RAM
   */
  void ClearDPRAM();

private:

  //! referenct to TTCci or LTC module for which this class handles RAM triggers
  GenericTTCModule& module;

  //! reference to ttc::Address corresponding to the begining of the TTCci or LTC trigger RAM
  const Address& start_trig_dpram_addr;

  //! reads RAM trigger delays directly from TTCci (w/o modifying triggerdelay)
  std::vector<unsigned> GetRAMTriggerDelaysFromTTCci();

  //! directly loads passed vector @param values to the TTCci RAM, w/o modifications
  void SetRAMTriggerDelaysDirectly(const std::vector<unsigned> &values);
};

}


#endif
