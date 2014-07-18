// $Id: ApplicationDescriptorImpl.h,v 1.14 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationDescriptorImpl_h_
#define _xdaq_ApplicationDescriptorImpl_h_

#include <string>
#include "toolbox/Properties.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdata/String.h"
#include "xdata/UnsignedInteger.h"
#include "xdata/Boolean.h"
#include "xdata/Properties.h"
#include "toolbox/net/UUID.h"
#include "xdaq/exception/Exception.h"

namespace xdaq
{

class ApplicationDescriptorImpl: public ApplicationDescriptor, public xdata::Properties
{
	public:
	
	//! Creation an ApplicationConfig. A logger object needs to be passed for the application. 
	// It must be created before this class is instantiated
	//
	ApplicationDescriptorImpl
	(
		xdaq::ContextDescriptor * context,
		const std::string & className, 
		xdata::UnsignedIntegerT localId,
		const std::string & groups
	);
	
	ApplicationDescriptorImpl
	(
		xdaq::ContextDescriptor * context,
		const std::string & className, 
		xdata::UnsignedIntegerT localId,
		const std::string & groups,
		toolbox::net::UUID & uuid
	);
	
	/*! \returns true if the UUID of the \param descriptor equals the UUID of the current application descriptor
	    \returns false otherwise
	*/
	bool equals (ApplicationDescriptor& descriptor);
		  				  
	//! Return the application's class name (not C++ class name, but XML configuration class name)
	//
	std::string getClassName();
	
	//! Return the application instance number (instances run from 0 to n and have to be contiguous)
	//
	xdata::UnsignedIntegerT getInstance() throw (xdaq::exception::Exception);
	
	//! Return the application target identifier (tids run from 0 to n)
	//
	xdata::UnsignedIntegerT getLocalId();

       	//! Return the hostId to which this application is associated
        //
        xdaq::ContextDescriptor* getContextDescriptor();
	
	//! Return a URN for the application in the form urn:xdaq-application:lid=[number]
	std::string getURN();
	
	/*! Set a new instance number. This shall never be done by ordinary users. It is only done by the executive.
          * The function also updates the tid by constructing a global tid from application id and context id
          */
	void setInstance(xdata::UnsignedIntegerT instance);
	
	//! Returns true if an instance was specified for this application
	bool hasInstanceNumber();
	
	std::string getAttribute (const std::string& name);
	
	void setAttribute(const std::string& name, const std::string& value);
	
	void setAttributes(toolbox::Properties& attributes) throw (xdaq::exception::Exception);
		
	toolbox::net::UUID getUUID();
			
	private:	

	xdata::String className_;
	xdata::UnsignedInteger instance_;
	xdata::Boolean hasInstance_;
	xdata::UnsignedInteger id_;
	xdaq::ContextDescriptor* context_;
	toolbox::net::UUID uuid_;
};

}

#endif
