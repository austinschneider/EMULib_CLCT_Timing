// $Id: Channel.h,v 1.2 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_Channel_h_
#define _pt_tcp_Channel_h_

#include <netinet/in.h>

#include "pt/tcp/Address.h"
#include "pt/tcp/exception/Exception.h"

namespace pt
{
namespace tcp
{

class Channel 
{
	public:
	
	Channel(pt::Address::Reference address) throw (pt::tcp::exception::Exception);
		
	virtual ~Channel();
	
	//! connect channel according configuration
	virtual void connect() throw (pt::tcp::exception::Exception) = 0;
	
	//! disconnect but keep channel alive
	virtual void disconnect() throw (pt::tcp::exception::Exception) = 0;
	
	//! receive len characters into buf
	virtual size_t receive(char * buf ,size_t len ) throw (pt::tcp::exception::Exception) = 0;
	
	//! send buffer of given lenght
	virtual void send(const char * buf, size_t len) throw (pt::tcp::exception::Exception) = 0;
	
	//! Close a connection definitely
	virtual void close() throw (pt::tcp::exception::Exception) = 0;
		
	//! Check if the connection is up
	virtual bool isConnected() throw (pt::tcp::exception::Exception) = 0;
		
	protected:
	
	struct sockaddr_in sockaddress_;
	socklen_t sockaddressSize_;
	int socket_;
};

}
}

#endif
