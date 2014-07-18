#ifndef _ttc_ttcci_TTCciControl_hh_
#define _ttc_ttcci_TTCciControl_hh_


#include "ttc/utils/BoardLockingProxy.hh"
#include "ttc/utils/TTCXDAQBase.hh"

#include "ttc/ttcci/TTCci.hh"
#include "ttc/ttcci/TTCciQPLLMonitoringListener.h"
#include "ttc/ttcci/TTCciStatusMonitoringListener.h"
#include "ttc/ttcci/TTCciScalersMonitoringListener.h"
#include "ttc/ttcci/TTCciConfigMonitoringListener.h"

#include "ttc/utils/HTMLFieldElement.hh"
#include "ttc/utils/LockMutex.hh"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"

#include <string>


namespace ttc
{

class TTCciControlSoapHandler;


//! proxy class managing resources for talking to TTCci
class TTCciProxy : public BoardLockingProxy
{
public:

  TTCciProxy();

  BoardTempLocker<TTCci> operator->();

  void initAdditionalParams(
      const uint32_t& bTimeCorrection,
      const uint32_t& delayT2Correction);

protected:

  virtual TTCci* createPtr(HAL::VMEBusAdapterInterface* busAdapter);

  uint32_t bTimeCorrection_;
  uint32_t delayT2Correction_;
};


//! XDAQ application controlling TTCci hardware.
class TTCciControl : public TTCXDAQBase
{

  friend class TTCciControlSoapHandler;

public:

  XDAQ_INSTANTIATOR();

  TTCciControl(xdaq::ApplicationStub* stub);

  virtual ~TTCciControl();

  virtual TTCciProxy& boardLockingProxy();

  virtual std::string softwareVersion();

private:

  // SOAP - application info space

  virtual void itemRetrieveAction(xdata::ItemRetrieveEvent& e);

  virtual void itemChangedAction(xdata::ItemChangedEvent& e);

  virtual void setDefaultValuesAction();


  // SOAP - FSM

  virtual void ConfigureAction(toolbox::Event::Reference e);

  virtual void EnableAction(toolbox::Event::Reference e);

  virtual void StopAction(toolbox::Event::Reference e);

  virtual void SuspendAction(toolbox::Event::Reference e);


  // CGI

  /**
   * Helper method implementing callback for some submit buttons
   * (e.g. 'execute sequence' on the sequence editing page).
   */
  virtual void CommandImpl(cgicc::Cgicc& cgi, const std::string& command);

  //! the default web page of the web application
  virtual void HTMLPageMain(xgi::Input* in, xgi::Output* out);

  //! The TTCci Main Configuration page
  void HTMLPageMainConfiguration(xgi::Input* in, xgi::Output* out);

  //! The TTCci BGO Configuration page
  void HTMLPageBGOConfiguration(xgi::Input* in, xgi::Output* out);

  //! The TTCci Sequences page
  void HTMLPageSequences(xgi::Input* in, xgi::Output* out);

  //! The TTCci Cyclic Generators page
  void HTMLPageCyclicGenerators(xgi::Input* in, xgi::Output* out);

  //! The TTCci Summary page
  void HTMLPageSummary(xgi::Input* in, xgi::Output* out);

  void HTMLPageRegisterAccess(xgi::Input* in, xgi::Output* out);

  //! small HTML page (which can be used as a popup) which displays BGO counters.
  void HTMLPageCountersPopup(xgi::Input *in, xgi::Output* out);

  void HTMLPageCommandNewConfigFile(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandWriteConfigFile(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandMainConfig(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandTriggerRules(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandSelectBGO(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandConfigureBGO(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandSelectSequence(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandEditSequence(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandConfigureCyclicGenerator(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandSendVMEBData(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandRegisterAccess(xgi::Input* in, xgi::Output* out);


  // utilities

  virtual void initHTMLFields();

  virtual void ErrorStatement(xgi::Output& out);

  void ReadTTCciCounters();

  void GetFileList();

  uint32_t GetBGOWord(size_t channel, size_t iword, bool takeDword);


  // info space items

  //! B-Channel timing correction
  xdata::UnsignedInteger32 BTimeCorrection_;

  xdata::UnsignedInteger32 DelayT2Correction_;

  //! tells whether TTCci hardware access resources have been successfully initialized
  xdata::Boolean TTCciObjectCreated_;

  uint32_t previousEventCounter_;
  xdata::UnsignedInteger32 EventCounter_;

  uint32_t previousOrbitCounter_;
  xdata::UnsignedInteger32 OrbitCounter_;

  uint32_t previousStrobeCounter_;
  xdata::UnsignedInteger32 StrobeCounter_;

  xdata::UnsignedInteger32 BoardStatus_;

  xdata::Boolean QPLLLocked_;

  std::vector<xdata::UnsignedInteger32> NumBgosRequested_;
  std::vector<xdata::UnsignedInteger32> NumBgosCancelled_;

  xdata::String ClockSource_;

  xdata::UnsignedInteger32 ClockFrequency_;

  xdata::String OrbitSource_;

  xdata::String TriggerSource_;

  xdata::String BGOSource_;


  // other parameters

  size_t currentBGO_;

  // For debug registers VMEDATS/L:
  bool debugb_short_;
  uint32_t debugbdata_;

  ttc::Mutex countersPopup_mutex_;


  //! the soap handler
  TTCciControlSoapHandler* soapHandler_;


  // HTML stuff
  ttc::HTMLFieldElement InputFileList;
  ttc::HTMLFieldElement CurrentBGOList;
  ttc::HTMLFieldElement CurrentCyclicList;
  ttc::HTMLFieldElement TriggerSourceList;
  ttc::HTMLFieldElement TriggerSourceList_other;
  ttc::HTMLFieldElement OrbitSourceList;
  ttc::HTMLFieldElement ClockSourceList;
  ttc::HTMLFieldElement BGOSourceList;
  ttc::HTMLFieldElement BGOSourceList_other;
  ttc::HTMLFieldElement VMEAddrList1;
  ttc::HTMLFieldElement VMEAddrList2;
  ttc::HTMLFieldElement DataTypeSelector;
  ttc::HTMLFieldElement SequenceSelector;


  //! the LTC board proxy object
  TTCciProxy ttcciProxy_;

  TTCciQPLLMonitoringListener monQPLL_;
  TTCciStatusMonitoringListener monStatus_;
  TTCciScalersMonitoringListener monScalers_;
  TTCciConfigMonitoringListener monConfig_;
};

}


#endif
