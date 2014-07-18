// $Id: Application.h,v 1.6 2008/07/18 15:26:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini and G. Lo Presti			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_eventing_Application_h_
#define _b2in_eventing_Application_h_

#include <string>
#include <stack>
#include <set>
#include <map>
#include <list>

#include "xdaq/Application.h"

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
#include "pt/Messenger.h"
#include "b2in/nub/Messenger.h"
#include "b2in/nub/Method.h"

#include "b2in/eventing/Statistics.h"
#include "b2in/eventing/HyperDAQ.h"
#include "b2in/eventing/Subscription.h"
#include "b2in/eventing/Diagnostics.h"
#include "b2in/utils/MessengerCacheListener.h"
#include "b2in/utils/MessengerCache.h"

namespace b2in
{
	namespace eventing
	{
		class Application: public xdaq::Application, public toolbox::task::TimerListener, public b2in::utils::MessengerCacheListener, public toolbox::ActionListener
		{
		public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);

			~Application();

			//! Web interface
			//
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void diagnostics(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

			//! Action listener interface implementation
			//
			void timeExpired(toolbox::task::TimerEvent& e);
			void asynchronousExceptionNotification(xcept::Exception& e);
			void actionPerformed(toolbox::Event& e);

			void onMessage (toolbox::mem::Reference *  msg, xdata::Properties & plist) 
				throw (b2in::nub::exception::Exception);

		protected:

			void subscribe(xdata::Properties & plist) throw (b2in::nub::exception::Exception);

			void notify(toolbox::mem::Reference *  msg, xdata::Properties & plist) throw (b2in::nub::exception::Exception);

			std::map<std::string, std::list<Subscription*> > subscriptions_;

			std::map<std::string, pt::Messenger::Reference > messengers_;

			toolbox::BSem mutex_;
			Statistics * statistics_;
			HyperDAQ * hyperdaq_;
			b2in::utils::MessengerCache* messengerCache_;

			b2in::eventing::Diagnostics diagnostics_;
			xdata::UnsignedInteger64T communicationLoss_;
		};
	}
}

#endif

