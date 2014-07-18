#ifndef _ttc_ttcci_ttcciconfigmonitoringlistener_h_
#define _ttc_ttcci_ttcciconfigmonitoringlistener_h_


#include "ttc/monitoring/CallbackMonitoringListener.h"
#include <sstream>


namespace ttc
{

class TTCciControl;
class TTCciProxy;


class TTCciConfigMonitoringListener : public CallbackMonitoringListener
{

public:

  TTCciConfigMonitoringListener(xdaq::Application* app);

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

  void refreshBTimeCorrection(const Component& component, std::ostringstream& value);

  void refreshDelayT2Correction(const Component& component, std::ostringstream& value);

  void refreshFSMState(const Component& component, std::ostringstream& value);

  void refreshPeriodicSequenceEnabled(const Component& component, std::ostringstream& value);

  void refreshPeriodicSequencePeriodSecs(const Component& component, std::ostringstream& value);

  void refreshConfiguringResetsQPLL(const Component& component, std::ostringstream& value);

  void refreshQPLLAutoRestart(const Component& component, std::ostringstream& value);

  void refreshClockInputSource(const Component& component, std::ostringstream& value);

  void refreshOrbitSource(const Component& component, std::ostringstream& value);

  void refreshL1ASource(const Component& component, std::ostringstream& value);

  void refreshBGOSource(const Component& component, std::ostringstream& value);

  void refreshL1AEnabled(const Component& component, std::ostringstream& value);

  void refreshL1AInternalFrequencyHz(const Component& component, std::ostringstream& value);

  void refreshL1AInternalRandomNotEqui(const Component& component, std::ostringstream& value);

  template <unsigned i>
  void refreshL1AExternalInputDelayBX(const Component& component, std::ostringstream& value);

  template <size_t i>
  void refreshTriggerRuleIntervalBX(const Component& component, std::ostringstream& value);

  void refreshLaserEnabled(const Component& component, std::ostringstream& value);

  //! gets the TTCciControl (casts app to concrete type)
  TTCciControl& getTTCciControl();

  //! gets the TTCci locking proxy object
  TTCciProxy& getTTCciProxy();
};

}


#endif
