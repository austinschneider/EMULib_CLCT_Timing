// $Id: Application.h,v 1.3 2008/07/18 15:28:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini and G. Lo Presti			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_tester_Application_h_
#define _xmas_tester_Application_h_

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


#include "toolbox/BSem.h"

namespace xmas
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


	protected:

	std::list<std::string> monitorables_;
    };
}
}
#endif
