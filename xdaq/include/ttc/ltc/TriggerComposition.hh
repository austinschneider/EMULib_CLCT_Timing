#ifndef _ttc_ltc_TriggerComposition_hh_
#define _ttc_ltc_TriggerComposition_hh_


#include <vector>
#include <iostream>
#include <stdint.h>


namespace ttc
{

class TriggerComposition
{
private:

  static const size_t _NN = 7;
  static const size_t _Nmax = 5000;

public:

  TriggerComposition();

  void Clear();

  size_t N() const
  {
    return _NN;
  }

  void SetTrigger(const std::vector<bool>& trig);

  void SetTrigger(bool HW0, bool HW1, bool HW2, bool HW3, bool HW4, bool HW5, bool INT = false);

  double GetTriggerFraction(size_t itrig, size_t itrig2 = 999) const;

  uint32_t GetSum() const;

  void Print(std::ostream &out = std::cout) const;

private:

  size_t _n;
  size_t _countall;
  size_t _countall0;
  std::vector<uint32_t> _counter;
  std::vector<uint32_t> _counter0;
  uint32_t _cnt[_NN][_NN];
  uint32_t _cnt0[_NN][_NN];
};

}


#endif
