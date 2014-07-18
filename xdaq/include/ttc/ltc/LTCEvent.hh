#ifndef _ttc_ltc_LTCEvent_hh_
#define _ttc_ltc_LTCEvent_hh_


#include <string>
#include <vector>
#include <ostream>


namespace ttc
{

//! Class representing one entry in LTC's event fifo.
class LTCEvent
{
public:

  LTCEvent(size_t BTCorrection = 0, size_t ATCorrection = 0);

  LTCEvent(const std::vector<uint32_t>& Data, size_t BTCorrection = 0, size_t ATCorrection = 0);

  uint32_t GetStrobeCounter() const;

  uint32_t GetEventCounter() const;

  uint32_t GetBunchCounter() const;

  uint32_t GetOrbitCounter() const;

  uint32_t GetBlockedCounter() const;

  size_t GetTTSWord() const;

  std::string GetTTSStatusString(const size_t idx, const bool htmlcolors = false) const;

  bool IsReady(size_t idx) const;

  bool IsDisconnected(size_t idx) const;

  bool IsOutOfSync(size_t idx) const;

  bool IsWarning(size_t idx) const;

  bool IsBusy(size_t idx) const;

  bool IsRAMTrigger() const;

  bool IsVMETrigger() const;

  bool IsHWTrigger(size_t idx = 99) const;

  bool IsCyclicTrigger(size_t idx = 99) const;

  bool IsBGO() const;

  void Print(std::ostream& out, bool html = false) const;

  size_t BGOChannel() const;

  bool IsSuppressed() const;

  bool IsBXMaskOK() const;

private:

  std::vector<uint32_t> data;
  size_t BTCorr;
  size_t ATCorr;

  bool CheckReady(size_t pattern) const;

  bool CheckDisconnected(size_t pattern) const;

  bool CheckOutOfSync(size_t pattern) const;

  bool CheckWarning(size_t pattern) const;

  bool CheckBusy(size_t pattern) const;

  void Set(const std::vector<uint32_t>& Data);

  std::vector<uint32_t> Get() const;

  void Clear();

  size_t NWordsPerEvent() const;

  uint32_t GetGPSWord0() const;

  void SetGPSWord0(const uint32_t GPSwd);

  uint32_t GetGPSWord1() const;

  void SetGPSWord1(const uint32_t GPSwd);

  void SetGPSWords(const uint32_t GPSwd0, const uint32_t GPSwd1);

  void SetStrobeCounter(const uint32_t cntr);

  void SetEventCounter(const uint32_t cntr);

  void SetBunchCounter(const uint32_t BC);

  void SetOrbitCounter(const uint32_t orbit);

  size_t NTTS() const;

  size_t GetTTSStatusPattern(const size_t idx) const;

  bool IsOK() const;
};

class LTC;


/**
 * Class containing data read out from the LTC's event fifo
 * (mainly used for debugging).
 */
class LTCEventFIFO
{
public:

  LTCEventFIFO();

  LTCEventFIFO(const std::vector<uint32_t>& buf, const LTC& ltc);

  LTCEvent& operator[](size_t i);

  const LTCEvent& operator[](size_t i) const;

  size_t size() const;

  bool IsL1AEnabled() const;

  bool IsExternalTriggerEnabled(const size_t i) const;

  std::string GetTriggerName(const size_t i) const;

  void print(std::ostream& os, bool html = false) const;

  void tofile(const std::string& path) const;

private:

  //! pointer to LTC object
  const LTC* ltcptr;

  std::vector<LTCEvent> data;
  uint32_t BTimeCorrection_;
  bool L1AEnabled_;
  bool ExternalTriggerEnabled_[6];
  bool TTSEnabled_[7];
  bool SlinkBackpressureIgnored_;
  std::string TriggerName_[6];

  void UpdateGeneralInfo();
};


// non-member-functions in ttc namespace

std::ostream& operator<<(std::ostream& os, const LTCEvent& e);

std::ostream& operator<<(std::ostream& os, const LTCEventFIFO& e);

}


#endif
