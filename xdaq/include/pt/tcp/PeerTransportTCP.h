// $Id: PeerTransportTCP.h,v 1.6 2008/12/08 08:30:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_PeerTransportTCP_h_
#define _pt_tcp_PeerTransportTCP_h_

#include "xdaq/WebApplication.h"
#include "pt/tcp/PeerTransportSender.h"
#include "pt/tcp/PeerTransportReceiver.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xdata/Double.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/ActionListener.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"

#include "xgi/WSM.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"


namespace pt
{

namespace tcp
{

//! this is the XDAQ Peer Transport Appliction Wrapper
//
class PeerTransportTCP: public xdaq::WebApplication,  xdata::ActionListener
{
	public:
	
	XDAQ_INSTANTIATOR();
	
	PeerTransportTCP(xdaq::ApplicationStub * s) throw(xdaq::exception::Exception);
	
	~PeerTransportTCP();
	
	//! Default page, displays configuration page
	//
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	//! apply new configuration 
	//
	void apply(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	
	void failurePage(xgi::Output * out, xcept::Exception & e)  throw (xgi::exception::Exception);
	
	private:
	void actionPerformed (xdata::Event& e) ;
	void reset() throw (pt::exception::Exception);

	void StatisticsTabPage (xgi::Output * out) throw (xgi::exception::Exception);
	
	pt::tcp::PeerTransportSender* pts_;
	pt::tcp::PeerTransportReceiver* ptr_;

	xdata::Boolean autosize_;
	xdata::UnsignedInteger32 maxPacketSize_;
	xdata::UnsignedInteger32 maxClients_;
	xdata::String poolName_;
	
	xdata::Double committedPoolSize_;
	xdata::Double lowThreshold_;
	xdata::Double highThreshold_;
	xdata::UnsignedInteger32 outputQueueSize_;
	
};

}
}
#endif
