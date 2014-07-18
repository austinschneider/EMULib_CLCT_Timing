// $Id: Application.h,v 1.5 2008/08/22 12:56:06 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _hyperdaq_Application_h_
#define _hyperdaq_Application_h_

#include <set>

#include "xdaq/WebApplication.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationRegistry.h"
#include "xcept/tools.h"

namespace hyperdaq {
class Application: public xdaq::WebApplication
{	
	public:
		
	XDAQ_INSTANTIATOR();
		
	Application(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);

	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	void ViewApplications (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void ViewEndpoints (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

	void ViewApplicationGroups (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void ViewGroup (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	void UploadApplicationForm (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void UploadApplication (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void ConfigureExecutiveForm (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void ConfigureExecutive (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void Control (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	void clusterExplore(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	//! Exit currently running process with code 2
	void Exit (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	
	//! Display a page that lists all loaded modules
	void displayModules (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	
	/*! Disply an <applet> tag with the properties editor for the xdaq application 
	  *  the following parameters are passed in a query string: class, instance
	  */
	void editProperties (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	/*! Display a page that lists all the information about a module.
	  * The name of the module is passed as a cgi environment variable named "module"
	  */
	void displayPackageInfo (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	
	/*! Display a page that contains a SOAP client applet for sending
	  * raw SOAP messages to the XDAQ process from which this page has been loaded.
	  */
	void displaySOAPClient (xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

	/*! Display a page that contains a SOAP client applet for sending
	  * raw SOAP messages to the XRelay application that has been loaded into the currently running process.
	  */	
	void displayXRelayController (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	/*! Retrieve a log file if existing
	  * parameters: url in encoded format, e.g. file:/path
	  * tail=size .... from the end of the file 'size' bytes (optional, by default 100)
	  * head=size .... from the beginning of the file 'size' bytes (optional, by default 100)
	  * from=X&len=Y.. from position X of file, Y bytes (len is optional, by default 100)
	  * if the request reads beyond the file size or limits, only the data up to the end of the file are returned
	  * If only the url is provided and nothing else, the whole file is retrieved
	  * If the file does not exist or cannot be opened a failure page is returned
	  */	
	void displayLog (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	/*! Display a page that contains information about the configured loggers and appenders
	  */	
	void logPage (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	/*! Display a page with the navigable content of a log file
	  */	
	void logContentPage (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	/*! Display process information 
          */
	void processInfoPage (xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

	private:

	void displayWidget(xgi::Output * out , const std::string & title, const std::string & url, 
			    const std::string & command, const std::string & icon, const std::string identifier = "");
	
	void displayApplicationTable(xgi::Output* out, std::set<xdaq::ApplicationDescriptor*>  & applications);

	void displayApplicationGroups(xgi::Output* out);
	
	void forwardConfiguration(DOMDocument* doc);
	
	std::vector<std::string> navigation_;
	
	//! Displays a navigation bar with links to all HyperDAQ pages
	void displayNavigationBar(xgi::Output* out);	

	std::string startTime_;

	//! Get a string representation of the current resource limit
	std::string getProcessLimit(int resource);
};

}
#endif
