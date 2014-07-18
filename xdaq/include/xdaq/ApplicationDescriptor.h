// $Id: ApplicationDescriptor.h,v 1.10 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationDescriptor_h_
#define _xdaq_ApplicationDescriptor_h_

#include <string>
#include "xdaq/ContextDescriptor.h"
#include "xdata/UnsignedInteger.h"
#include "toolbox/net/UUID.h"

namespace xdaq
{

class ApplicationDescriptor
{
	public:
	
	virtual  ~ApplicationDescriptor() {}

	/*! \returns true if the UUID of the \param descriptor equals the UUID of the current application descriptor
	    \returns false otherwise
	*/
	virtual bool equals (ApplicationDescriptor& descriptor) = 0;

	//! Return the application's class name (not C++ class name, but XML configuration class name)
	//
	virtual std::string getClassName() = 0;
	
	//! Return the application instance number (instances run from 0 to n and have to be contiguous)
	//
	virtual xdata::UnsignedIntegerT getInstance() = 0;
	
	//! Return the application identifier (tids run from 0 to n)
	//
	virtual xdata::UnsignedIntegerT getLocalId() = 0;

	//! Return a pointer to the context to which this application belongs
	//
	virtual xdaq::ContextDescriptor* getContextDescriptor() = 0;
	
	//! Return a URN for the application
	virtual std::string getURN() = 0;
	
	//! Returns true if an instance was specified for this application
	virtual bool hasInstanceNumber() = 0;
	
	//! Returns the value of an application property, empty string if it doesn't exist
	//
	virtual std::string getAttribute (const std::string& name) = 0;
	
	//! Sets the value of an application property
	//
	virtual void setAttribute (const std::string& name, const std::string& value) = 0;
	
	//! Returns the universal unique identifier of the application desciptor
	//
	virtual toolbox::net::UUID getUUID() = 0;
	
};

}

#endif
