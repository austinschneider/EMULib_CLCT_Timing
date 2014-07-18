// $Id: Transmitter.h,v 1.2 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_Transmitter_h_
#define _pt_tcp_Transmitter_h_

#include <netinet/in.h>

#include "pt/tcp/Address.h"
#include "pt/tcp/exception/Exception.h"
#include "pt/tcp/Channel.h"

namespace pt
{
namespace tcp
{

const unsigned int MaxRetry = 3;

class Transmitter : public tcp::Channel
{
	public:
	
	Transmitter(pt::Address::Reference remote, pt::Address::Reference local) throw (pt::tcp::exception::Exception);
		
	~Transmitter();
	
	//! connect channel according configuration
	void connect() throw (pt::tcp::exception::Exception);
	
	//! disconnect but keep channel alive
	void disconnect() throw (pt::tcp::exception::Exception);
	
	//! receive len characters into buf
	size_t receive(char * buf ,size_t len ) throw (pt::tcp::exception::Exception);
	
	//! send buffer of given lenght
	void send(const char * buf, size_t len) throw (pt::tcp::exception::Exception);
	
	//! Close a connection definitely
	void close() throw (pt::tcp::exception::Exception);
		
	//! Check if the connection is up
	bool isConnected() throw (pt::tcp::exception::Exception);
	
	bool isConnected_;
	unsigned int retry_;
};


}
}

#endif
