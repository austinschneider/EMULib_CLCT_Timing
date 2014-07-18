#ifndef _ttc_ltc_Monitoring_hh_
#define _ttc_ltc_Monitoring_hh_


#include "ttc/ltc/LTCEvent.hh"
#include "ttc/ltc/TriggerComposition.hh"
#include "ttc/ltc/StateChanges.hh"
#include "ttc/utils/Utils.hh"

#include <stdint.h>
#include <ctime>
#include <iostream>


namespace ttc
{

class LTCStatusInfo;


struct MonitoringStruct
{
  time_t time;
  double L1ARate;
  double L1ARate_Accum;
  double BGORate;
  double BGORate_Accum;
  double CancelRate;
  double CancelRate_Accum;
  double BlockedRate;
  double BlockedRate_Accum;
  double AccumTime;
  double Efficiency;
  double Efficiency_Accum;
  double TotalEfficiency;
  double TTS[10];
  double slink;
};


class Monitoring
{
public:
  Monitoring(
      size_t BTCorrection = DEFAULT_LTC_BTC,
      size_t ATCorrection = 0,
      size_t maxbufsize = 2048,
      std::ostream* outputstream = &std::cout);

  void Flush();

  size_t N() const;

  size_t Nmax() const;

  void SetEventFIFO(const LTCEventFIFO& myevts);

  void SetRunNumber(const int32_t No);

  void Print(std::ostream& out = std::cout) const;

  void NewState(const std::string& Name);

  LTCEventFIFO GetEventFIFO() const;

  const TriggerComposition* GetTriggerComposition() const;

  double RunDuration() const;

  void SetLTCStatusInfo(LTCStatusInfo *stat = 0);

private:

  LTCStatusInfo *Status;
  const size_t nmax;
  LTCEventFIFO buf;
  std::ostream *out_;
  int32_t runno;
  StateChanges MyStates;
  size_t BTCorr;
  size_t ATCorr;
  TriggerComposition Comp;
  time_t tinit;
};

}


#endif
