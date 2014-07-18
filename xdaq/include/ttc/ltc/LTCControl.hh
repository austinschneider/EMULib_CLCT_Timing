#ifndef _ttc_ltc_LTCControl_hh_
#define _ttc_ltc_LTCControl_hh_


#include "ttc/utils/BoardLockingProxy.hh"
#include "ttc/utils/TTCXDAQBase.hh"

#include "ttc/ltc/LTC.hh"
#include "ttc/utils/HTMLFieldElement.hh"

#include "xdata/UnsignedInteger32.h"
#include "xdata/Double.h"

#include <string>
#include <map>


namespace ttc
{

// forward declarations

class LTCControl;
class LTCControlSoapHandler;


//! proxy class managing resources for talking to LTC
class LTCProxy : public BoardLockingProxy
{
public:
  LTCProxy();

  BoardTempLocker<LTC> operator->();

  void initAdditionalParams(
      const uint32_t& bTimeCorrection,
      const uint32_t& sLinkSrcId);

protected:
  virtual LTC* createPtr(HAL::VMEBusAdapterInterface* busAdapter);

  uint32_t bTimeCorrection_;
  uint32_t sLinkSrcId_;
};


/**
 * This class implements 'HyperDAQ the web interface' to the LTC,
 * i.e. it generates various html pages, processes form input etc.
 */
class LTCControl : public TTCXDAQBase
{
  friend class LTCControlSoapHandler;

public:

  XDAQ_INSTANTIATOR();

  LTCControl(xdaq::ApplicationStub* stub);

  virtual ~LTCControl();

  virtual LTCProxy& boardLockingProxy();

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

  virtual void CommandImpl(cgicc::Cgicc& cgi, const std::string& command);

  //! The main HyperDAQ entry point.
  virtual void HTMLPageMain(xgi::Input* in, xgi::Output* out);

  //! The LTC Main Configuration Page (long method, should be splitted)
  void HTMLPageMainConfiguration(xgi::Input* in, xgi::Output* out);

  //! The Send BGOs from VME page
  void HTMLPageBGOConfiguration(xgi::Input* in, xgi::Output* out);

  //! The LTC sequence edit page. Produces html.
  void HTMLPageSequences(xgi::Input* in, xgi::Output* out);

  //! The Cyclic Generators Page.
  void HTMLPageCyclicGenerators(xgi::Input* in, xgi::Output* out);

  //! The Summary Page. Produces html.
  void HTMLPageSummary(xgi::Input* in, xgi::Output* out);

  //! The LTC Register Access. Produces html.
  void HTMLPageRegisterAccess(xgi::Input* in, xgi::Output* out);

  //! HTML page which displays trigger and BGO rates (for use as popup).
  void HTMLPageRatesPopup(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandConfigureTTS(xgi::Input* in, xgi::Output* out);

  /**
   * This is called when the user selects a new configuration file
   * in the 'Configure LTC FROM file' radio button group on the 'LTC Control' tab.
   */
  void HTMLPageCommandNewConfigFile(xgi::Input* in, xgi::Output* out);

  /**
   * This is called when the user selects 'Write current configuration TO file'
   * in the 'LTC Control' tab.
   */
  void HTMLPageCommandWriteConfigFile(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandMainConfig(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandTriggerRulesDelays(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandVMEBGOTiming(xgi::Input* in, xgi::Output* out);

  //! callback for command to perform sequence action
  void HTMLPageCommandSequenceAction(xgi::Input* in, xgi::Output* out);

  //! callback for command to edit selected sequence
  void HTMLPageCommandEditSequence(xgi::Input* in, xgi::Output* out);

  /**
   * Evaluates a HTTP request for updating the cyclic generator configuration
   * (i.e. this is behind the 'apply' button of the cyclic generator configuration page.
   */
  void HTMLPageCommandConfigureCyclicGenerator(xgi::Input* in, xgi::Output* out);

  /**
   * Triggers reading back of the cyclic generators from the hardware
   * (used on the cyclic generator's page).
   */
  void HTMLPageCommandReadCyclicGeneratorConfig(xgi::Input* in, xgi::Output* out);

  void HTMLPageCommandRegisterAccess(xgi::Input* in, xgi::Output* out);

  //! Read from / write to LTC adresses.
  void HTMLPageSetControlRegisterBits(xgi::Input* in, xgi::Output* out);


  // utilities

 //! initialization before CGI callbacks
  virtual void initHTMLFields();

  virtual void ErrorStatement(xgi::Output& out);

  /**
   * This probably should go away as we should not support any more
   * calling the 'default' sequence which somebody has selected on the html page.
   */
  std::string GetDefaultSequenceName();

  void ReadLTCCounters();

  void GetFileList();

  /**
   * Main page helper function for generating radio buttons corresponding to a binary value
   * (actually, this is the functionality a checkbox provides...)
   */
  void WriteBinaryRadioButton(
      std::ostream &out,
      const std::string &radio_group_name,
      const std::string &text1,
      const std::string &text2,
      const std::string &value1,
      const std::string &value2,
      unsigned selected_index,
      bool disabled);


  // info space items

  xdata::String TimeOfLastStateChange_;

  //! fraction of active bunches
  xdata::Double FractionOfActiveBunches_;

  //! B-Channel timing correction
  xdata::UnsignedInteger32 BTimeCorrection_;

  xdata::UnsignedInteger32 SlinkSrcId_;

  //! Current state of TTS (summary)
  xdata::String TTSStatus_;
  xdata::String SLinkStatus_;
  xdata::String ClockSignal_;
  xdata::String OrbitSignal_;

  xdata::UnsignedInteger32 TriggerCounter_;
  xdata::UnsignedInteger32 EventCounter_;
  xdata::UnsignedInteger32 OrbitCounter_;
  xdata::UnsignedInteger32 StrobeCounter_;
  xdata::UnsignedInteger32 BlockedL1ACntr_;
  xdata::UnsignedInteger32 BoardStatus_;

  xdata::String TriggerInputs_;
  xdata::Double TotalEfficiency_;
  xdata::Double Efficiency_;
  xdata::Double AvEfficiency_;
  xdata::Double L1ARate_;
  xdata::Double AvL1ARate_;
  xdata::Double RawL1ARate_;
  xdata::Double AvRawL1ARate_;
  xdata::Double BlockedL1ARate_;

  xdata::Double DeltaT_;
  xdata::Double UptimeSec_;

  std::vector<xdata::Double> HWTriggerFraction_;

  std::vector<xdata::String> HWTriggerName_;

  std::vector<xdata::Boolean> HWTriggerEnable_;

  std::vector<xdata::Double> HWTriggerDelay_;

  xdata::String ClockSource_;
  xdata::UnsignedInteger32 ClockFrequency_;

  xdata::UnsignedInteger32 RunNumber_;

  // other parameters

  int resetbits_;
  bool OverwriteRunNumber_;

  //! the soap handler
  LTCControlSoapHandler* soapHandler_;

  // HTML field elements
  ttc::HTMLFieldElement RegList;
  ttc::HTMLFieldElement InputFileList;
  ttc::HTMLFieldElement CurrentBGOList;
  ttc::HTMLFieldElement CurrentCyclicList;
  ttc::HTMLFieldElement Trigselector;
  ttc::HTMLFieldElement BGOselector;
  ttc::HTMLFieldElement VMEAddrList1;
  ttc::HTMLFieldElement VMEAddrList2;
  ttc::HTMLFieldElement DataTypeSelector;
  ttc::HTMLFieldElement SequenceSelector;

  //! the LTC board proxy object
  LTCProxy ltcProxy_;
};

}


#endif
