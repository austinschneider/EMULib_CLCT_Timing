// $Id: Application.h,v 1.2 2008/07/18 15:26:42 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _roundtrip_Application_h_
#define _roundtrip_Application_h_

#include "i2o/i2o.h"

#include "xdata/UnsignedInteger.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedLong.h"
#include "xdata/Double.h"
#include "xdaq/WebApplication.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/ApplicationContext.h"
#include "i2o/Method.h"
#include "toolbox/mem/Reference.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/mem/CommittedHeapAllocator.h"
#include "toolbox/exception/Handler.h"
#include "toolbox/net/URN.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include <list>
#include <algorithm>
#include <map>
#include "toolbox/PerformanceMeter.h"

#include "xgi/WSM.h"
//
// cgicc
//
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "xgi/Utils.h"
#include "xgi/Input.h"
#include "xgi/Output.h"


// #include "Plot.h"

// Example:
// This is an example that shows how to build a simple XDAQ peer to 
// peer application.
// The peer is called RoundTrip. Peer instance 0 sends an i2o frame 
// and peer 1 returns the frame, the frame shuttles between the peers
// repeatedly, total number of roundtrips is set by the run control 
// parameter "samples".

// callback binding (user defined)
#define I2O_TOKEN_CODE 0x0001

typedef struct _I2O_TOKEN_MESSAGE_FRAME 
{
	I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;
} I2O_TOKEN_MESSAGE_FRAME, *PI2O_TOKEN_MESSAGE_FRAME;


namespace roundtrip
{

class Application: public xdaq::WebApplication, xdata::ActionListener
{
	
public:
	XDAQ_INSTANTIATOR();

	Application(xdaq::ApplicationStub* stub) throw (xdaq::exception::Exception);
	
	bool onError ( xcept::Exception& ex, void * context );
	
	//
	// This function is invoked whenever a message comes
	// in - both on the instance 0 and instance 1
	//
	void token(  toolbox::mem::Reference * ref)  throw (i2o::exception::Exception) ;
	
	//
	// Callback for requesting current exported parameter values
	//
	void actionPerformed (xdata::Event& e);
	
	xoap::MessageReference fireEvent (xoap::MessageReference msg) throw (xoap::exception::Exception);

	void ConfigureAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception);
	void EnableAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception );
	void HaltAction(toolbox::Event::Reference e) throw (toolbox::fsm::exception::Exception );
	
	// Web callback functions
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void dispatch (xgi::Input * in, xgi::Output * out)  throw (xgi::exception::Exception);
	void Configure(xgi::Input * in ) throw (xgi::exception::Exception);
	void Enable(xgi::Input * in ) throw (xgi::exception::Exception);
	void Halt(xgi::Input * in ) throw (xgi::exception::Exception);
	void stateMachinePage( xgi::Output * out ) throw (xgi::exception::Exception);
	void displayMeasurements(xgi::Input * in, xgi::Output * out)  throw (xgi::exception::Exception);
	void failurePage(xgi::Output * out, xgi::exception::Exception & e)  throw (xgi::exception::Exception);
	
protected:
	
	// some parameters
	xdata::UnsignedInteger64 counter_;
	xdata::UnsignedInteger samples_;
	xdata::UnsignedInteger startSize_;
	xdata::UnsignedInteger endSize_;
	xdata::UnsignedInteger currentSize_;
	xdaq::ApplicationDescriptor* destination_;
	xdata::UnsignedInteger destinationInstance_;
	//
	//! performance meters
	//
	toolbox::PerformanceMeter  pmeter_;
	//
	//! current measurements
	//
	xdata::Double dataBw_;
	xdata::Double dataRate_;
 	xdata::Double dataLatency_;
	xdata::UnsignedInteger step_;
	xdata::UnsignedInteger pipeLine_;	
	xdata::UnsignedInteger committedPoolSize_;
	
	toolbox::mem::Pool* pool_;
	toolbox::exception::HandlerSignature  * errorHandler_;
	
	struct Measurement
	{
		Measurement()
		{
			latency = 0.0;
			rate = 0.0;
			bandwidth = 0.0;
		}
		
		Measurement(double l, double r, double b)
		{
			latency = l;
			rate = r;
			bandwidth = b;
		}
		
		double latency;
		double bandwidth;
		double rate;
	};
	
	std::map<unsigned long, Measurement, std::less<unsigned long> > measurementHistory_;
	
	toolbox::fsm::FiniteStateMachine fsm_; // application state machine
	xgi::WSM wsm_; // Web dialog state machine

        void downloadMeasurements(xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception);
};
}
#endif
