#ifndef _ttc_ttcci_ttcciscalersmonitoringlistener_h_
#define _ttc_ttcci_ttcciscalersmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"
#include <sstream>


namespace ttc
{

class TTCciControl;
class TTCciProxy;


class TTCciScalersMonitoringListener : public CallbackMonitoringListener
{

public:

  TTCciScalersMonitoringListener(xdaq::Application* app, const double& periodSecs = 30);

protected:

  //! implements ttc::MonitoringListener::addComponents
  virtual void addComponents();

  //! implements ttc::MonitoringListener::addItems
  virtual void addItems();

private:

  void refreshOrbitCount(const Component& component, std::ostringstream& value);

  void refreshOrbitRateHz(const Component& component, std::ostringstream& value);

  void refreshL1ACount(const Component& component, std::ostringstream& value);

  void refreshL1ARateHz(const Component& component, std::ostringstream& value);

  void refreshBGORequestCount(const Component& component, std::ostringstream& value);

  void refreshBGORequestRateHz(const Component& component, std::ostringstream& value);

  //! gets the TTCciControl (casts app to concrete type)
  TTCciControl& getTTCciControl();

  //! gets the TTCci locking proxy object
  TTCciProxy& getTTCciProxy();

  double periodSecs_;

  std::map<std::string, float> mapComponentKeyToOrbitRateHz_;
  std::map<std::string, float> mapComponentKeyToL1ARateHz_;
  std::map<std::string, float> mapComponentKeyToBGORequestRateHz_;
};

}


#endif
