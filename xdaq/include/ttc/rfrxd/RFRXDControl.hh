#ifndef _ttc_rfrxd_RFRXDControl_hh_
#define _ttc_rfrxd_RFRXDControl_hh_


#include "ttc/utils/BoardLockingProxy.hh"
#include "ttc/utils/TTCXDAQBase.hh"

#include "ttc/rfrxd/RFRXD.hh"

#include "xdata/xdata.h"
#include "xdata/UnsignedInteger32.h"


namespace ttc
{

class RFRXDControl;

//! proxy class managing resources for talking to RFRXD
class RFRXDProxy : public BoardLockingProxy
{
public:
  BoardTempLocker<RFRXD> operator->();

protected:
  virtual RFRXD* createPtr(HAL::VMEBusAdapterInterface* busAdapter);
};


/**
 * This is the online software to configure and monitor the RFRXD.
 * NOTE:
 * The RFRXDControl spawns a paralel thread that keeps the time
 * and periodically asks the RFRXDControl to publish values to PSX.
 */

class RFRXDControl : public TTCXDAQBase
{

private:

  /**
   * The parallel thread, e.g. using for publishing the values periodically to PVSS.
   * This method is the main one run by the parallel thread created from the RFRXDControl.
   * It takes as argument a pointer to the RFRXDControl (cast to void*).
   * This method periodically pushes the RFRXDControl to publish some values to the PSX bridge.
   * As soon as the stop_thread_flag variable in the RFRXDControl gets set
   * (and the thread notices) it will terminate.
   */
  static void* ParallelThread(void *arg);

public:

  XDAQ_INSTANTIATOR();

  RFRXDControl(xdaq::ApplicationStub* stub);

  virtual ~RFRXDControl();

  virtual RFRXDProxy& boardLockingProxy();

  virtual std::string softwareVersion();

private:

  // SOAP - application info space

  virtual void itemRetrieveAction(xdata::ItemRetrieveEvent& e);

  virtual void setDefaultValuesAction();

  void checkItemChannelSignalName(size_t i);

  void checkItemChannelDACValue(size_t i);


  // SOAP - FSM

  virtual void ConfigureAction(toolbox::Event::Reference event);


  // CGI

  //! The RFRXD default Web Page.
  virtual void HTMLPageMain(xgi::Input* in, xgi::Output* out);

  //! callback method bound to the buttons on the HTML form that set new DAC Vref values in the RFRXD
  void HTMLPageCommandSetDACValue(xgi::Input* in, xgi::Output* out);


  // utilities

  /**
   * Produce an error message on 'out'.
   * The same code as the corresponding method in the class RF2TTC,
   * so should be merged into a base class.
   */
  virtual void ErrorStatement(xgi::Output& out);

  /**
   * Prints a table with the information read from the board
   * (printed on the main HTML page).
   */
  void PrintStatusTable(xgi::Output& out);

  /**
   * Creates (starts) the parallel thread
   * (which does e.g. periodically publish the values to the database).
   */
  void CreateParallelThread();

  /**
   * Function to publish the frequencies via PSX to PVSS.
   * This will be called from the periodic thread.
   */
  void PublishToPSX();

  //! To publish a single value to PSX.
  void PublishSingleValueToPSX(const std::string &varname, const std::string &value);


  // info space items

  /**
   * Type of the signals at the inputs (BC1, BC2, BCREF, ORBIT1, ORBIT2, or 'no value set').
   * This is needed to identify which channel corresponds to which signal
   * when checking the availability of signals when configuring the RF2TTC.
   */
  xdata::String ChannelSignalName_[3];

  //! The DAC Vref value for each channel
  xdata::UnsignedInteger ChannelDACValue_[3];

  /**
   * Variable names (of the PVSS datapoints) corresponding to each channel.
   * If empty, the corresponding frequency counter is NOT published to the PSX server.
   */
  xdata::String ChannelFrequencyDPName_[3];

  //! Signal presence for each channel.
  xdata::Boolean SignalPresentChannel_[3];

  //! Signal raw frequency counter for each channel.
  xdata::UnsignedInteger32 RawFrequencyCounterChannel_[3];

  //! Signal frequency for each channel.
  xdata::Double FrequencyChannel_[3];


  //! The thread spawned (e.g. for periodic updating of the BST time via VME)
  pthread_t thethread;

  /**
   * This flag must be read by any threads spawned from the
   * RFRXDControl. If this is true, they should terminate as soon as possible.
   */
  volatile bool stop_thread_flag;

  //! Time at which the periodic thread was run the last time.
  time_t last_periodic_thread_run;

  //! Time at which the periodic thread could sucesffully update the database.
  time_t last_periodic_thread_succesful_update;

  bool period_thread_initialized_;

  /**
   * Maps from the official signal name (BC1, BC2, BCREF, ORBIT1 or ORBIT2)
   * to the title which is displayed on the XDAQ page.
   * This mapping is hardwired into the software because it contains the
   * signal names of the AB/RF group and the labels on the TTC fibres.
   */
  std::map<std::string, std::string> official_signal_name_to_title;

  //! the RFRXD board proxy object
  ttc::RFRXDProxy rfrxdProxy_;
};

}


#endif
