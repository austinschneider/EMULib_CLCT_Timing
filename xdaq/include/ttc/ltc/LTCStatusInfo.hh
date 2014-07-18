#ifndef _ttc_ltc_LTCStatusInfo_hh_
#define _ttc_ltc_LTCStatusInfo_hh_


#include "ttc/ltc/TriggerComposition.hh"

#include <ctime>
#include <vector>


namespace ttc
{

class LTCStatusInfo
{
public:

  LTCStatusInfo();

  void Set(uint32_t orbit, uint32_t evtnum, uint32_t blockedL1As, uint32_t nbgos, uint32_t ncancelled = 0);

  void SetTriggerComposition(const TriggerComposition* Composition);

  const TriggerComposition* GetTriggerComposition() const;

  //! Delta(T) in sec
  double DeltaT() const;

  double L1ARate() const;

  double RawTriggerRate() const;

  double BlockedTriggerRate() const;

  double CancelledRate() const;

  double Efficiency() const;

  double BGORate() const;

  double L1AsPerOrbit() const;
  
  double BGOsPerOrbit() const;

  uint32_t OrbitDiff() const;

  uint32_t L1ADiff() const;

  uint32_t RawDiff() const;

  uint32_t BGODiff() const;

  double DeltaT_Accumulated() const;

  double L1ARate_Accumulated() const;

  double RawTriggerRate_Accumulated() const;

  double BlockedTriggerRate_Accumulated() const;

  double CancelledRate_Accumulated() const;

  double BGORate_Accumulated() const;

  double Efficiency_Accumulated() const;

  size_t NAccumulations() const;

  void Print() const;

private:

  std::vector<time_t> _tupdate;
  std::vector<uint32_t> _evt0;
  std::vector<uint32_t> _evt1;
  std::vector<uint32_t> _blocked0;
  std::vector<uint32_t> _blocked1;
  std::vector<uint32_t> _cancelled0;
  std::vector<uint32_t> _cancelled1;
  std::vector<uint32_t> _bgo0;
  std::vector<uint32_t> _bgo1;
  std::vector<uint32_t> _orb0;
  std::vector<uint32_t> _orb1;
  TriggerComposition _comp;

  size_t N() const;

  double DeltaT_Accum(size_t &i0, size_t &i1) const;

  time_t Time() const;
};

}


#endif
