// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_InvalidInputEvent_h_
#define _toolbox_InvalidInputEvent_h_

#include "toolbox/Event.h"
#include "toolbox/fsm/FiniteStateMachine.h"

namespace toolbox {
namespace fsm {

class InvalidInputEvent: public toolbox::Event
{
	public:
	
	InvalidInputEvent(toolbox::fsm::State fromState, const std::string & input, void* originator = 0);
	
	//! Retrieve the state from which the failing transition originated
	//
	toolbox::fsm::State getFromState();
	
	//! Retrieve the state to which the failing transition originally should have gone
	//
	std::string getInput();
	
	protected:
	
		toolbox::fsm::State fromState_;
		std::string input_;
};

}
}

#endif
