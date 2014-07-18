// $Id: FailedEvent.h,v 1.4 2008/07/18 15:27:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_FailedEvent_h_
#define _toolbox_FailedEvent_h_

#include "toolbox/Event.h"
#include "toolbox/fsm/FiniteStateMachine.h"

namespace toolbox {
namespace fsm {

class FailedEvent: public toolbox::Event
{
	public:
	
	FailedEvent(xcept::Exception& ex, 
			toolbox::fsm::State fromState, 
			toolbox::fsm::State toState,
			const std::string & type, void* originator = 0);
	
	//! Retrieve a reference to the exception that caused the transition to "failed" ('F') state
	//
	xcept::Exception& getException();
	
	//! Retrieve the state from which the failing transition originated
	//
	toolbox::fsm::State getFromState();
	
	//! Retrieve the state to which the failing transition originally should have gone
	//
	toolbox::fsm::State getToState();
	
	protected:
	
		xcept::Exception ex_;
		toolbox::fsm::State fromState_;
		toolbox::fsm::State toState_;
};

}
}

#endif
