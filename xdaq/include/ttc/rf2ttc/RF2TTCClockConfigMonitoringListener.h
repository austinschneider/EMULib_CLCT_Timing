#ifndef _ttc_rf2ttc_rf2ttcclockconfigmonitoringlistener_h_
#define _ttc_rf2ttc_rf2ttcclockconfigmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"

#include "ttc/rf2ttc/RF2TTC.hh"

#include <sstream>


namespace ttc
{

class RF2TTCControl;
class RF2TTCProxy;


class RF2TTCClockConfigMonitoringListener : public CallbackMonitoringListener
{

public:

  RF2TTCClockConfigMonitoringListener(xdaq::Application* app);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

private:

  void refreshOutputSource(const Component& component, std::ostringstream& value);

  void refreshOperatingMode(const Component& component, std::ostringstream& value);

  void refreshQPLLAutoRelock(const Component& component, std::ostringstream& value);

  void refreshOutputDelay25Enabled(const Component& component, std::ostringstream& value);

  void refreshOutputDelay25Units(const Component& component, std::ostringstream& value);

  //! gets the RF2TTCControl (casts app to concrete type)
  RF2TTCControl& getRF2TTCControl();

  //! gets the RF2TTC locking proxy object
  RF2TTCProxy& getRF2TTCProxy();


  //! container to map clock local ID to BC channel
  std::map<std::string, RF2TTC::BCChannel> mapClockIdToChannel_;
};

}


#endif
