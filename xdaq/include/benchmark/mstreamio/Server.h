// $Id: Server.h,v 1.2 2008/07/18 15:26:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _Server_h_
#define _Server_h_

#include <set>
#include "toolbox/mem/Reference.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "xdaq/Application.h"
#include "toolbox/PerformanceMeter.h"
#include "xdata/UnsignedLong.h"
#include "xdata/UnsignedInteger.h"
#include "xdata/Double.h"
#include "xdata/Boolean.h"
#include "xdata/Event.h"
#include "xdata/ActionListener.h"
#include "i2o/Method.h"

class Server:  public xdaq::Application, xdata::ActionListener
{	
	public:
		XDAQ_INSTANTIATOR();

		Server(xdaq::ApplicationStub* c) throw(xdaq::exception::Exception);

		// Interface function invoked for the I2O token message
		// that is received from the Client(s)
		//
		void token(  toolbox::mem::Reference * ref)  throw (i2o::exception::Exception);

		// External interface to start test  
		xoap::MessageReference start(xoap::MessageReference  message) throw (xoap::exception::Exception);

	protected:

		void checkMeasurements(int size);

		// Stop clients from sending I2O frames
		void stopClients();

		// Tell Clients to update the size of their I2O
		// token message by sending a ParameterSet:
		//  <properties xmlns:c="urn:xdaq-application:PeerTransportTCP" xsi:type="soapenc:Struct">
        	//                        <c:currentSize xsi:type="xsd:unsignedLong">xxx</poolName>
        	//   </properties>
		void nextSize(xdata::UnsignedLongT size);

		// Executed upon parameter set
		void actionPerformed (xdata::Event& e);

		// Start Clients by sending the command "start"
		//
		void activateClients();
	
	protected:
	
		xdata::UnsignedLong    counter_;     // counter for all received messages
		xdata::UnsignedInteger samples_;     // number of messages expected for one size measurement
		xdata::UnsignedLong    startSize_;   // start size of the messages
		xdata::UnsignedLong    currentSize_; // the size of the currently received token message
		xdata::UnsignedLong    endSize_;     // end size of the test
		xdata::UnsignedLong    step_;	     // the increment of the I2O token message
		xdata::Boolean	       stopped_;     // For checking if the server should count/discard incoming messages
		xdata::UnsignedLong    completed_;   // For checking if all last messages of a given size are received

		//
		//! perfromamce Meters
		//
		toolbox::PerformanceMeter * pmeter_;

		//
		//!current measurements
		//
		xdata::Double dataBw_;
		xdata::Double dataRate_;
		xdata::Double dataLatency_;
		std::set<xdaq::ApplicationDescriptor*> clients_; // remember clients descriptors
		
		toolbox::BSem mutex_;

};

#endif
