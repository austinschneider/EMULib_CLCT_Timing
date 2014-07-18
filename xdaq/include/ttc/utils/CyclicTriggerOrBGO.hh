#ifndef _ttc_utils_CyclicTriggerOrBGO_hh_
#define _ttc_utils_CyclicTriggerOrBGO_hh_


#include <iostream>
#include <sstream>
#include <stdint.h>

// Format macros:
#define CTB_STARTBX_OFFS 12
#define CTB_STARTBX_WDTH 12
#define CTB_REPETITIVE_BIT 28
#define CTB_ENABLE_BIT 29
#define CTB_PERMANENT_BIT 31 // 30?
#define CTB_IPRESC_OFFS 0
#define CTB_IPRESC_WDTH 16
#define CTB_PRESC_OFFS 0
#define CTB_PRESC_WDTH 16
#define CTB_POSTSC_OFFS 0
#define CTB_POSTSC_WDTH 16
#define CTB_PAUSE_OFFS 0
#define CTB_PAUSE_WDTH 16
#define CTB_TYPE_OFFS 0
#define CTB_TYPE_WDTH 5


namespace ttc
{

//! class representing a cyclic trigger or BGO
class CyclicTriggerOrBGO
{

public:

  CyclicTriggerOrBGO(
      const bool forTrigger,
      const unsigned id,
      const unsigned int btimecorr = 0);

  void Reset();

  bool Changed() const;

  std::string GetName() const;

  //! Prints information about this cyclic trigger/BGO generator.
  void Print(std::ostream& os) const;

  // The following methods are getters and setters for several words corresonding to cyclig trigger/BGO functions.

  uint32_t GetInhibitWd() const;

  uint32_t GetInitPrescaleWd() const;

  uint32_t GetPrescaleWd() const;

  uint32_t GetPostscaleWd() const;

  uint32_t GetPauseWd() const;

  uint32_t GetTypeWd() const;

  void SetInhibitWd(const uint32_t val);

  void SetInitPrescaleWd(const uint32_t val);

  void SetPrescaleWd(const uint32_t val);

  void SetPostscaleWd(const uint32_t val);

  void SetPauseWd(const uint32_t val);

  void SetTypeWd(const uint32_t val);

  // The following methods are getters/setters for unpacked (high-level) functions of cyclic triggers/BGOs.

  unsigned int GetID() const;

  bool IsTrigger() const;

  bool IsBGO() const;

  uint32_t GetStartBX() const;

  void SetStartBX(const uint32_t val);

  bool IsRepetitive() const;

  void SetRepetitive(const bool repetitive = true);

  bool IsPermanent() const;

  void SetPermanent(const bool permanent = true);

  bool IsEnabled() const;

  void SetEnable(const bool enable = true);

  uint32_t GetInitialPrescale() const;

  void SetInitialPrescale(const uint32_t val);

  uint32_t GetPrescale() const;

  void SetPrescale(const uint32_t val);

  uint32_t GetPostscale() const;

  void SetPostscale(const uint32_t val);

  uint32_t GetPause() const;

  void SetPause(const uint32_t val);

  uint32_t GetBChannel() const;

  void SetBChannel(const uint32_t val);

private:

  bool _trigger;
  unsigned int _id;
  uint32_t wd_inhibit;
  uint32_t wd_initialpresc;
  uint32_t wd_presc;
  uint32_t wd_postsc;
  uint32_t wd_pause;
  uint32_t wd_type;
  uint32_t BTimeCorrection_;
};

std::ostream&
operator <<(std::ostream& os, const CyclicTriggerOrBGO& generator);

}


#endif
