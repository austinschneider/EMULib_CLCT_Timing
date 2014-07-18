#ifndef _ttc_utils_BGOChannel_hh_
#define _ttc_utils_BGOChannel_hh_


#include <stdint.h>
#include <vector>
#include <set>
#include <string>


#define BGO_SINGLEBIT 31
#define BGO_DOUBLEBIT 30
#define BGO_BLOCKBIT 29
#define BGO_REPETITIVE 28
#define BGO_TIME1SHIFT 12
#define BGO_ISLASTBIT 2
#define BGO_NOTRANSMITBIT 1
#define BGO_PRESCALESHIFT 16


namespace ttc
{

// types

enum BGODataLength
{
  UNSET = 0,
  SINGLE = 1,
  DOUBLE = 2,
  BLOCK = 3
};


//! class BGOChannel
class BGOChannel
{

// static
public:

  static const size_t maxcommands = 1024;

// member
public:

  BGOChannel(const unsigned int ChannelID);

  void Set(const unsigned int ChannelID);

  void Reset();

  //! returns true if data integrity is ok
  bool IsOK() const;

  //! throws exception if data integrity is violated
  void Check() const;

  //! Sets name for this BGO channel (e.g. 'BC0' or 'TestEnable')
  void SetName(const std::string &Name);

  //! returns name of BGO channel
  std::string GetName() const;

  /**
   * returns true iff the given name matches the name of this BGOChannel or any of the alternatives
   * @param case_sensitive specifies whether matching shall be case sensitive
   */
  bool MatchesNameOrAlternative(std::string name, bool case_sensitive);

  //! adds an alternative name for this BGOChannel (use case: 'resynch' in addition to 'resync')
  void AddAlternativeName(const std::string &name);

  //! adds several alternative names for this BGOChannel at once
  void AddAlternativeNames(const std::vector<std::string> &names);

  BGODataLength GetDataLength() const;

  uint32_t GetPrescale() const;

  uint32_t GetInitialPrescale() const;

  uint32_t GetPostscale() const;

  uint32_t GetDelayTime1() const;

  uint32_t GetDelayTime2() const;

  bool IsSingleCommand() const;

  bool IsDoubleCommand() const;

  bool IsBlockCommand() const;

  void SetPreAndInitPrescale(const uint32_t Prescale, const uint32_t InitPrescale = 0);

  void SetPostscale(const uint32_t val);

  //! Retrieve the full words so that they can be written to the registers
  uint32_t InhibitDelayWord() const;

  uint32_t PrescaleWord() const;

  uint32_t PostscaleWord() const;

  //! Setting with full words
  void SetInhibitDelayWord(const uint32_t wd);

  void SetPrescaleWord(const uint32_t wd);

  void SetPostscaleWord(const uint32_t wd);

protected:

  std::string name;
  unsigned int channel;
  uint32_t delay_;

  //! value corresponding to register TTCciAdd::CHIHB of the TTCci for this channel
  uint32_t inhibitDelay;

  uint32_t prescale;
  uint32_t postscale;

  //! Alternative names which are accepted in configuration files for this channel.
  std::set<std::string> alternative_names;
};

}


#endif
