// $Id: Client.h,v 1.2 2008/07/18 15:26:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _Client_h_
#define _Client_h_

#include <set>
#include "toolbox/Task.h"
#include "toolbox/mem/Reference.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "xdaq/Application.h"
#include "xdata/UnsignedLong.h"
#include "xdata/Event.h"
#include "xdata/ActionListener.h"

class Client: public xdaq::Application, public toolbox::Task, public xdata::ActionListener
{	
	public:
		XDAQ_INSTANTIATOR();

		Client(xdaq::ApplicationStub* c) throw(xdaq::exception::Exception);

		// start sending of token frame to all servers
		xoap::MessageReference start(xoap::MessageReference  message) throw (xoap::exception::Exception);

		// stop client from sending token frames to server
		xoap::MessageReference stop(xoap::MessageReference  message) throw (xoap::exception::Exception);

	protected:
	
		// Send an I2O token message to all servers, If last is 1, the flag 'last' in the
		// message is set to one. Otherwise it is set to 0
		//
		int sendMessage(unsigned int last);

		// service routine for sending
		int svc();

		//
		// used to create the memory pool upon parametrization
		//	
		void actionPerformed (xdata::Event& e);
	
	protected:

		xdata::UnsignedLong counter_; 			// counts all outgoing I2O messages
		xdata::UnsignedLong currentSize_;		// The size of the current I2O token message
		xdata::UnsignedLong completed_;			// Number of Disable messages received from servers
		xdata::UnsignedLong starting_;         		// Number of Enable messages received from servers
		xdata::UnsignedLong maxFrameSize_;		// The maximum frame size to be allocated by the Client       
		std::set<xdaq::ApplicationDescriptor*> destination_;	// Vector of all server tids
		xdata::UnsignedLong committedPoolSize_;		// Total memory for messages
		xdata::UnsignedLong highMemoryWatermark_;	// Application should not use more bytes than specified here
		toolbox::mem::Pool* pool_;			// Memory pool for allocating messages for sending
		toolbox::fsm::FiniteStateMachine fsm_;
};

#endif
