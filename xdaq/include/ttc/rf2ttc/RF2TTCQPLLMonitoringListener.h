#ifndef _ttc_rf2ttc_rf2ttcqpllmonitoringlistener_h_
#define _ttc_rf2ttc_rf2ttcqpllmonitoringlistener_h_


#include "ttc/monitoring/QPLLMonitoringListener.h"

#include "ttc/rf2ttc/RF2TTC.hh"

#include <map>
#include <string>


namespace ttc
{

class RF2TTCControl;
class RF2TTCProxy;

class RF2TTCQPLLMonitoringListener : public QPLLMonitoringListener
{

public:

  RF2TTCQPLLMonitoringListener(xdaq::Application* app);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::QPLLMonitoringListener::setQPLLLockingState
  virtual void setQPLLLockingState(const Component& component, QPLLLockingState& qpllLockingState);

private:

  //! gets the RF2TTCControl (casts app to concrete type)
  RF2TTCControl& getRF2TTCControl();

  //! gets the RF2TTC locking proxy object
  RF2TTCProxy& getRF2TTCProxy();


  //! container to map QPLL local ID to BC channel
  std::map<std::string, RF2TTC::BCChannel> mapQpllIdToChannel_;
};

}


#endif
