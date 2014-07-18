// $Id: ApplicationDescriptorFactory.h,v 1.3 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationDescriptorFactory_h_
#define _xdaq_ApplicationDescriptorFactory_h_

#include <set>
#include "toolbox/BSem.h"


#include "xdaq/ContextDescriptor.h"
#include "xdata/UnsignedInteger.h"
#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/ZoneImpl.h"
#include "xdaq/exception/InvalidZone.h"


namespace xdaq
{

	class ApplicationDescriptorFactory
	{
		public:
		
		ApplicationDescriptorFactory();
		
		//! Returns \true is the provided descriptor exists, i.e. is valid
		//
		bool hasDescriptor(xdaq::ApplicationDescriptor* descriptor);
		
		void lock();
		
		void unlock();
		
		//! Creates zone
		//
		xdaq::ZoneImpl * createZone(const std::string & name ) 
			throw ( xdaq::exception::InvalidZone);
		
		//! Creates a new descriptor object without checking the provided parameters
		//
		xdaq::ApplicationDescriptorImpl* createApplicationDescriptor 
		(
			xdaq::ContextDescriptor* context, 
			const std::string& className, 
			xdata::UnsignedIntegerT localId,
			std::set<std::string>& zones,
			std::set<std::string>& groups
		)
			throw (xdaq::exception::DuplicateApplicationDescriptor, xdaq::exception::InvalidZone);

		/*! Deletes a descriptor object. Throws if descriptor is not valid/existing
		*/
		void destroyDescriptor (xdaq::ApplicationDescriptor* descriptor)
			throw (xdaq::exception::ApplicationDescriptorNotFound);
		
		std::set<std::string> getZoneNames ();
	
		xdaq::Zone * getZone(const std::string & name ) 
			throw ( xdaq::exception::InvalidZone);
				
		static xdaq::ApplicationDescriptorFactory* getInstance();
		
		protected:
		
		std::set<xdaq::ApplicationDescriptorImpl*> descriptors_;
		toolbox::BSem mutex_;
		static xdaq::ApplicationDescriptorFactory* instance_;
		
		std::map<std::string, xdaq::ZoneImpl*> zones_;
	};

}

#endif
