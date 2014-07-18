// $Id: AsynchronousFiniteStateMachine.h,v 1.3 2008/07/18 15:27:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
#ifndef _toolbox_fsm_AsynchronousFiniteStateMachine_h_
#define _toolbox_fsm_AsynchronousFiniteStateMachine_h_ 

#include <map>
#include <string>
#include <vector>
#include <set>

#include "toolbox/task/Action.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/exception/Exception.h"
#include "toolbox/Event.h"
#include "toolbox/rlist.h"
#include "toolbox/lang/Class.h"

namespace toolbox {
namespace fsm {

class AsynchronousFiniteStateMachine: public toolbox::fsm::FiniteStateMachine, public toolbox::lang::Class
{
	public:
	
	AsynchronousFiniteStateMachine(const std::string& workLoopName);	
	
	virtual ~AsynchronousFiniteStateMachine();
	
	
	//! Puts the state machine into the initial state (set with setInitialState) without triggering any action
	//
	void reset() throw (toolbox::fsm::exception::Exception);
	
		
	//! fire an Event that contains the Input (a string) for the transition to be fired
	//
	void fireEvent(toolbox::Event::Reference e) 
		throw (toolbox::fsm::exception::Exception);

	template <class OBJECT>
	void setInvalidInputStateTransitionAction(OBJECT * obj, 
				void (OBJECT::*func)(toolbox::Event::Reference) ) 
		throw (toolbox::fsm::exception::Exception)
	{
		invalidInputAction_ = new Action<OBJECT>(obj,func);
	}
	protected:
	
	bool processTransition(toolbox::task::WorkLoop* wl);

	toolbox::task::ActionSignature* processTransitionJob_;
	toolbox::task::WorkLoop* workLoop_;
	toolbox::rlist<toolbox::Event::Reference*> eventQueue_;
	BSem eventQueueLock_; // protects multiple event producers pushing into eventQueue
	BSem stateMachineLock_; // protects the execution of jobs against an asynchronous reset command
	ActionSignature* invalidInputAction_;
};

}}

#endif
