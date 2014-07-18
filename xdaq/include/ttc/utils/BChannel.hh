#ifndef _ttc_utils_BChannel_hh_
#define _ttc_utils_BChannel_hh_


#include "ttc/utils/BGOChannel.hh"

#include <stdint.h>


namespace ttc
{

class BChannel : public BGOChannel
{
public:

  BChannel(const unsigned int ChannelID, const uint32_t DelayT2Correction = 0);

  void ClearWords();

  //! Clears the data content of this BGO.
  void Reset();

  bool IsOK() const;

  void Check() const;

  void SetData(
      const size_t index,
      const uint32_t data,
      const bool isShort,
      const bool isACommand = false,
      const bool isLast = false,
      const bool NoTransmit = false);

  /**
   * Adds another B frame to the BGO channel.
   * Adds also an empty B frame after this and
   * calls MakeLast() to terminate the structure in the TTCci's D/P RAM properly
   * (doesn't write the data to the TTCci).
   */
  void PushBackData(
      const uint32_t data,
      const bool isShort,
      const bool isACommand = false,
      const bool NoTransmit = false);

  bool IsRepetitive() const;

  void Set(
      const BGODataLength L,
      const bool repetitive,
      const uint32_t delayTime1 = 0,
      const uint32_t delayTime2 = 0);

  //! sets just the delay1
  void SetDelay1(const uint32_t delayTime1);

  uint32_t InhibitDelayWord_corr() const;

  //! Word to be written to the CHxD[index] memory location of the TTCci (where x is the BGO channel)
  uint32_t DataWord_D(const size_t index) const;

  //! Word to be written to the CHxP[index] memory location of the TTCci (where x is the BGO channel).
  uint32_t DataWord_P(const size_t index) const;

  bool IsLastWord(const size_t index) const;

  bool IsShortWord(const size_t index) const;

  bool IsACommand(const size_t index) const;

  size_t NWords() const;

  void DeleteWord(const size_t index);

  void SetDataWord_D(const size_t index, const uint32_t wd);

  void SetDataWord_P(const size_t index, const uint32_t wd);

  void PushBackDataWord_D(const uint32_t wd);

  void PushBackDataWord_P(const uint32_t wd);

  /**
   * Sets the data content of the command at 'index' to 0 (short B command),
   * sets its 'islast' and 'notransmit' bits.
   */
  void MakeLast(const size_t index);

  /**
   * Returns the individual postscale value for word 'index'.
   * This can only be called if the firmware supports it,
   * which is not checked here (call TTCci::HasIndividualBPostScaleNumbers() to find out).
   * TODO: check with Magnus if bits returned from P register are those needed.
   */
  unsigned GetIndividualPostScaleValue(unsigned index) const;

  void SetIndividualPostScaleValue(unsigned index, unsigned value);

  void Print(std::ostream &os) const;

private:

  void RemoveDataWordsSetToLast();

  std::vector<uint32_t> data_D;
  std::vector<uint32_t> data_P;
  uint32_t DelayT2Correction_;
};


std::ostream & operator<<(std::ostream &os, const BChannel &channel);

}


#endif
