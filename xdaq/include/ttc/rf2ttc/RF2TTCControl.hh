#ifndef _ttc_rf2ttc_RF2TTCControl_hh_
#define _ttc_rf2ttc_RF2TTCControl_hh_


#include "ttc/utils/BoardLockingProxy.hh"
#include "ttc/utils/TTCXDAQBase.hh"

#include "ttc/rf2ttc/RF2TTC.hh"
#include "ttc/rf2ttc/RF2TTCQPLLMonitoringListener.h"
#include "ttc/rf2ttc/RF2TTCConfigMonitoringListener.h"
#include "ttc/rf2ttc/RF2TTCClockConfigMonitoringListener.h"
#include "ttc/rf2ttc/RF2TTCOrbitConfigMonitoringListener.h"
#include "ttc/utils/HTMLFieldElement.hh"

#include "xdata/UnsignedInteger32.h"

#include <vector>
#include <string>


namespace ttc
{

//! proxy class managing resources for talking to RF2TTC
class RF2TTCProxy : public BoardLockingProxy
{
public:
  BoardTempLocker<RF2TTC> operator->();

protected:
  virtual RF2TTC* createPtr(HAL::VMEBusAdapterInterface* busAdapter);
};


//! class representing the RF2TTC control web application
class RF2TTCControl : public TTCXDAQBase
{
// types
public:

  //! RAII class printing HTML header at construction and footer and destruction time
  class XgiOutputHeaderFooterHandler
  {
  public:
    XgiOutputHeaderFooterHandler(
        RF2TTCControl* _rf2ttc_control,
        xgi::Output& out,
        const std::string& page_to_reload,
        const std::vector<std::string>& additional_head_elements);

    ~XgiOutputHeaderFooterHandler();

  private:
    RF2TTCControl* rf2ttc_control;
    xgi::Output& out_;
  };

// statics
public:

  /**
   * JavaScript code for loading the coloring of the operating modes table cells (for RF2TTC)
   * from the server, depending on the current setting in the RF2TTC hardware.
   */
  static std::string makeReloadOperatingModeSourcesCommand();

  static std::string getYuiIncludesForButtons();

// members
public:

  XDAQ_INSTANTIATOR();

  RF2TTCControl(xdaq::ApplicationStub* stub);

  virtual ~RF2TTCControl();

  virtual RF2TTCProxy& boardLockingProxy();

  virtual std::string softwareVersion();

private:

  // SOAP - application info space

  virtual void itemRetrieveAction(xdata::ItemRetrieveEvent& e);

  virtual void setDefaultValuesAction();


  // SOAP - FSM

  //! implements the configure action for the RF2TTC
  virtual void ConfigureAction(toolbox::Event::Reference event);


  // CGI

  //! default RF2TTC page
  void HTMLPageMain(xgi::Input* in, xgi::Output* out);

  //! Prints a page to configure the bunch clock paths.
  void HTMLPageBunchClockConfig(xgi::Input* in, xgi::Output* out);

  //! Prints a page to configure the orbit clock paths.
  void HTMLPageOrbitClockConfig(xgi::Input* in, xgi::Output* out);

  //! Prints a page to configure the automatic mode (depending on the LHC machine mode) settings.
  void HTMLPageAutomaticModeConfig(xgi::Input* in, xgi::Output* out);

  //! produces RF2TTC Resets page (page with buttons to reset various parts of RF2TTC HW)
  void HTMLPageResets(xgi::Input* in, xgi::Output* out);

  //! produces RF2TTC Registers page
  void HTMLPageRegisters(xgi::Input* in, xgi::Output* out);

  //! produces RF2TTC Summary page
  void HTMLPageSummary(xgi::Input* in, xgi::Output* out);

  //! callback on selection of new config file in RF2TTC Control page (radio button group)
  void HTMLPageCommandNewConfigFile(xgi::Input* in, xgi::Output* out);

  //! callback on 'Write current configuration TO file' button of RF2TTC Control page
  void HTMLPageCommandWriteConfigFile(xgi::Input* in, xgi::Output* out);

