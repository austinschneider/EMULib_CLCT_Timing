// $Id: Application.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_Application_h_
#define _statepanel_Application_h_

#include <string>
#include <map>

#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdata/UnsignedInteger64.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"
#include "xdata/UnsignedInteger32.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"

#include "toolbox/ActionListener.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

#include "state/panel/Repository.h"

namespace state
{
namespace panel 
{
	class Application :public xdaq::Application, 
		public toolbox::ActionListener,
		public xdata::ActionListener
	{
		public:

		XDAQ_INSTANTIATOR();

		Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
		~Application();

		void actionPerformed ( xdata::Event& e );
		
		void actionPerformed ( toolbox::Event & e);

		//
		// XGI Interface
		//
		void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
		
		void TabPanel(xgi::Output * out );
		void PanelTabPage(xgi::Output * out );
		
		void catalog(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

		void retrieve(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

		void action(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

		//
		// SOAP interface
		//
		xoap::MessageReference notify(xoap::MessageReference msg) throw	(xoap::exception::Exception);
		
		private:

		toolbox::task::AsynchronousEventDispatcher dispatcher_;
		xdata::UnsignedInteger32 lostCounter_;
		state::panel::Repository repository_;
	};
}
}
#endif

