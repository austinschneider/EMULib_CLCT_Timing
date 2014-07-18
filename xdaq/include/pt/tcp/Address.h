// $Id: Address.h,v 1.3 2009/03/04 08:51:31 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_Address_h
#define _pt_tcp_Address_h

#include "pt/Address.h"
#include "toolbox/net/URL.h"
#include <netinet/in.h>

namespace pt
{
namespace tcp
{

class Address: public pt::Address
{
	public:
	
	//! Create address from url
	Address (const std::string  & url, const std::string& service);
	
	virtual ~Address ();
	
	//! Get the URL protocol, e.g. tcp
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

	bool isSocketBound();
	void bindSocket(int s); // s is the socket
	int getBoundSocket();

	protected:
	
	bool socketIsBound_;
	int socket_;
	toolbox::net::URL url_;
	std::string service_;
};

}
}

#endif