  //! This page is NOT intended to be viewed, just to be called from AJAX.
  void HttpCommand_SetDelay25(xgi::Input * in, xgi::Output * out);

  //! This page is NOT intended to be viewed, just to be called from AJAX.
  void HttpCommand_EnableDelay25(xgi::Input * in, xgi::Output * out);

  //! This can only be used for non-MAIN sources (i.e. not for BCMAIN and ORBIT_MAIN)
  void HttpCommand_SetSignalSourceExternal(xgi::Input * in, xgi::Output * out);

  //! This can only be used for non-MAIN sources (i.e. not for BCMAIN and ORBIT_MAIN)
  void HttpCommand_SetAutomaticWorkingMode(xgi::Input * in, xgi::Output * out);

  void HttpCommand_SetQPLLAutoLockMode(xgi::Input * in, xgi::Output * out);

  //! Set signal source for BCMain
  void HttpCommand_SetSignalSourceForMain(xgi::Input * in, xgi::Output * out);

  //! Configure the LHC machine modes (beam/nobeam settings depending on the LHC machine mode)
  void HttpCommand_ConfigureMachineMode(xgi::Input * in, xgi::Output * out);

  //! calls RFTTCControl::ResetsPage after performing reset (?)
  void HttpCommand_DoReset(xgi::Input * in, xgi::Output * out);

  /**
   * This is to get the information about the coloring of the operation modes.
   * This returns a javascript associative array of the 'html tag id' to 'background color' mapping.
   */
  void HttpCommand_GetOpModeColoring(xgi::Input * in, xgi::Output * out);

  //! Callback to set the orbit coarse delay.
  void HttpCommand_SetOrbitCoarseDelay(xgi::Input * in, xgi::Output * out);

  void HttpCommand_SetDAC(xgi::Input * in, xgi::Output * out);

  //! Returns a html string with the current error conditions.
  void HttpCommand_GetHardwareStatus(xgi::Input * in, xgi::Output * out);


  // utilities

  virtual void ErrorStatement(xgi::Output& out);

  /**
   * Performs some checks on the state of the hardware (e.g. QPLL locked etc.).
   * Returns an array of error messages.
   */
  ErrorMessages CheckHardwareErrorConditions();

  //! Fills the variable InputFileList.
  void GetFileList();


  // info space items

  //! The base url where YUI files should be taken from.
  xdata::String YuiBaseUrl_;

  std::map<RF2TTC::BCChannel, xdata::UnsignedInteger32> QPLLLocked_;

  std::map<RF2TTC::BCChannel, xdata::String> CurrentBCSource_;

  std::map<RF2TTC::OrbitChannel, xdata::String> CurrentOrbitSource_;


  std::map<std::string, RF2TTC::BCChannel> mapItemNameQPLLLockedToChannel_;

  std::map<std::string, RF2TTC::BCChannel> mapItemNameBCSourceToChannel_;

  std::map<std::string, RF2TTC::OrbitChannel> mapItemNameOrbitSourceToChannel_;


  //! The list of configuration files displayed on the main page.
  ttc::HTMLFieldElement InputFileList;

  ttc::HTMLFieldElement Trigselector;

  ttc::HTMLFieldElement SequenceSelector;

  //! the RF2TTC board proxy object
  ttc::RF2TTCProxy rf2ttcProxy_;

  //! the RF2TTC QPLLMonitoringListener
  ttc::RF2TTCQPLLMonitoringListener monQPLL_;

  //! the RF2TTC configuration monitoring listener
  ttc::RF2TTCConfigMonitoringListener monConfig_;

  //! the RF2TTC clock signal configuration monitoring listener
  ttc::RF2TTCClockConfigMonitoringListener monClockConfig_;

  //! the RF2TTC orbit signal configuration monitoring listener
  ttc::RF2TTCOrbitConfigMonitoringListener monOrbitConfig_;
};

}


#endif
