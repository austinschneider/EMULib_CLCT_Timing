// $Id: Address.h,v 1.1 2007/03/31 14:23:29 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_Address_h
#define _atcp_Address_h

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include "pt/Address.h"
#include "toolbox/net/URL.h"
#include <netinet/in.h>

namespace pt {
namespace atcp
{

class Address: public pt::Address
{
	public:
	
	//! Create address from url
#ifdef XDAQ31
	Address (const std::string  & url, const std::string& service);
#else
	Address (const std::string  & url);
}
#endif
	virtual ~Address ();
	
	//! Get the URL protocol, e.g. atcp
	std::string getProtocol();
	
	//! Get the URL service if it exists, e.g. i2o
	std::string getService();
	
	//! Get additional parameters at the end of the URL
	std::string getServiceParameters();
	
	//! Return the URL in string form
	std::string toString();
	
	//! Get the host part of the url
	std::string getHost();
	
	//! Get the port number of the url if it exists
	std::string getPort();
	
	//! Get the url provided in the constructor
	std::string getURL();
	
	//! Get the path
	std::string getPath();
	
	//! Get the IP representation of the hostname/port address combination
	struct sockaddr_in getSocketAddress();

	//! Compare with another address
	bool equals( pt::Address::Reference address );

	//! Get the TcpNodelay for the logical network
	int getTcpNodelayNet(); //ADDEDATCP

	//! Get the Thread
	int getThread(); //ADDEDATCP

	//! Set the TcpNodelay for the logical network
	void setTcpNodelayNet(int tcpNodelayNet); //ADDEDATCP

	//! Set the Thread
	void setThread(int thread); //ADDEDATCP

	//new 30/06/2011
	void setSocketReuseAddr(bool socketReuseAddr);
	bool getSocketReuseAddr();

	/*
	//! Compare with another address
	bool equals( pt::Address::Reference address ); //XDAQ31
	*/

	protected:
	
	toolbox::net::URL url_;
	std::string service_; //XDAQ31

        private:

	int tcpNodelayNet_; //ADDEDATCP
	int thread_; //ADDEDATCP

	//new 30/06/2011
	bool socketReuseAddr_;
};

}

}
#endif
