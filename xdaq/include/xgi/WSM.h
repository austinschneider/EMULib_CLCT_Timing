#ifndef _xgi_WSM_h_
#define _xgi_WSM_h_

#include <iostream>
#include <string>
#include <map>
#include <string>
#include <vector>
#include <set>


#include "xgi/Input.h"
#include "xgi/Output.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "xgi/exception/Exception.h"
#include <string>
#include "xgi/Input.h"
#include "xgi/Output.h"


namespace xgi
{




class WSM
{
	public:
		
	typedef char State;
	typedef std::string Input;
	

	WSM();
	~WSM();
	
	template <class OBJECT>
	void addState(State s, const std::string & name, OBJECT * obj , void (OBJECT::*page)(xgi::Output *)) throw (xgi::exception::Exception)
	{
		if ( states_.find(s) == states_.end() )
		{
			states_[s] = name;
			pages_[s] = new Page<OBJECT>(obj,page);
		}
		else
		{
			std::string msg = "State: ";
			msg += s;
			msg += "named: ";
			msg += states_[s];
			msg += " already existing";
			XCEPT_RAISE (xgi::exception::Exception, msg); 

		}
	}

	void setInitialState(State s);

	std::string getStateName(State s) throw (xgi::exception::Exception);
	std::vector<State> getStates();
	std::set<Input> getInputs(State s);
	std::set<Input> getInputs();
	
	State getCurrentState();


	template <class OBJECT>
	void addStateTransition(State from, State to, Input i, OBJECT * obj , void (OBJECT::*func)(xgi::Input *) , void	(OBJECT::*failure)(xgi::Output *, xgi::exception::Exception & )) throw (xgi::exception::Exception)
	{
		if (states_.find(from) == states_.end()) 
		{
			std::string msg = "'From' state: ";
			msg += from;
			msg += "undeclared ";
			XCEPT_RAISE (xgi::exception::Exception, msg); 
		}	

		if (states_.find(to) == states_.end()) 
		{
			std::string msg = "'To' state: ";
			msg += to;
			msg += "undeclared ";
			XCEPT_RAISE (xgi::exception::Exception, msg); 
		}	

		inputs_.insert(i);
		stateTransitionTable_[from][i] = to;
		actionTable_[from][i] = new Action<OBJECT>(obj,func);
		failures_[i] = new Failure<OBJECT>(obj,failure);
	}

	void displayPage(xgi::Output* out);
	
	
	void addStateTransition(State from, State to, Input i) throw (xgi::exception::Exception);


	void fireEvent(const Input & i, xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

	protected:

	class ActionSignature
	{
		public:
		virtual ~ActionSignature()
		{
		}

		virtual void invoke(xgi::Input * i) = 0;

	};

	template <class OBJECT>
	struct Action: public ActionSignature
	{
		public:
		virtual ~Action()
		{
		}

		Action(OBJECT * object, void (OBJECT::*func)(xgi::Input * i) ): obj_(object), func_(func)
		{
		}

		void invoke(xgi::Input * i) 
		{
			if ( func_ != 0 ) {
				(obj_->*func_)(i);
			}	
		}


		OBJECT * obj_;
		void (OBJECT::*func_)(xgi::Input * i);
	};


	class PageSignature
	{
		public:
		virtual ~PageSignature()
		{
		}

		virtual void invoke(xgi::Output *) = 0;

	};

	template <class OBJECT>
	struct Page: public PageSignature
	{
		public:

		Page(OBJECT * object, void (OBJECT::*func)(xgi::Output *) ): obj_(object), func_(func)
		{
		}

		virtual ~Page()
		{
		}

		void invoke(xgi::Output * o) 
		{
			if ( func_ != 0 ) {
				(obj_->*func_)(o);
			}	
		}


		OBJECT * obj_;
		void (OBJECT::*func_)(xgi::Output *);
	};

	class FailureSignature
	{
		public:
		virtual ~FailureSignature()
		{
		}

		virtual void invoke(xgi::Output *, xgi::exception::Exception & e) = 0;

	};

	template <class OBJECT>
	struct Failure: public FailureSignature
	{
		public:
		virtual ~Failure()
		{
		}

		Failure(OBJECT * object, void (OBJECT::*func)(xgi::Output *, xgi::exception::Exception & e) ): obj_(object), func_(func)
		{
		}

		void invoke(xgi::Output * o,  xgi::exception::Exception & e) 
		{
			if ( func_ != 0 ) {
				(obj_->*func_)(o,e);
			}	
		}


		OBJECT * obj_;
		void (OBJECT::*func_)(xgi::Output *, xgi::exception::Exception & e);
	};
	


	protected:

	State currentState_;
	std::map< State, std::map<Input, State, std::less<Input> >, std::less<State> > stateTransitionTable_;
	std::map< State, std::map<Input, ActionSignature*, std::less<Input> >, std::less<State> > actionTable_;

	std::map< State, std::string, std::less<State> > states_;
	std::map< State, PageSignature*, std::less<State> > pages_;
	std::set<std::string> inputs_;
	std::map<Input, FailureSignature *, std::less<Input> > failures_; 

		
};

}

#endif
