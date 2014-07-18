// $Id: Application.h,v 1.5 2009/05/08 13:03:46 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _executive_Application_h_
#define _executive_Application_h_

#include "xercesc/dom/DOM.hpp"
#include <xercesc/util/XMLURL.hpp>
#include <string.h>
#include <stdlib.h>

#include "toolbox/HostInfo.h"
#include "toolbox/Runtime.h"

#include "xdaq/WebApplication.h"
#include "xoap/MessageReference.h"

#include "xdata/ActionListener.h"
#include "xdaq/exception/Exception.h"
#include "xdaq/exception/BadCommand.h"
#include "xdaq/exception/ConfigurationError.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xdata/Double.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Integer.h"
#include "xdata/Table.h"

namespace executive {

class Application: public xdaq::WebApplication, xdata::ActionListener
{
	const std::string ConfigurationNamespaceURI;
	public:
	
 	XDAQ_INSTANTIATOR();
	
	Application (xdaq::ApplicationStub * stub) throw (xdaq::exception::Exception);
	
	~Application ();
	
	//! override default xdaqApplication  methods, this enable access to
	//! message information
	
	xoap::MessageReference Configure (xoap::MessageReference message) 
		throw (xoap::exception::Exception);
		
	/*! Return list of all loaded modules in format
	    <module name="" version=""/>
	    <module...
	 */
	xoap::MessageReference ListModules (xoap::MessageReference message) 
		throw (xoap::exception::Exception);			
		
	//! Callback for setting xdata parameters
	//
	void actionPerformed (xdata::Event& e);
	
	//! Configure the executive with a valid configuration contained in a DOM tree.
	// This function is internally called by Configure with SOAP or CGI and by HyperDAQ
	//
	void Configure (DOMNode* configurationNode) throw (xdaq::exception::Exception);

	protected:
		
	void addApplicationConfigs (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void downloadModules (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void instantiateApplications (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void configureAliasNetworks (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void configureNetworks (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void configureDefaultRouting (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	void overwriteDefaultRouting (DOMNode* partitionNode) 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);

	void configureProtocols (DOMNode* partitionNode)
		 throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);

	//! loop over all local endpoints and call "configure" of all local peer transports
	//
	void configureTransportReceivers() 
		throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
		
	void parseDefinitions (DOMNode* funcNode ); 
		
	//! set the executives default parameters (helper function)
	//void setExecutiveDefaultValues(DOMNode* partitionNode )
	//	throw (xdaq::exception::BadCommand, xdaq::exception::ConfigurationError);
		
	/*! Default callback function for unhandled asynchronous exceptions that are reported
	  *  via the xdaq::exception::Processor
	  */
	bool handleException(xcept::Exception& ex, void * context);
	
	//! exported configurables
	//
	xdata::String tempDir_;
	xdata::Boolean checkPackageDependencies_;
	xdata::String logUrl_;
	xdata::String logLevel_;		
	
	toolbox::ProcessInfo::Reference processInfo_;
	toolbox::HostInfo::Reference hostInfo_;
	
	//! Helper variables
	//
	std::string lastLogUrl_;
	std::string lastLogLevel_;
	
	//! Monitorables
	xdata::Integer m_pid_;
	xdata::Double m_sampleDuration_;
	xdata::Double m_cpuUsage_;
	xdata::Double m_totalCpuUsage_;
	xdata::UnsignedInteger32 m_virtualSize_;
	xdata::UnsignedInteger32 m_residentSize_;
	xdata::String m_context_;	
	xdata::Table m_diskUsage_;

};
}
#endif
