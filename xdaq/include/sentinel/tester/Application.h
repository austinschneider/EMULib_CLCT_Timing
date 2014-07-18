// $Id: Application.h,v 1.5 2008/12/02 15:41:20 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini and G. Lo Presti			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_tester_Application_h_
#define _sentinel_tester_Application_h_

#include <string>
#include <stack>
#include <set>
#include <map>
#include <list>

#include "xdaq/Application.h"
#include "xdaq/ApplicationContext.h"
#include "xoap/exception/Exception.h"
#include "xoap/MessageReference.h"

#include "xdata/ActionListener.h"
#include "xdata/String.h"
#include "xdata/UnsignedInteger32.h"

#include "xgi/Input.h"
#include "xgi/Output.h"
#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "toolbox/Properties.h"
#include "toolbox/ActionListener.h"
#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/task/WaitingWorkLoop.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/fsm/AsynchronousFiniteStateMachine.h"

#include "toolbox/BSem.h"

namespace sentinel
{
namespace tester
{
    class Application: public xdaq::Application, public toolbox::task::TimerListener
    {
	public:

	XDAQ_INSTANTIATOR();

	Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);

	~Application();

	//! Web interface
	//
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	//! Action listener interface implementation
	//
	void timeExpired(toolbox::task::TimerEvent& e);
	
	void onSubmit
	(
		xgi::Input * in,
		xgi::Output * out
	)
	throw (xgi::exception::Exception);

	void sendException ()
	throw (xgi::exception::Exception);
	
	void sendNews ()
	throw (xgi::exception::Exception);
	// FSM
	void autofire (toolbox::fsm::FiniteStateMachine & fsm) throw (toolbox::fsm::exception::Exception);
	void kickoff (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void reset (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);

	void soar (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void notification (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) ;
	void empty (toolbox::fsm::FiniteStateMachine & fsm) throw (toolbox::fsm::exception::Exception);
	void firealarm (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void revokealarm (toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);

	toolbox::fsm::AsynchronousFiniteStateMachine fsm_;
	toolbox::fsm::AsynchronousFiniteStateMachine fsm2_;
	toolbox::fsm::AsynchronousFiniteStateMachine fsm3_;

    };
	
		
}
}
#endif
