// $Id: Configuration.h,v 1.6 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_Configuration_h_
#define _xdaq_util_Configuration_h_

#include <string>

#include "xdaq/ContextTable.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/util/HostsTable.h"
#include "xdaq/util/ModulesTable.h"
#include "xdaq/util/ClassesTable.h"
#include "xdaq/util/ProtocolsTable.h"
#include "xdaq/util/NetworkDeviceTable.h"

namespace xdaq
{
	namespace util
	{
	
		class Configuration 
		{
			public:
			
			virtual ~Configuration() {};
			
			virtual std::string  getType() = 0;
			
			virtual xdaq::ContextTable * getContextTable() = 0;
			
			virtual xdaq::ApplicationGroup * getApplicationGroup() = 0;
			
			virtual xdaq::util::HostsTable * getHostsTable() = 0;
			
			virtual xdaq::util::ModulesTable * getModulesTable() = 0;
			
			virtual xdaq::util::ClassesTable * getClassesTable() = 0;

			virtual xdaq::util::ProtocolsTable * getProtocolsTable() = 0;
			
			virtual xdaq::util::NetworkDeviceTable * getNetworkDeviceTable() = 0;
			
			// safe editing functions
			
			//! Remove a context from a configuration keeping consistency with related objects
			virtual void removeContext(const std::string & name) = 0;
                        
			//! Remove a host from a configuration keeping consistency with related objects
			virtual void removeHost(const std::string & name) = 0;
			
			protected:


		};
	
	}
	
}

#endif
