// $Id: NetworkConnectionTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_NetworkConnectionTable_h_
#define _xdaq_util_NetworkConnectionTable_h_

#include <string>
#include <map>


#include "xdaq/exception/ConnectionNotFound.h"
#include "xdaq/exception/DuplicateConnection.h"

#include "xdaq/util/HostDescriptor.h"
#include "xdaq/util/NetworkDevice.h"

namespace xdaq {

namespace util {

class NetworkConnectionTable
{
	public:
	
	// DTOR
	~NetworkConnectionTable()
	{
		for (int i = 0; i< connections_.size(); i++)
                {
                    delete connections_[i];
                }    
	}
	
	//! Create a new host/network 
	xdaq::util::NetworkConnection* createConnectionDescriptor (xdaq::util::HostDescriptor * h, xdaq::util::NetworkDevice * n )
                                        throw  (xdaq::exception::DuplicateConnection )
	{
                for (int i = 0; i< connections_.size(); i++)
                {
                    xdaq::util::NetworkDevice * d = connections_[i];
                    if (( d->getHostDescriptor()->getName() == h->getName() ) && (  d->getNetworkDevice()->getName() == n->getName()  ) )
                    {
                             std::string msg = toolbox::toString("Connection already existing for host %s network %s found", h->getName().c_str(), n->getName().c_str());
                             XCEPT_RAISE(xdaq::exception::DuplicateConnection, msg);
                    }
                }
                xdaq::util::NetworkConnection d = new xdaq::util::NetworkConnection(h,n);
                connections_.push_back(d);
                return d;
               
		
	}
	
	//! Remove a connection descriptor by host and network
 	void removeConnection(const std::string & host, const std::string & network) throw (xdaq::exception::ConnectionNotFound)
	{
		for (int i = 0; i< connections_.size(); i++)
                {
                    xdaq::util::NetworkConnection * d = connections_[i];
                    if (( d->getHostDescriptor()->getName() == host ) && (  d->getNetworkDescriptor()->getName() == network ) )
                    {
                            delete d;
                            connections_.erase(i);
                            return;
                    }
                }
                std::string msg = toolbox::toString("No descritptor for host %s network %s found",host.c_str(), network.c_str());
                XCEPT_RAISE(xdaq::exception::ConnectionNotFound, msg);

	}
	
	//! Retrieve a connection descriptor by indicating the host and network 
 	xdaq::util::NetworkConnection*  getConnectionDescriptor(const std::string & host,const std::string & network )
                        throw (xdaq::exception::ConnectionNotFound)
	{
		for (int i = 0; i< connections_.size(); i++)
                {
                    xdaq::util::NetworkConnection * d = connections_[i];
                    if (( d->getHostDescriptor()->getName() == host ) && (  d->getNetworkDevice()->getName() == network ) )
                    {
                            return d;
                    }
                }
                std::string msg = toolbox::toString("No descritptor for host %s network %s found",host.c_str(), network.c_str());
                XCEPT_RAISE(xdaq::exception::ConnectionNotFound, msg);

	}
	
	std::vector<xdaq::util::NetworkConnection*>  getConnectionDescriptors() 
	{
		return connections_;

	}
	
	private:
	
	std::vector<xdaq::util::NetworkConnection*>> connections_;
	
};
}
}

#endif
