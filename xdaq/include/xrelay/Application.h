// $Id: Application.h,v 1.2 2008/07/18 15:28:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xrelay_Application_h_
#define _xrelay_Application_h_

#include <string>

#include "xdaq/WebApplication.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/ApplicationContext.h"

#include "xdaq/exception/Exception.h"
#include "xdaq/exception/ParameterSetFailed.h"
#include "xdaq/exception/CommandStateMismatch.h"
#include "xdaq/exception/MultipleCommandsInSOAP.h"
#include "xdaq/exception/MissingCommandInSOAP.h"
#include "xoap/MessageFactory.h"
#include "xoap/MessageReference.h"
#include "xoap/Method.h"
#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/task/WaitingWorkLoop.h"
#include "toolbox/task/Action.h"
#include "xdata/InfoSpace.h"
#include "xoap/MessageReference.h"

namespace xrelay {

class Application: public xdaq::WebApplication
{
	public:
		XDAQ_INSTANTIATOR();

		Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
	
		//! Handler for any ('*') incoming SOAP message. Extracts '<relay>' header and processes it in processRelay
		//
		xoap::MessageReference onMessage (xoap::MessageReference msg)
			throw (xoap::exception::Exception);
		
		//! Callback for handling '<Notify>' SOAP messages (replies from '<relay>' processors)
		//
		xoap::MessageReference onNotify (xoap::MessageReference msg)
			throw (xoap::exception::Exception);	
			
		//! A simple handler for a '<Test>' message that can be used to test the xrelay processor
		//
		xoap::MessageReference onTest (xoap::MessageReference msg)
			throw (xoap::exception::Exception);		
			
		//! Process the '<relay>' tags
		//
		bool processRelay(toolbox::task::WorkLoop* wl);	
	
	protected:
	
		//! Wrapper to send a SOAP message to url/urn combination
		//
		void sendMessage (xoap::MessageReference msg, const std::string & url, const std::string & urn) 
			throw (xdaq::exception::Exception);

		//! Relay a message to another xrelay
		//
		void processRoute(xoap::MessageReference message, DOMNode* toNode, DOMNode * fromNode, 
				const std::string & url, const std::string & urn, const std::string & prefix)
			throw (xdaq::exception::Exception);

		//! Extract a '<from>' tag from a '<relay>' element and return the DOM node that points to it or 0 if not found	
		//
		DOMNode * extractFromNode(DOMNode * relayNode);
		
		//! Extract a '<to>' tag from any element and return the DOM node that points to it or 0 if not found		
		//
		DOMNode * extractToNode(DOMNode * relayNode);

		//! Check if the given '<to>' tag contains other '<to>' tags and therefore is a routing node
		//
		bool isRoutingNode(DOMNode * toNode);

		/*! set a Reply route in message
		 */
		void setReplyRoute(xoap::MessageReference message, DOMNode* fromNode) throw (xdaq::exception::Exception);
		
		toolbox::task::ActionSignature* processRelayJob_;
		toolbox::task::WorkLoop* workLoop_;
		toolbox::rlist<xoap::MessageReference*> relayQueue_;
		size_t maxRetries_;
};

}

#endif
