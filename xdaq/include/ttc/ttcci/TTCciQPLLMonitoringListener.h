#ifndef _ttc_ttcci_ttcciqpllmonitoringlistener_h_
#define _ttc_ttcci_ttcciqpllmonitoringlistener_h_


#include "ttc/monitoring/QPLLMonitoringListener.h"


namespace ttc
{

class TTCciControl;
class TTCciProxy;

class TTCciQPLLMonitoringListener : public QPLLMonitoringListener
{

public:

  TTCciQPLLMonitoringListener(xdaq::Application* app);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::QPLLMonitoringListener::setQPLLLockingState
  virtual void setQPLLLockingState(const Component& component, QPLLLockingState& qpllLockingState);

  //! reimplements ttc::QPLLMonitoringListener::setQPLLLockingStateLatched
  virtual void setQPLLLockingStateLatched(const Component& component, QPLLLockingState& qpllLockingStateLatched);

private:

  //! gets the TTCciControl (casts app to concrete type)
  TTCciControl& getTTCciControl();

  //! gets the TTCci locking proxy object
  TTCciProxy& getTTCciProxy();
};

}


#endif
