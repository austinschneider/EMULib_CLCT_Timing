// $Id: FEDEmulator.hh,v 1.2 2009/04/29 10:26:40 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors:  R. Arcidiacono, L. Orsini, C. Schwick			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _d2s_FEDEmulator_h_
#define _d2s_FEDEmulator_h_

#include <unistd.h>
#include <fstream>

// includes for XDAQ 3
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedShort.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"
//#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/WebApplication.h"
#include "toolbox/exception/Handler.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"
#include "toolbox/Event.h"
#include "toolbox/Runtime.h"
#include "xdaq/NamespaceURI.h"

#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/task/WaitingWorkLoop.h"
#include "toolbox/task/Action.h"

#include "xoap/Method.h"
#include "xdaq/NamespaceURI.h"
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPPart.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "d2s/fedemulator/FEDEmulatorCard.hh"


/**
*
*
*     @short Fed emulator based on a GIII.
*            This  class controls the  GIII which  emulates a  FED. It 
*            generates data  on an incoming external TTL  signal or on 
*            a software trigger. Event  properties for up to 2 Million
*            events can be stored in  a table. The Pseudo FED issues a
*            hardware  busy signal  if it  is not  able to  accept the 
*            incoming   trigger   rate.   (An  internal   counter   is 
*            incremented   on   an   incoming   trigger   signal   and 
*            decremented   for  every   generated   event.  The   most 
*            significant  bit of  this counter  (an 8-bit  counter) is 
*            the BUSY signal).
*            
*
*       @see 
*    @author Roberta Arcidiacono, Luciano Orsini, Christoph Schwick
*
**/

#include <stdint.h>

namespace d2s {

class FEDEmulator : public xdaq::WebApplication , xdata::ActionListener {
public:

  XDAQ_INSTANTIATOR();
  
  enum TriggerSouce { EXTERN, SOFTWARE, HARDWARELOOP }; 
  
  
  
  FEDEmulator(xdaq::ApplicationStub* stub) 
    throw (xdaq::exception::Exception);
  
  virtual ~FEDEmulator();
  
  /**
   * Retrieve counters' values from the hardware 
   * 
   */
  void Get_Counters()  
    throw(xcept::Exception);
  
  /**
   * Read counters when "RetrieveItem" action is performed 
   * 
   */
  void actionPerformed (xdata::Event& e);         
  
  
  /**
   * XDAQ state transition callback.
   * Creates address table and fedEmulatorCard.
   * Perform software Reset, sets event counter to 0x01.
   */
  void ConfigureAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  
  /**
   * XDAQ state transition callback.
   * Sets the event sizes in the hardware (fixed size if 
   * the eventSizeStdDev is 0, lognormal otherwise).
   * Sets the eventCounterOn and the start bit.
   */
  void EnableAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  /**
   * XDAQ state transition callback.
   * Called when running puts the FedEmulator in the 
   * state Configured (ready to start the next run)
   */
  void StopAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  
  /**
   * XDAQ state transition callback.
   * Resets the start bit in the hardware.
   */
  void SuspendAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  
  /**
   * XDAQ state transition callback.
   * Sets the start bit in the hardware.
   */
  void ResumeAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  /**
   * XDAQ state transition callback.
   * Resets the start bit in the hardware. 
   * Reads back the pending triggers and the event counter
   * in case someone is interested in the last values. 
   * Deletes the address table and the fedEmulatorCard.
   */
  void HaltAction(toolbox::Event::Reference e) 
    throw(toolbox::fsm::exception::Exception);
  
  
  void stateChanged(toolbox::fsm::FiniteStateMachine & fsm )  
    throw (toolbox::fsm::exception::Exception);
  
  void failedTransition(toolbox::Event::Reference e ) 
    throw (toolbox::fsm::exception::Exception);
  
  /**
   * HyperDAQ default WEB PAGE for the application
   * 
   */
  
  void defaultWebPage(xgi::Input *in, xgi::Output *out) 
    throw (xgi::exception::Exception);
  
  void setParameter(xgi::Input * in, xgi::Output * out ) 
    throw (xgi::exception::Exception);
  
  /**
   * Gives a manual trigger and generates one event.
   * Afterwards the trigger source is put back to the 
   * original value.
   */
  
  xoap::MessageReference UserTrigger ( xoap::MessageReference message ) 
    throw(xcept::Exception);

  /**
   * Write an item to a FEDEmulatorCard.
   * This function is intended for debugging only.
   */
  xoap::MessageReference writeItem( xoap::MessageReference message ) 
    throw(xcept::Exception, xoap::exception::Exception);

