// $Id: Application.h,v 1.4 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_Application_h_
#define _xplore_Application_h_

#include "xdaq/WebApplication.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "xdata/String.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationRegistry.h"
#include "xdaq/Network.h"
#include "xdaq/Endpoint.h"
#include "xcept/tools.h"

#include "xslp/DiscoveryService.h"
#include "xplore/Interface.h"
#include "xplore/Browser.h"
#include "toolbox/ActionListener.h"
#include "toolbox/Event.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h" 
#include "toolbox/task/Timer.h"
#include "toolbox/BSem.h"
#include "toolbox/ActionListener.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"

#include <vector>

#include "xplore/Settings.h"

namespace xplore
{

class Application: 
	public xdaq::WebApplication, 
	public toolbox::ActionListener,
	public xdata::ActionListener,
	public xplore::Interface,
	public toolbox::task::TimerListener
{	
	public:
	
	XDAQ_INSTANTIATOR();

	
	/*! Interfaces inherited from xdaq::XPlore */
	void search 
	(
		const std::string& type, 
		const std::string& filter, 
		std::vector<xplore::Advertisement::Reference>& resultSet
	) 
		throw (xdaq::exception::Exception);
		
	void retrieveProperties(const std::string& service, toolbox::Properties& properties)
		throw (xdaq::exception::Exception);

			
	// ----------------------------------------------------
		
	void actionPerformed(toolbox::Event& e);
	
	void actionPerformed(xdata::Event& e);
		
	Application(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);

	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	//! Display all advertisements of a given type (to be extracted from HTTP stream as "advtype"
	//	
	//void displayAdvertisements(xgi::Input * in, xgi::Output* out) throw (xgi::exception::Exception);
	
	//! Remove an advertisement by its id (passed in CGI form as "id")
	//
	//void removeAdvertisement(xgi::Input * in, xgi::Output* out) throw (xgi::exception::Exception);

	void display(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void action(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void apply(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
    
    void search(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	private:
	
	// Allow the xplore::Settings class to access
	// all private members so it can save them to disk
	//
	friend class xplore::Settings;
	
	void timeExpired (toolbox::task::TimerEvent& e) ;
	void addListener( toolbox::ActionListener * listener, const std::string & service, const std::string & filter)  throw (xplore::exception::Exception);
	void removeListener( toolbox::ActionListener * listener )  throw (xplore::exception::Exception);

	//void revokeApplication(xdaq::Application* application) 
	//		throw (xdaq::exception::Exception);
		
	void publishApplication(xdaq::ApplicationDescriptor* descriptor) throw (xdaq::exception::Exception);
	void publishEndpoint(xdaq::Endpoint* endpoint, xdaq::Network* network) throw (xdaq::exception::Exception);
	
	
	// Load and save operations for settings
	// The settings file should be called xplore.conf and a
	// sample one is found in TriDAS/daq/xplore/xml/xplore.conf
	//
	void loadSettings(const std::string& filename) throw (xplore::exception::Exception);
	
	void saveSettings(const std::string& filename) throw (xplore::exception::Exception);

	xslp::DiscoveryService discoveryService_;
	
	toolbox::BSem mutex_;
	//std::multimap<toolbox::ActionListener *, std::string > filters_;
	std::multimap<toolbox::ActionListener *, std::pair<std::string,std::string> > filters_;

	std::string zoneFilter_; // filter according to allowed zones
	
	xplore::Browser *  browser_;
	xplore::Settings*  settings_;
	xdata::String      settingsFile_;	
	xdata::String      republishInterval_; // seconds
	
	toolbox::task::AsynchronousEventDispatcher dispatcher_;
};
}

#endif
