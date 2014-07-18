// $Id: RoutingTable.h,v 1.7 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_RoutingTable_h_
#define _xdaq_RoutingTable_h_

#include <map>
#include <string>
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/exception/NoRoute.h"
#include "xdaq/exception/DuplicateRoute.h" 

namespace xdaq 
{

//! The default routing from source to destination tids.
//! There may be other routes, but they are not stored in this table.
//
class RoutingTable 
{
	public:
	
	//! Retrieve the default network name to a destination tid
	//
	std::string getNetworkPath
	(
		xdaq::ApplicationDescriptor* from, 
		xdaq::ApplicationDescriptor* to
	) 
	throw (xdaq::exception::NoRoute);
	
	/*! add a network path for a source/destination tid combination. Throw an exception, if a path exists already

	*/
	void addNetworkPath
	(
		xdaq::ApplicationDescriptor* from, 
		xdaq::ApplicationDescriptor* to, 
		const std::string & networkName
	) 
	throw (xdaq::exception::DuplicateRoute);
	
	/*! set a network path for a source/destination tid combination. Be sure to check that the network is 
	  *  available on both hosts.
	*/
	void setNetworkPath
	(
		xdaq::ApplicationDescriptor* from, 
		xdaq::ApplicationDescriptor* to, 
		const std::string & networkName
	);
	
	private:
	
	//matrix of network names (from and to are ApplicationDescriptor references)
	std::map<xdaq::ApplicationDescriptor*, std::map<xdaq::ApplicationDescriptor*, std::string> > routes_;
};


}

#endif
