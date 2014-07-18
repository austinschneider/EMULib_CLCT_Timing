// $Id: ZoneImpl.h,v 1.4 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ZoneImpl_h_
#define _xdaq_ZoneImpl_h_

#include <list>
#include "toolbox/BSem.h"
#include "xdaq/Zone.h"
#include "xdata/UnsignedInteger.h"

namespace xdaq
{

class ZoneImpl: public xdaq::Zone
{
	public:
	
	//! Comma separated list of zones e.g. services, system.subsystem, etc
	ZoneImpl
	(
	);
	
	virtual ~ZoneImpl();

	xdaq::ApplicationGroup* createApplicationGroup
	(
		const std::string & group
	) 
	throw (xdaq::exception::Exception);
	

	xdaq::ApplicationGroup* getApplicationGroup
	(
		const std::string & group
	) 
	throw (xdaq::exception::Exception);

	std::set< xdaq::ApplicationGroup * > getGroups
	(
	)
	throw (xdaq::exception::Exception);
	
	//! Retrieve am application descriptor from any of the groups in the zone
	//
	xdaq::ApplicationDescriptor* getApplicationDescriptor 
	(
		xdaq::ContextDescriptor * context, 
		xdata::UnsignedIntegerT localId
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound);
	
	//! Retrieve a set of application descriptors from all groups in the zone
	//
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors
	(
		const std::string & className
	);
	
	//! Retrieve a set of application descriptors from all groups in the zone
	//
	xdaq::ApplicationDescriptor* getApplicationDescriptor 
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound);
		
	//! Retrieve a set of application descriptors from all groups in the zone
	//
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		xdaq::ContextDescriptor * context
	);
		
	std::set<std::string> getGroupNames();
	
	//! Returns the set of all groups the application descriptor belongs to
	//
	std::set<std::string> getGroupNames(xdaq::ApplicationDescriptor* descriptor);
	
	
	//void  removeApplicationGroup(const std::string & name) 
	//	throw (xdaq::exception::Exception);
	
	bool hasApplicationGroup
	(
		const std::string & name
	);
	
	protected:
	
	std::map<std::string, xdaq::ApplicationGroup *> groups_; // descriptors organized by group
	toolbox::BSem mutex_;
};

}

#endif
