#ifndef _ttc_utils_TTSInfo_hh_
#define _ttc_utils_TTSInfo_hh_


#include <string>


namespace ttc
{

//! Class representing the TTS info as encoded in the TTS status word read from the LTC
class TTSInfo
{
public:

  TTSInfo(const uint32_t StatusWord = 0);

  uint32_t GetStatusWord() const;

  //! Returns the number of partitions: 6 sTTS + 1 aTTS input
  size_t NPartitions() const;

  //! returns the 4 bits corresponding to the status of partition @param idx
  size_t GetStatus_Pattern(size_t idx) const;

  std::string GetStatus_String(size_t idx, bool htmlcolors = false) const;

  bool IsReady(size_t idx) const;

  bool IsDisconnected(size_t idx) const;

  bool IsOutOfSync(size_t idx) const;

  bool IsWarning(size_t idx) const;

  bool IsBusy(size_t idx) const;

  bool IsError(size_t idx) const;

private:

  uint32_t status_;

  bool CheckReady(size_t stat) const;

  bool CheckDisconnected(size_t stat) const;

  bool CheckOutOfSync(size_t stat) const;

  bool CheckWarning(size_t stat) const;

  bool CheckBusy(size_t stat) const;

  bool CheckError(size_t stat) const;
};

}


#endif
