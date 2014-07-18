#ifndef _ttc_ltc_StatusChanges_hh_
#define _ttc_ltc_StatusChanges_hh_


#include <string>
#include <vector>
#include <ctime>

namespace ttc
{

enum Action
{
  COLDRESET, CONFIGURE, ENABLE, SUSPEND, STOP, UNKNOWN
};


struct StateEvent
{
  Action act;
  time_t t;
};


class StateChanges
{
public:

  StateChanges();

  void push_back(const StateEvent& evt);

  void push_back(const std::string& statename);

  void push_back(const Action statechange);

  void push_back(const Action statechange, const time_t time);

  size_t size() const;

  StateEvent* Get(const size_t idx);

  const StateEvent* Get(const size_t idx) const;

  void Delete(const size_t idx);

private:

  std::vector<StateEvent> states;
};


// non-member-functions in namespace ttc

Action State(const std::string& Name);

std::string State(const Action State);

}


#endif
