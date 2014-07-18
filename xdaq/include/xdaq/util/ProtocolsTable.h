// $Id: ProtocolsTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ProtocolsTable_h_
#define _xdaq_util_ProtocolsTable_h_

#include <string>
#include <map>


#include "xdaq/exception/ProtocolNotFound.h"
#include "xdaq/exception/DuplicateProtocol.h"

#include "xdaq/util/ProtocolDescriptor.h"


namespace xdaq {

namespace util {

class ProtocolsTable
{
	public:
	
	// DTOR
	~ProtocolsTable()
	{
		std::map<std::string, xdaq::util::ProtocolDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  protocols_.begin(); i != protocols_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new protocol with name implemented by clasName
	/*! A protocol is uniquely identified by its name, e.g. tcp  */
	xdaq::util::ProtocolDescriptor* createProtocolDescriptor (const std::string  & name, const std::string  & className ) throw  (xdaq::exception::DuplicateProtocol )
	{
		if ( protocols_.find(name) == protocols_.end() ) 
		{
			protocols_[name] = new xdaq::util::ProtocolDescriptor(name,className);
			return protocols_[name];
		}
		else
		{
			std::string msg = toolbox::toString("Protocol name %s already existing", name.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateProtocol, msg);
		}	
	}
	
	//! Remove a host descriptor by name 
 	void removeProtocol(const std::string & name) throw (xdaq::exception::ProtocolNotFound)
	{
		if ( protocols_.find(name) != protocols_.end() ) 
		{
			xdaq::util::ProtocolDescriptor* d = protocols_[name];
			delete d;
			protocols_.erase(name);
		}
		else
		{
			std::string msg = toolbox::toString("No descriptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::ProtocolNotFound, msg);
		}
	}
	
	//! Retrieve a host by indicating the name 
 	xdaq::util::ProtocolDescriptor*  getProtocolDescriptor(const std::string & name) throw (xdaq::exception::ProtocolNotFound)
	{
		if ( protocols_.find(name) != protocols_.end() ) 
		{
			return protocols_[name];

		}
		else
		{
			std::string msg = toolbox::toString("No descritptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::ProtocolNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::ProtocolDescriptor*>   getProtocolDescriptors() 
	{
		std::vector<xdaq::util::ProtocolDescriptor*> protocols;

		std::map<std::string, xdaq::util::ProtocolDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  protocols_.begin(); i != protocols_.end(); i++ )
		{
			protocols.push_back((*i).second);

		}
		return protocols;

	}
	
	private:
	
	std::map<std::string, xdaq::util::ProtocolDescriptor*, std::less<std::string> > protocols_;
	
};
}
}

#endif
