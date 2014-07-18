#ifndef _ttc_rf2ttc_rf2ttcconfigmonitoringlistener_h_
#define _ttc_rf2ttc_rf2ttcconfigmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"

#include <sstream>


namespace ttc
{

class RF2TTCControl;
class RF2TTCProxy;


class RF2TTCConfigMonitoringListener : public CallbackMonitoringListener
{

public:

  RF2TTCConfigMonitoringListener(xdaq::Application* app);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

private:

  void refreshBoardSlot(const Component& component, std::ostringstream& value);

  void refreshUsedBusAdapter(const Component& component, std::ostringstream& value);

  void refreshFirmwareVersion(const Component& component, std::ostringstream& value);

  void refreshConfigurationDataSource(const Component& component, std::ostringstream& value);

  void refreshConfigurationDataFile(const Component& component, std::ostringstream& value);

  void refreshFSMState(const Component& component, std::ostringstream& value);

  //! gets the RF2TTCControl (casts app to concrete type)
  RF2TTCControl& getRF2TTCControl();

  //! gets the RF2TTC locking proxy object
  RF2TTCProxy& getRF2TTCProxy();
};

}


#endif
