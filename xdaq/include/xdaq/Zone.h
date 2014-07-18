// $Id: Zone.h,v 1.3 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_Zone_h_
#define _xdaq_Zone_h_

#include <list>
#include "xdaq/ApplicationGroup.h"

namespace xdaq
{

	class Zone
	{
		public:
		
		virtual ~Zone() {};
			
		virtual xdaq::ApplicationGroup*  getApplicationGroup
		(
			const std::string & name
		) 
		throw (xdaq::exception::Exception) = 0;
	
		virtual std::set<xdaq::ApplicationGroup *>  getGroups
		(
		)
		throw (xdaq::exception::Exception) = 0;
			
		virtual bool hasApplicationGroup
		(
			const std::string & name
		) = 0;
		
		virtual xdaq::ApplicationDescriptor* getApplicationDescriptor 
		(
			xdaq::ContextDescriptor * context, 
			xdata::UnsignedIntegerT localId
		)
		throw (xdaq::exception::ApplicationDescriptorNotFound) = 0;
		
		virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
		(
			const std::string & className
		) = 0;
			
		virtual xdaq::ApplicationDescriptor* getApplicationDescriptor 
		(
			const std::string & className, 
			xdata::UnsignedIntegerT instance
		)
		throw (xdaq::exception::ApplicationDescriptorNotFound) = 0;
			
		virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
		(
			xdaq::ContextDescriptor * context
		) = 0;			
				
		virtual std::set<std::string> getGroupNames() = 0;	
		
		//! Returns the set of all groups the application descriptor belongs to
		//
		virtual std::set<std::string> getGroupNames(xdaq::ApplicationDescriptor* descriptor) = 0;	
	};

}

#endif
