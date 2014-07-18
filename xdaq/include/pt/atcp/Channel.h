// $Id: Channel.h,v 1.1 2007/03/31 14:23:31 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_Channel_h_
#define _atcp_Channel_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include <netinet/in.h>

#include "pt/atcp/Address.h"
#include "pt/atcp/exception/Exception.h"

namespace pt {
namespace atcp
{

class Channel 
{
	public:
	
	Channel(pt::Address::Reference address) throw (pt::atcp::exception::Exception);
		
	virtual ~Channel();
	
	//! connect channel according configuration
	virtual void connect() throw (pt::atcp::exception::Exception) = 0;
	
	//! disconnect but keep channel alive
	virtual void disconnect() throw (pt::atcp::exception::Exception) = 0;
	
	//! receive len characters into buf
	virtual int receive(char * buf ,int len ) throw (pt::atcp::exception::Exception) = 0;
	//! receive non blocking len characters into buf
	virtual int receiveNonBlocking(char * buf ,int len ) throw (pt::atcp::exception::Exception) = 0; //ADDEDATCP
	
	//! send buffer of given lenght
	virtual void send(const char * buf, int len) throw (pt::atcp::exception::Exception) = 0;
	
	//! send non blocking buffer of given lenght
	virtual int sendNonBlocking(const char * buf, int len) throw (pt::atcp::exception::Exception) = 0; //ADDEDATCP
	
	//! Close a connection definitely
	virtual void close() throw (pt::atcp::exception::Exception) = 0;
		
	//! Check if the connection is up
	virtual bool isConnected() throw (pt::atcp::exception::Exception) = 0;
		
	protected:
	
	struct sockaddr_in sockaddress_;
	socklen_t sockaddressSize_;
	int socket_;
};


}

}
#endif
