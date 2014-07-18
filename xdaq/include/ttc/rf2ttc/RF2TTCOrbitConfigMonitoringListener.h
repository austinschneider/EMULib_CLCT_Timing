#ifndef _ttc_rf2ttc_rf2ttcorbitconfigmonitoringlistener_h_
#define _ttc_rf2ttc_rf2ttcorbitconfigmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"

#include "ttc/rf2ttc/RF2TTC.hh"

#include <sstream>


namespace ttc
{

class RF2TTCControl;
class RF2TTCProxy;


class RF2TTCOrbitConfigMonitoringListener : public CallbackMonitoringListener
{

public:

  RF2TTCOrbitConfigMonitoringListener(xdaq::Application* app);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

private:

  void refreshOutputSource(const Component& component, std::ostringstream& value);

  void refreshOperatingMode(const Component& component, std::ostringstream& value);

  void refreshOutputDelayCoarseBX(const Component& component, std::ostringstream& value);

  void refreshOutputDelay25Enabled(const Component& component, std::ostringstream& value);

  void refreshOutputDelay25Units(const Component& component, std::ostringstream& value);

  void refreshInputDACUnits(const Component& component, std::ostringstream& value);

  void refreshInputDelay25Enabled(const Component& component, std::ostringstream& value);

  void refreshInputDelay25Units(const Component& component, std::ostringstream& value);

  //! gets the RF2TTCControl (casts app to concrete type)
  RF2TTCControl& getRF2TTCControl();

  //! gets the RF2TTC locking proxy object
  RF2TTCProxy& getRF2TTCProxy();


  //! container to map orbit local ID to orbit channel
  std::map<std::string, RF2TTC::OrbitChannel> mapOrbitIdToChannel_;
};

}


#endif
