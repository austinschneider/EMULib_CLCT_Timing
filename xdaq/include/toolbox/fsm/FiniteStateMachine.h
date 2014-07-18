#ifndef _toolbox_fsm_FiniteStateMachine_h_
#define _toolbox_fsm_FiniteStateMachine_h_ 

#include <map>
#include <string>
#include <vector>
#include <set>

#include "toolbox/fsm/exception/Exception.h"
#include "toolbox/Event.h"

namespace toolbox {
namespace fsm {

typedef char State;

class FiniteStateMachine 
{
	public:
	
	FiniteStateMachine();	
	
	~FiniteStateMachine();
	
	void addState(State s, const std::string & name ) throw (toolbox::fsm::exception::Exception);
	
	template <class OBJECT>
	void addState(State s, 
			const std::string & name, 
			OBJECT * obj,  
			void (OBJECT::*stateChanged)(toolbox::fsm::FiniteStateMachine &) )
		 throw (toolbox::fsm::exception::Exception)
	{
		if ( states_.find(s) == states_.end() )
		{
			states_[s] = name;
			stateChangedTable_[s] = new StateChanged<OBJECT>(obj,stateChanged);
		}
		else
		{
			std::string msg = "State: ";
			msg += s;
			msg += "named: ";
			msg += states_[s];
			msg += " already existing";
			XCEPT_RAISE (toolbox::fsm::exception::Exception, msg); 

		}
	}
	
	//! Sets the initial state without triggering any action
	//
	void setInitialState(State s) throw (toolbox::fsm::exception::Exception);
	
	//! Gets the initial 
	//
	State getInitialState() throw (toolbox::fsm::exception::Exception);
	
	
	//! Puts the state machine into the initial state (set with setInitialState) without triggering any action
	//
	void reset() throw (toolbox::fsm::exception::Exception);
	
	std::string getStateName(State s) throw (toolbox::fsm::exception::Exception);
	
	void setStateName(State s, const std::string & name) throw (toolbox::fsm::exception::Exception);
	
	std::vector<State> getStates();
		
	std::set<std::string> getInputs(State s);	
	
	std::set<std::string> getInputs();
	
	//! return the possible transitions for all inputs from a given state
	std::map<std::string, State, std::less<std::string> > getTransitions(State s) throw (toolbox::fsm::exception::Exception);
	
	State getCurrentState();

	template <class OBJECT>
	void setFailedStateTransitionAction(OBJECT * obj, 
				void (OBJECT::*func)(toolbox::Event::Reference) ) 
		throw (toolbox::fsm::exception::Exception)
	{
		actionTable_['*']["fail"] = new Action<OBJECT>(obj,func);
	}

	
	
	template <class OBJECT>
	void setFailedStateTransitionChanged(OBJECT * obj, 
				void (OBJECT::*stateChanged)(toolbox::fsm::FiniteStateMachine &) ) 
		throw (toolbox::fsm::exception::Exception)
	{
		stateChangedTable_['F'] = new StateChanged<OBJECT>(obj,stateChanged);
	}
	
	template <class OBJECT>
	void addStateTransition(State from, 
				State to, 
				const std::string& input, 
				OBJECT * obj, 
				void (OBJECT::*func)(toolbox::Event::Reference) ) 
		throw (toolbox::fsm::exception::Exception)
	{
		if (states_.find(from) == states_.end()) 
		{
			std::string msg = "'From' state: ";
			msg += from;
			msg += "undeclared ";
			XCEPT_RAISE (toolbox::fsm::exception::Exception, msg); 
		}	
		
		if (states_.find(from) == states_.end()) 
		{
			std::string msg = "'To' state: ";
			msg += to;
			msg += "undeclared ";
			XCEPT_RAISE (toolbox::fsm::exception::Exception, msg); 
		}	
		
		inputs_.insert(input);
		stateTransitionTable_[from][input] = to;
		actionTable_[from][input] = new Action<OBJECT>(obj,func);
	}
	
	void addStateTransition(State from, State to, const std::string& input) 
		throw (toolbox::fsm::exception::Exception);
	
	//! fire an Event that contains the Input (a string) for the transition to be fired
	//
	void fireEvent(toolbox::Event::Reference e) 
		throw (toolbox::fsm::exception::Exception);

	protected:
	
	class ActionSignature
	{
		public:

		virtual ~ActionSignature()
		{
		}

		virtual void invoke(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception) = 0;
	
	};
	
	template <class OBJECT>
	struct Action: public ActionSignature
	{
		public:
		
		Action(OBJECT * object, void (OBJECT::*func)(toolbox::Event::Reference) ): obj_(object), func_(func)
		{
		}

		virtual ~Action()
		{
		}

		void invoke(toolbox::Event::Reference e)  throw (toolbox::fsm::exception::Exception)
		{
			if ( func_ != 0 ) {
				(obj_->*func_)(e);
			}	
		}


		OBJECT * obj_;
		void (OBJECT::*func_)(toolbox::Event::Reference);
	};


	class StateChangedSignature
	{
		public:
		virtual ~StateChangedSignature()
		{
		}

		virtual void invoke(toolbox::fsm::FiniteStateMachine & fsm) throw (toolbox::fsm::exception::Exception) = 0;
	
	};
	
	template <class OBJECT>
	struct StateChanged: public StateChangedSignature
	{
		public:
		
		StateChanged(OBJECT * object, void (OBJECT::*func)(toolbox::fsm::FiniteStateMachine&) ): obj_(object), func_(func)
		{
		}

		virtual ~StateChanged()
		{
		}

		void invoke(toolbox::fsm::FiniteStateMachine & fsm)  throw (toolbox::fsm::exception::Exception)
		{
			if ( func_ != 0 ) {
				(obj_->*func_)(fsm);
			}	
		}


		OBJECT * obj_;
		void (OBJECT::*func_)(toolbox::fsm::FiniteStateMachine & );
	};

	
	
	protected:
	
	State currentState_;
	State initialState_;
	std::map< State, std::map<std::string, State, std::less<std::string> >, std::less<State> > stateTransitionTable_;
	std::map< State, std::map<std::string, ActionSignature*, std::less<std::string> >, std::less<State> > actionTable_;
	
	std::map< State, std::string, std::less<State> > states_;
	std::set<std::string> inputs_;
	
	std::map< State, StateChangedSignature*, std::less<State> > stateChangedTable_;


};

}}

#endif
