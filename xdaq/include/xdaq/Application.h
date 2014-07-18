// $Id: Application.h,v 1.31 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_Application_h_
#define _xdaq_Application_h_

#include <string>

#include "xdaq/ApplicationStub.h"
#include "xdaq/ApplicationDescriptor.h"
#include "toolbox/lang/Class.h"
#include "toolbox/net/URN.h"

#include "xdaq/ApplicationContext.h"

#include "xdaq/exception/Exception.h"
#include "xdaq/exception/ParameterSetFailed.h"

#include "xoap/MessageReference.h"
#include "xdata/InfoSpace.h"

//
// The following macro instantiates a XDAQ appliation.
// An application class cannot have a namespace qualifier. The macro does not work in this case.
//
#define XDAQ_INSTANTIATE(CLASS) \
extern "C" xdaq::Application * instantiate_##CLASS(xdaq::ApplicationStub * stub ) throw (xdaq::exception::Exception) \
{\
	std::cerr << "Macro XDAQ_INSTANTIATE is deprecated. Use XDAQ_INSTANTIATOR and XDAQ_INSTANTIATOR_IMPL" << std::endl; \
	return new CLASS(stub);\
}

/*! The XDAQ_INSTANTIATOR macro needs to put this macro into the header file (.h) class declaration */
#define XDAQ_INSTANTIATOR() \
static xdaq::Application* instantiate(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception)

/*! the XDAQ_INSTANTIATOR_IMPL(ns1::ns2::...) macro needs to be put into the implementation file (.cc) of the XDAQ application */
#define XDAQ_INSTANTIATOR_IMPL(QUALIFIED_CLASS_NAME) \
xdaq::Application * QUALIFIED_CLASS_NAME::instantiate(xdaq::ApplicationStub * stub ) \
throw (xdaq::exception::Exception) \
{\
	return new QUALIFIED_CLASS_NAME(stub);\
}

namespace xdaq
{


class Application: public virtual toolbox::lang::Class
{
	public:
	
	Application
	(
		xdaq::ApplicationStub * c
	) 
	throw (xdaq::exception::Exception);
	
	virtual ~Application();
	
	//! Return the InfoSpace that is associated with the application (it contains the exported parameters)
	//
	xdata::InfoSpace* getApplicationInfoSpace();	
	
	// Allow initialization of values after creation
	void setDefaultValues(DOMNode* funcNode) throw (xdaq::exception::ParameterSetFailed);

	// Interface to exported parameters (temporary only)
	virtual xoap::MessageReference ParameterGet (xoap::MessageReference message) throw (xoap::exception::Exception);
	virtual xoap::MessageReference ParameterSet (xoap::MessageReference message) throw (xoap::exception::Exception);
	virtual xoap::MessageReference ParameterQuery (xoap::MessageReference message) throw (xoap::exception::Exception);
	virtual xoap::MessageReference InterfaceQuery (xoap::MessageReference message) throw (xoap::exception::Exception);
	
	xdaq::ApplicationContext* getApplicationContext();
	
	xdaq::ApplicationDescriptor* getApplicationDescriptor();
	
	Logger & getApplicationLogger();
	
	//! Create an infospace scoped within the XDAQ application. A unique id 'urn:<nid>:<uniqueid>' is returned to identify the infospace
	// associated to this application. This method can be used to create an unlimited number of infospaces.
	// 
	toolbox::net::URN createQualifiedInfoSpace(const std::string & nid ) 
		throw (xdaq::exception::Exception );

	void notifyQualified( std::string severity, xcept::Exception & e  );
	void qualifyException( std::string severity, xcept::Exception & e  );


	private:
	
	// the Application is responsible for deleting the Stub object
	std::auto_ptr<xdaq::ApplicationStub> stub_;	
	xdaq::ApplicationContext* context_;	
};

}

#endif


