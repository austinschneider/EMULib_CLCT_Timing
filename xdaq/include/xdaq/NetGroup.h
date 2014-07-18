// $Id: NetGroup.h,v 1.6 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_NetGroup_h_
#define _xdaq_NetGroup_h_

#include <map>
#include <vector>
#include <string>

#include "xdaq/Network.h"
#include "xdaq/exception/NoNetwork.h"
#include "xdaq/exception/DuplicateNetwork.h"  

namespace xdaq {

//! Collect all logical network defined for a given cluster
//
class NetGroup 
{
	public:
	
	//! Add a new network to the group. If network exists already an exception is thrown
	// 
	void addNetwork(const std::string & name, const std::string & protocol) 
		throw (xdaq::exception::DuplicateNetwork);
	
	bool isNetworkExisting (const std::string & name) const;
	
	Network * getNetwork(const std::string & name) 	
		throw (xdaq::exception::NoNetwork);
	
	//! Returns a list of all networks
	std::vector<xdaq::Network*> getNetworks();
	
	~NetGroup();
	
	private:
	
	// Index by network name
	std::map<std::string, xdaq::Network*, std::less<std::string> > networks_;
};

}

#endif





