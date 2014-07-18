#ifndef _ttc_bobr_BOBRControl_hh_
#define _ttc_bobr_BOBRControl_hh_


#include "ttc/utils/TTCXDAQBase.hh"
#include "ttc/utils/BoardLockingProxy.hh"
#include "ttc/bobr/BOBR.hh"

#include "xdata/xdata.h"
#include "xdata/UnsignedInteger32.h"

namespace xgi
{
class Input;
class Output;
}


namespace ttc
{

class BOBRControl;

//! proxy class managing resources for talking to BOBR
class BOBRProxy : public BoardLockingProxy
{
public:
  BoardTempLocker<BOBR> operator->();

protected:
  virtual BOBR* createPtr(HAL::VMEBusAdapterInterface* busAdapter);
};


//! This is the online software to configure and monitor the BOBR.
class BOBRControl : public TTCXDAQBase
{

public:

  XDAQ_INSTANTIATOR();

  BOBRControl(xdaq::ApplicationStub* stub);

  virtual ~BOBRControl();

  virtual BOBRProxy& boardLockingProxy();

  virtual std::string softwareVersion();

private:

  // SOAP - application info space

  virtual void itemRetrieveAction(xdata::ItemRetrieveEvent& e);


  // CGI

  //! The BOBR default Web Page in XDAQ
  virtual void HTMLPageMain(xgi::Input* in, xgi::Output* out);

  //! page with the raw values
  void HTMLPageRawView(xgi::Input* in, xgi::Output* out);

  //! Form callback enabling the writing to the DP RAM.
  void HTMLPageEnableDPRAMWriting(xgi::Input* in, xgi::Output* out);


  // utilities

  virtual void ErrorStatement(xgi::Output& out);

  /**
   * Prints a table with the information read from the two BST
   * receiver mezzanine cards (printed on the main HTML page).
   * This is NOT the information received over the BST fibre.
   */
  void PrintReceiversStatusTable(
      xgi::Output& out,
      const std::string &this_page_url);

  /**
   * Prints a table with the information obtained from the BST
   * messages over the fibre.
   * This is NOT the information received over the BST fibre.
   */
  void PrintBSTMessagesTable(xgi::Output& out);

  /**
   * Prints a table with 'global' information about the module
   * (from block 0)
   */
  void PrintBlock0StatusTable(xgi::Output& out);

  //! prints a table with the raw data received
  void PrintRawTable(xgi::Output& out);


  // info space items

  //! beam momenta
  xdata::UnsignedInteger32 BeamMomentum_[2];

  //! turns since injection
  xdata::UnsignedInteger32 TurnsSinceInjection_[2];

  //! seconds since injection
  xdata::UnsignedInteger32 SecondsSinceInjection_[2];

  //! Beam mode (in numerical format)
  xdata::Integer BeamModeNumber_[2];

  //! Beam mode (textual description)
  xdata::String BeamMode_[2];

  //! beam intensity in units of 10e10 charges
  xdata::Integer BeamIntensity10e10_[2];

  //! particle types for each beam (number)
  xdata::Integer ParticleTypeNumber_[2];

  //! particle types for each beam (verbose text)
  xdata::String ParticleType_[2];

  //! LHC fill number
  xdata::Integer FillNumber_[2];


  //! the BOBR board proxy object
  ttc::BOBRProxy bobrProxy_;
};

}


#endif
