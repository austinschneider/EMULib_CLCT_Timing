// $Id: GroupTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_GroupTable_h_
#define _xdaq_util_GroupTable_h_

#include <string>
#include <map>


#include "xdaq/exception/GroupNotFound.h"
#include "xdaq/exception/DuplicateGroup.h"

#include "xdaq/util/Group.h"


namespace xdaq {

namespace util {

class GroupTable
{
	public:
	
	// DTOR
	~GroupTable()
	{
		std::map<std::string, xdaq::util::Group*, std::less<std::string> >::iterator i;
		for ( i =  groups_.begin(); i != groups_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new group  with name.
	/*! A group is uniquely identified by its name, e.g. peer */       
	xdaq::util::Group* createGroup(const std::string & name)
                                        throw  (xdaq::exception::DuplicateGroup )
	{
		if ( groups_.find(name) == groups_.end() ) 
		{
			groups_[name] = new xdaq::util::Group(name);
			return groups_[name];
		}
		else
		{
			std::string msg = toolbox::toString("Group name %s already existing", name.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateDevice, msg);
		}	
	}
	
	//! Remove a device descriptor by name 
 	void removeGroup(const std::string & name) throw (xdaq::exception::GroupNotFound)
	{
		if ( groups_.find(name) != groups_.end() ) 
		{
			xdaq::util::Group* d = groups_[name];
			delete d;
			groups_.erase(name);
		}
		else
		{
			std::string msg = toolbox::toString("No group for name %s found",name.c_str());
			XCEPT_RAISE(xdaq::exception::GroupNotFound, msg);
		}
	}
	
	//! Retrieve a host by indicating the name 
 	xdaq::util::Group*  getGroup(const std::string & name) 
		throw (xdaq::exception::GroupNotFound)
	{
		if ( groups_.find(name) != groups_.end() ) 
		{
			return groups_[name];

		}
		else
		{
			std::string msg = toolbox::toString("No group for name %s found",name.c_str());
			XCEPT_RAISE(xdaq::exception::DeviceNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::Group*>   getGroups() 
	{
		std::vector<xdaq::util::Group*> groups;

		std::map<std::string, xdaq::util::Group*, std::less<std::string> >::iterator i;
		for ( i =  groups_.begin(); i != groups_.end(); i++ )
		{
			groups.push_back((*i).second);

		}
		return groups;

	}
	
	private:
	
	std::map<std::string, xdaq::util::Group*, std::less<std::string> > groups_;
	
};
}
}

#endif
