// $Id: PeerTransportATCP.h,v 1.4 2009/04/29 10:33:01 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _PeerTransportATCP_h_
#define _PeerTransportATCP_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include "pt/atcp/Address.h"
#include "xdaq/WebApplication.h"
#include "pt/atcp/PeerTransportSender.h"
#include "pt/atcp/PeerTransportReceiver.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/Double.h"
#include "xdata/UnsignedInteger32.h"
#include "pt/atcp/Constants.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"

#include "xgi/WSM.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//! this is the XDAQ Peer Transport Appliction Wrapper
//
namespace pt
{

namespace atcp
{

class PeerTransportATCP: public xdaq::WebApplication,  xdata::ActionListener
{
	public:
	
	XDAQ_INSTANTIATOR();
	
	PeerTransportATCP(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
	~PeerTransportATCP();
	
	//xoap::MessageReference fireEvent (xoap::MessageReference msg) throw (xoap::exception::Exception);

	void ConfigureAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void EnableAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void HaltAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void FailAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);

	
	// Web callback functions
	/* AP 17/05/2011
	void Configure(xgi::Input * in ) throw (xgi::exception::Exception);
	void Enable(xgi::Input * in ) throw (xgi::exception::Exception);
	void Halt(xgi::Input * in ) throw (xgi::exception::Exception);
	void Fail(xgi::Input * in ) throw (xgi::exception::Exception);
	*/
	// void stateMachinePage( xgi::Output * out ) throw (xgi::exception::Exception);
	void failurePage(xgi::Output * out, xgi::exception::Exception & e)  throw (xgi::exception::Exception);


    /**
     * Callback invoked when the state machine of the application has changed.
     */
    void stateChanged(toolbox::fsm::FiniteStateMachine & fsm)
    throw (toolbox::fsm::exception::Exception);

	
	private:
	
	pt::atcp::PeerTransportSender* pts_;
	pt::atcp::PeerTransportReceiver* ptr_;

	xdata::Boolean autosize_;
	xdata::UnsignedInteger32 maxPacketSize_;
	xdata::String poolName_;

	xdata::Boolean tcpNodelay_; //ADDEDATCP
	xdata::Boolean blockingSend_; //ADDEDATCP
	xdata::Boolean blockingReceive_; //ADDEDATCP
	xdata::Boolean writesetRare_; //ADDEDATCP
	xdata::UnsignedInteger32 maxWritePerSelect_; //ADDEDATCP
	xdata::UnsignedInteger32 maxReadPerSelect_; //ADDEDATCP
	xdata::Boolean connectAtFirstSend_; //ADDEDATCP
	xdata::Boolean syncronousSend_; //ADDEDATCP

	xdata::String stateName_;
	xdata::UnsignedInteger32 queueSize_;


	//new 26/1/06
	xdata::Boolean nonBlockingConnection_;
	xdata::Boolean noTimeoutSend_;
	xdata::UnsignedInteger32 timeoutSendSec_;
	xdata::UnsignedInteger32 timeoutSendUsec_;
	xdata::Boolean noTimeoutRecv_;
	xdata::UnsignedInteger32 timeoutRecvSec_;
	xdata::UnsignedInteger32 timeoutRecvUsec_;

	// new 23/09/2009
	xdata::UnsignedInteger32 nTriesToConnect_;

	// new 6/04/2010
	xdata::Boolean tryToReconnect_;
	xdata::UnsignedInteger32 nTriesToReconnect_;
	xdata::UnsignedInteger32 nTriesToCheckReconnect_;
	
	// new 30/06/2011
	xdata::Boolean socketReuseAddr_;

	toolbox::fsm::FiniteStateMachine fsm_; // state machine for general control
	xgi::WSM wsm_; // state machine for web page dialog

	
	xdata::Boolean useCommittedHeapAllocator_;
	xdata::Double committedPoolSize_;
	xdata::Double lowThreshold_;
	xdata::Double highThreshold_;

	
	//Added for the new HyperDAQ interface (from v 1.12.0)

	/**
	 * The application's URN.
	 */
	std::string urn_;

	/**
	 * The XML class name of the application.
	 */
	std::string xmlClass_;

	/**
	 * The instance number of the application.
	 */
	unsigned int instance_;

	/**
	 * Binds the XGI callback methods.
	 */
	void bindXgiCallbacks() throw (xdaq::exception::Exception);

	/**
	 * Creates the CSS file for this application.
	 */
	void css(xgi::Input *in, xgi::Output *out)
			throw (xgi::exception::Exception);

	/**
	 * Displays the default web page of the application.
	 */
	void defaultWebPage(xgi::Input *in, xgi::Output *out)
			throw (xgi::exception::Exception);

	/**
	 * Displays the developer's web page used for debugging.
	 */
	void debugWebPage(xgi::Input *in, xgi::Output *out)
			throw (xgi::exception::Exception);

	/**
	 * Displays the developer's web page used for FSM.
	 */
	void fsmWebPage(xgi::Input *in, xgi::Output *out)
	                throw (xgi::exception::Exception);

	/**
	 * Binary semaphore used to protect the internal data structures of the
	 * application from multithreaded access.
	 */
	toolbox::BSem applicationBSem_;

	/**
	 * Processes the form sent from the finite state machine web page.
	 */
	void processFsmForm(xgi::Input *in) throw (xgi::exception::Exception);

	/**
	 * Callback responsible for processing FSM events received via
	 * SOAP messages.
	 */
	xoap::MessageReference processSoapFsmEvent(xoap::MessageReference msg)
			throw (xoap::exception::Exception);

	/**
	 * Returns the finite state machine event represented by the specified soap      * message.
	 */
	std::string extractFsmEventFromSoapMsg(xoap::MessageReference msg)
			throw (pt::atcp::exception::Exception);

	/**
	 * Creates a SOAP response message for the specified FSM event and result
	 * state.
	 */
	xoap::MessageReference createFsmSoapResponseMsg(const std::string event,
			const std::string state) throw (xoap::exception::Exception);

	/**
	 * The application's standard monitoring parameters.
	 */
	std::vector< std::pair<std::string, xdata::Serializable *> >
			stdConfigParams_;

	/**
	 * Initialises and returns the application's debug (private to developer)
	 * monitoring parameters.
	 */
	std::vector< std::pair<std::string, xdata::Serializable*> >
			initStdConfigParams() throw (xcept::Exception);
	
	void actionPerformed (xdata::Event& e) ;    
};

}
}
#endif
