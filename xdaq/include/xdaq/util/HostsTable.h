// $Id: HostsTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_HostsTable_h_
#define _xdaq_util_HostsTable_h_

#include <string>
#include <map>


#include "xdaq/exception/HostNotFound.h"
#include "xdaq/exception/DuplicateHost.h"

#include "xdaq/util/HostDescriptor.h"


namespace xdaq {

namespace util {

class HostsTable
{
	public:
	
	// DTOR
	~HostsTable()
	{
		std::map<std::string, xdaq::util::HostDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  hosts_.begin(); i != hosts_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new host with name.
	/*! A host is uniquely identified by its name and domain, e.g. lxcmd106.cern.ch */
	xdaq::util::HostDescriptor* createHostDescriptor (const std::string  & name, const std::string  & info ) throw  (xdaq::exception::DuplicateHost )
	{
		if ( hosts_.find(name) == hosts_.end() ) 
		{
			hosts_[name] = new xdaq::util::HostDescriptor(name,info);
			return hosts_[name];
		}
		else
		{
			std::string msg = toolbox::toString("Host url %s already existing", name.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateHost, msg);
		}	
	}
	
	//! Remove a host descriptor by name 
 	void removeHost(const std::string & name) throw (xdaq::exception::HostNotFound)
	{
		if ( hosts_.find(name) != hosts_.end() ) 
		{
			xdaq::util::HostDescriptor* d = hosts_[name];
			delete d;
			hosts_.erase(name);
		}
		else
		{
			std::string msg = toolbox::toString("No descriptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::HostNotFound, msg);
		}
	}
	
	//! Retrieve a host by indicating the name 
 	xdaq::util::HostDescriptor*  getHostDescriptor(const std::string & name) throw (xdaq::exception::HostNotFound)
	{
		if ( hosts_.find(name) != hosts_.end() ) 
		{
			return hosts_[name];

		}
		else
		{
			std::string msg = toolbox::toString("No descritptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::HostNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::HostDescriptor*>   getHostDescriptors() 
	{
		std::vector<xdaq::util::HostDescriptor*> hosts;

		std::map<std::string, xdaq::util::HostDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  hosts_.begin(); i != hosts_.end(); i++ )
		{
			hosts.push_back((*i).second);

		}
		return hosts;

	}
	
	private:
	
	std::map<std::string, xdaq::util::HostDescriptor*, std::less<std::string> > hosts_;
	
};
}
}

#endif