  /**
   * Read an item from a FEDEmulatorCard via SOAP.
   * This function is for debugging only.
   */
  xoap::MessageReference readItem( xoap::MessageReference message ) 
    throw(xcept::Exception, xoap::exception::Exception);

  /**
   * XDAQ callback.
   * If pendingTriggers or eventCounter are in the list
   * of the parameters to be read, they are retrieved from
   * the hardware.
   */
  
  xoap::MessageReference readpar ( xoap::MessageReference message )
    throw(xcept::Exception);

  xoap::MessageReference setWriteFile ( xoap::MessageReference message )
    throw(xcept::Exception);
  
  xoap::MessageReference setSTTSPattern( xoap::MessageReference msg ) 
    throw(xcept::Exception, xoap::exception::Exception);

  xoap::MessageReference cycleSTTSPatterns( xoap::MessageReference msg ) 
    throw(xcept::Exception, xoap::exception::Exception);

  xoap::MessageReference setSTTSControl( xoap::MessageReference msg ) 
    throw(xcept::Exception, xoap::exception::Exception);

private:
  
  Logger logger_;
  
  void webTableEntry( xgi::Output *out, const std::string name, const std::string value ) const;
  void webTableEntry( xgi::Output *out, const std::string name, const bool value ) const;
  void webTableEntry( xgi::Output *out, const std::string name, const uint32_t value ) const;

  xoap::MessageReference makeReply( std::string command, std::string answerString  );
  xoap::MessageReference makeFaultReply( std::string command, std::string answerString  );
  
  xoap::MessageReference changeState (xoap::MessageReference msg) 
    throw (xoap::exception::Exception);
  
  /**
   * Creates a SOAP response message for the specified FSM event and
   * result state.
   */
  xoap::MessageReference createFsmSoapResponseMsg ( const std::string event,
						    const std::string state)
    throw (xcept::Exception);
  
  HAL::PCIDevice::PCILocationIdentifier BusLoc_;
  HAL::PCILinuxBusAdapter *busAdapter_; // Made a pointer by Steve 04.10.05
  HAL::PCIAddressTable *addressTable_p;
  d2s::FEDEmulatorCard *fedEmulatorCard_p;
  bool fedEmulatorCardExists_;
  uint32_t writeFile_;
 
  // exported Properties of the application:
  // configuration parameters
  
  xdata::String eventFilePath_;
  xdata::String MonFile_;

  std::vector<std::string> expEventFile_;
  std::vector<std::string> expMonFile_;

  xdata::UnsignedInteger32 GIIIversion_;
  xdata::UnsignedInteger32 slot_;
  xdata::UnsignedInteger32 pciIndex_;
  xdata::Boolean           instantiateByIndex_;
  xdata::String            setupName_;
  
  xdata::UnsignedInteger32 triggerSource_;
  xdata::UnsignedInteger32 initialEventNumber_; //< initial setting of  
                                           //< eventCounter 
  xdata::UnsignedInteger32 eventSize_;
  xdata::UnsignedInteger32 deltaT_;
  xdata::UnsignedInteger32 FedSourceId_;
  xdata::UnsignedInteger32 eventTableRank_;
  xdata::UnsignedInteger32 eventSizeSeed_;
  xdata::UnsignedInteger32 eventSizeStdDev_;
  xdata::UnsignedInteger32 minEventSize_;
  xdata::UnsignedInteger32 maxEventSize_;
  
  xdata::UnsignedShort thresholdTTSReady_;
  xdata::UnsignedShort thresholdTTSBusy_;


  xdata::Boolean eventPreload_;

  // read-only variables
  xdata::String className_;
  xdata::UnsignedInteger32 instance_;
  xdata::String url_;
  
  xdata::String stateName_;
  xdata::UnsignedInteger32 pendingTriggers_; //< counts the triggers in the "trigger fifo"
  xdata::UnsignedInteger32 triggerNum_;    //< counts all generated events, 
                                        //< written to hardware in Enable()
  xdata::UnsignedInteger32 linkNotFull_;
  xdata::UnsignedInteger32 linkNotDown_;

  xdata::UnsignedInteger32 softSTTSEnable_;
  
  uint32_t setloop_;
  uint32_t softwareTriggerEnable_;
  
protected:
  // update parameter from web page 
  xdata::UnsignedInteger32 fragSizMean_;
  xdata::UnsignedInteger32 fragSizStdDev_;
  
  // the statemachine of the application:
  toolbox::fsm::FiniteStateMachine fsm_;
};

}

#endif 
