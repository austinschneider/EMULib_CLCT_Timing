// $Id: StandardConfiguration.h,v 1.9 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_StandardConfiguration_h_
#define _xdaq_util_StandardConfiguration_h_

#include <vector>
#include <map>

#include "toolbox/net/URL.h"

#include "xdaq/util/Configuration.h"
#include "xdaq/util/HostsTable.h"
#include "xdaq/util/NetworkDeviceTable.h"
#include "xdaq/util/GroupTable.h"


namespace xdaq
{
	namespace util
	{
	
		class StandardConfiguration : public xdaq::util::Configuration
		{
			public:
			
			virtual std::string getType()
			{
				return("urn:xdaq-configuration-type:standard");
			}
			
			StandardConfiguration()
        		{
			
  			}
			
			virtual ~StandardConfiguration()
        		{
			
  			}
			
			xdaq::ContextTable * getContextTable()
			{
				return &contextTable_;
			}
			
			xdaq::ApplicationGroup * getApplicationGroup()
			{
				return &applicationGroup_;
			}
			
			xdaq::util::HostsTable * getHostsTable()
			{
				return &hostsTable_;
			}
			
			xdaq::util::ModulesTable * getModulesTable()
			{
				return &modulesTable_;
			}
			
			xdaq::util::ClassesTable * getClassesTable()
			{
				return &classesTable_;
			}
			
			xdaq::util::ProtocolsTable * getProtocolsTable()
			{
				return &protocolsTable_;
			}
			
			xdaq::util::NetworkDeviceTable * getNetworkDeviceTable()
			{
				return &networksTable_;
			}
			
			// safe editing functions
			
			//! Remove a context from a configuration keeping consistency with related objects
			void removeContext(const std::string & name)
			{
				
				// remove all applications that belong to this context
				xdaq::ContextDescriptor * cd = contextTable_.getContextDescriptor(name);


				std::vector<xdaq::ApplicationDescriptor*> applications = applicationGroup_.getApplicationDescriptors (cd);

				for ( std::vector<xdaq::ApplicationDescriptor*>::size_type  i = 0; i < applications.size(); i++ )
				{
					applicationGroup_.removeApplicationDescription(cd, applications[i]->getClassName(),applications[i]->getLocalId()); 
				}

				// finally remove context
				contextTable_.removeContext(name);

				
			}
			
			void removeHost(const std::string & name)
			{
				
				// remove all context that belong to this host
				
				std::vector<xdaq::ContextDescriptor*> contexts =  contextTable_.getContextDescriptors();

				for ( std::vector<xdaq::ContextDescriptor*>::size_type  i = 0; i < contexts.size(); i++ )
				{
					toolbox::net::URL url(contexts[i]->getURL());
					if ( url.getHost() == name ) 
						this->removeContext(contexts[i]->getURL()); 
				}

				// finally remove  host
				hostsTable_.removeHost(name);

				
			}
			
			
			
			private:
			
			xdaq::ContextTable contextTable_;	
			xdaq::ApplicationGroup applicationGroup_;
			xdaq::util::HostsTable hostsTable_;
			xdaq::util::ClassesTable classesTable_;
			xdaq::util::ModulesTable modulesTable_;
			xdaq::util::ProtocolsTable protocolsTable_;
			xdaq::util::NetworkDeviceTable networksTable_;
			xdaq::util::GroupTable groupTable_;
			
					

		};
	
	}
	
}

#endif
