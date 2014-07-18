#ifndef FMMCONTROLLER_H
#define FMMCONTROLLER_H

/**
 *     @class FMMController
 *
 *     @short XDAQ WebApplication controlling a crate of FMMs
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.4 $
 *     $Date: 2007/12/18 16:25:29 $
 *
 *
 **/

#include "tts/fmmcontroller/FMMParameters.hh"

#include "xdaq/WebApplication.h"

// to repesent data as XDATA
#include "xdata/Vector.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"

// for SOAP messaging
#include "xoap/MessageReference.h"

// state machine
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/Event.h"
#include "toolbox/fsm/exception/Exception.h"

// work loop
#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/task/PollingWorkLoop.h"
#include "toolbox/task/Action.h"


#include <map>
#include <stdint.h>

namespace tts {

  class FMMDeadTimeMonitor;
  class FMMCrate;
  class FMMMonitor;
  class FMMWebInterface;
  class FMMInterconnectionTestHandler;
  class FMMHistoryMonitor;
  class FMMHistoryLogger;
  class FMMSpecialStateLogger;
  class FMMTransitionAnalyzer;

  class FMMController : public xdaq::WebApplication {

  public:
    XDAQ_INSTANTIATOR();
	
    FMMController(xdaq::ApplicationStub * s) 
      throw (xdaq::exception::Exception);
    virtual ~FMMController();
	

  private:
    /// callback function to proccess a SOAP message to change to a different state
    xoap::MessageReference changeStateCommandHandler (xoap::MessageReference msg) 
      throw (xoap::exception::Exception);

    /// find a mask in the mask string passed by Run Control
    uint32_t findMask(std::string maskstr, uint32_t geoslot) 
      throw ( toolbox::fsm::exception::Exception);

    /// callback for state machine configure action
    ///
    /// configures the FMM using the current exported parameters
    void ConfigureAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine enable action
    ///
    /// resets the dead time counters of the FMM
    void EnableAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine disable action
    ///
    /// 
    void DisableAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine halt action
    ///
    /// does nothing special ...
    void HaltAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine transition to failed state
    ///
    /// this function logs the exception to the logger
    void transitionToFailed(toolbox::Event::Reference e ) 
      throw (toolbox::fsm::exception::Exception);

    /// callback when a new state is entered
    /// 
    void stateChanged(toolbox::fsm::FiniteStateMachine & fsm )
      throw (toolbox::fsm::exception::Exception);

    /// display the default web page
    void displayDefaultWebPage(xgi::Input * in, xgi::Output * out ) 
      throw (xgi::exception::Exception);

    /// action to be called in workloop
    bool autoUpdateAction(toolbox::task::WorkLoop* wl);

    /// action to be called in workloop
    bool monitorHistoryAction(toolbox::task::WorkLoop* wl);

    /// callback function to process SOAP message for interconnection test
    xoap::MessageReference readInputStates(xoap::MessageReference msg)   
      throw (xoap::exception::Exception);

    /// callback function to process SOAP message for interconnection test
    xoap::MessageReference resetHistory(xoap::MessageReference msg)   
      throw (xoap::exception::Exception);

    /// callback function to process SOAP message for interconnection test
    xoap::MessageReference checkInputSequence(xoap::MessageReference msg)   
      throw (xoap::exception::Exception);


  private:
    xdata::Vector<xdata::Bag<tts::FMMParameters> > _config;
    xdata::UnsignedInteger32 _runNumber;
    xdata::Boolean _useTriggerDistributor;
    xdata::Boolean _logHistoryToFile;
    xdata::UnsignedInteger32 _logFileSizeLimitBytes;
    xdata::String _logFileNameBase;
    xdata::String _specialStateLogFileNameBase;
    xdata::String _maskString;
    xdata::UnsignedInteger32 _monitorForcePushIntervalSeconds;
    xdata::UnsignedInteger32 _histoyMonitorSleepMilliSeconds;
    xdata::Boolean _enableLogRotation;

    tts::FMMCrate* _fmmcrate;
    toolbox::fsm::FiniteStateMachine _fsm;
    tts::FMMWebInterface* _wi;
    tts::FMMInterconnectionTestHandler* _ictHandler;

    /// the workloop for dead time monitoring
    toolbox::task::WorkLoop* _wl;  
    toolbox::task::ActionSignature* _autoUpdateSignature;
    uint32_t _autoUpdateCount;
    uint32_t _monitorUpdateCount;

    /// the workloop for history memory readout
    toolbox::task::WorkLoop* _wl_hmon;  
    toolbox::task::ActionSignature* _monitorHistorySignature;

    std::map<std::string, tts::FMMDeadTimeMonitor*> _dtmons;
    std::map<std::string, tts::FMMHistoryMonitor*> _hmons;
    std::map<std::string, tts::FMMHistoryLogger*> _hloggers;
    std::map<std::string, tts::FMMSpecialStateLogger*> _ssloggers;
    std::map<std::string, tts::FMMTransitionAnalyzer*> _fmmtas;
    std::map<std::string, tts::FMMMonitor*> _mons;

    // monitorables
    xdata::String _stateName;
  };

}
#endif
