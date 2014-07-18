#ifndef GTPECONTROLLER_H
#define GTPECONTROLLER_H

/**
 *     @class GTPeController
 *
 *     @short XDAQ WebApplication controlling a GTPe (Global Trigger Processor Emulator)
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 08:02:38 $
 *
 *
 **/

#include "d2s/gtpecontroller/GTPeParameters.hh"

#include "xdaq/WebApplication.h"

#include "xdata/String.h"
#include "xdata/Double.h"
#include "xdata/UnsignedShort.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"

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

#include <stdint.h>

namespace d2s {

  // to control the hardware
  class GTPeWebInterface;
  class GTPeCrate;
  class GTPeMonitor;

  class GTPeController : public xdaq::WebApplication {

  public:
    XDAQ_INSTANTIATOR();
	
    GTPeController(xdaq::ApplicationStub * s) 
      throw (xdaq::exception::Exception);
    virtual ~GTPeController();
	

  private:
    /// clean up the object
    void cleanup();

    /// callback function to proccess a SOAP message to change to a different state
    xoap::MessageReference changeStateCommandHandler (xoap::MessageReference msg) 
      throw (xoap::exception::Exception);

    /// callback for state machine configure action
    ///
    /// resets and configures the GTPe using the current exported parameters
    void ConfigureAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine enable action
    ///
    /// enables the SLINK and Triggers, starts monitoring and workloop
    void EnableAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine stop action
    ///
    /// Stops the SLINK and trigger generation, counter monitor and workloop
    void StopAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine pause action
    ///
    /// pauses the GTPe
    void PauseAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine resume action
    ///
    /// resumes the GTPe
    void ResumeAction(toolbox::Event::Reference e) 
      throw(toolbox::fsm::exception::Exception);

    /// callback for state machine halt action
    ///
    /// Stops the SLINK and trigger generation, counter monitor and workloop
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

    GTPeParameters _config;
    xdata::UnsignedInteger32 _runNumber;

    GTPeCrate* _gtpecrate;
    GTPeMonitor* _gtpeM;
    GTPeMonitor* _gtpePartitionM;
    toolbox::fsm::FiniteStateMachine _fsm;
    GTPeWebInterface* _wi;

    /// the workloop 
    toolbox::task::WorkLoop* _wl;  
    toolbox::task::ActionSignature* _autoUpdateSignature;
    uint32_t _autoUpdateCount;

    // monitorables
    xdata::String _stateName;
    xdata::UnsignedShort _daqPartitionId; // the actual DAQPartition ID (differs from the one in config if autoDAQPartitionID is true)

    xdata::Double _totalTriggerRate;
    xdata::UnsignedInteger64 _totalTriggerNumber;

    xdata::Double _partitionTriggerRate;
    xdata::UnsignedInteger64 _partitionTriggerNumber;

    uint32_t _rateBitsBeforePause;
  };

}

#endif
