#ifndef _ttc_ttcci_ttccistatusmonitoringlistener_h_
#define _ttc_ttcci_ttccistatusmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"
#include <sstream>


namespace ttc
{

class TTCciControl;
class TTCciProxy;


class TTCciStatusMonitoringListener : public CallbackMonitoringListener
{

public:

  TTCciStatusMonitoringListener(xdaq::Application* app, const double& periodSecs = 30);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

private:

  void refreshClockInverted(const Component& component, std::ostringstream& value);

  void refreshClockSingleEventUpset(const Component& component, std::ostringstream& value);

  void refreshClockSingleEventUpsetLatched(const Component& component, std::ostringstream& value);

  void refreshDataClockSyncError(const Component& component, std::ostringstream& value);

  void refreshDataClockSyncErrorLatched(const Component& component, std::ostringstream& value);

  void refreshOrbitSyncError(const Component& component, std::ostringstream& value);

  void refreshOrbitSyncErrorLatched(const Component& component, std::ostringstream& value);

  void refreshL1AVetoedByTriggerRules(const Component& component, std::ostringstream& value);

  void refreshL1AVetoedByTriggerRulesLatched(const Component& component, std::ostringstream& value);

  void refreshL1AMissed(const Component& component, std::ostringstream& value);

  void refreshL1AMissedLatched(const Component& component, std::ostringstream& value);

  void refreshDoubleL1A(const Component& component, std::ostringstream& value);

  void refreshDoubleL1ALatched(const Component& component, std::ostringstream& value);

  void refreshBDataCancelled(const Component& component, std::ostringstream& value);

  void refreshBDataCancelledLatched(const Component& component, std::ostringstream& value);

  //! gets the TTCciControl (casts app to concrete type)
  TTCciControl& getTTCciControl();

  //! gets the TTCci locking proxy object
  TTCciProxy& getTTCciProxy();
};

}


#endif
