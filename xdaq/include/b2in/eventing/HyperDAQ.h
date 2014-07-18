// $Id: HyperDAQ.h,v 1.3 2008/07/18 15:26:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini and G. Lo Presti			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_eventing_HyperDAQ_h_
#define _b2in_eventing_HyperDAQ_h_

#include <string>
#include <stack>
#include <set>
#include <map>
#include <list>

#include "xdaq/Application.h"
#include "b2in/eventing/Diagnostics.h"
#include "b2in/eventing/Statistics.h"
#include "b2in/eventing/Subscription.h"

#include "xgi/Input.h"
#include "xgi/Output.h"
#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

namespace b2in
{
namespace eventing
{
	class HyperDAQ
	{
		public:

		HyperDAQ(xdaq::Application* application, Statistics* statistics, std::map<std::string, std::list<Subscription*> >  & subscriptions, b2in::eventing::Diagnostics* diagnostics);

		~HyperDAQ();

		//! Web interface
		//
		void mainPage(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
		
		void StatisticsTabPage
		(
			xgi::Output * out
		) 
		throw (xgi::exception::Exception);
		
		void SubscriptionTabPage
		(
			xgi::Output * out
		)
		throw (xgi::exception::Exception);

		void DiagnosticsTabPage
		(
			xgi::Output * out
		)
		throw (xgi::exception::Exception);

		protected:

		xdaq::Application* application_;
		Statistics* statistics_;
		std::map<std::string, std::list<Subscription*> >  & subscriptions_;
		b2in::eventing::Diagnostics* diagnostics_;
	};
}
}
#endif

