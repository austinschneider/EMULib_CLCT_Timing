// $Id: HTTPURLConnection.h,v 1.4 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_HTTPURLConnection_h_
#define xoap_HTTPURLConnection_h_

#include "xoap/exception/HTTPException.h"
#include <string>

namespace xoap
{

class HTTPURLConnection 
{
	public:
	
	HTTPURLConnection() throw (xoap::exception::HTTPException);
	~HTTPURLConnection();
	
	//! receive  from established HTTP connection and returns data into a BufRef	
	std::string receiveFrom() throw (xoap::exception::HTTPException);
	
	//! send data to an established HTTP connection
	void sendTo
		(
			char * path,
			char * host,
			unsigned int port,
			const char * buf,
			size_t len
		) 
		throw (xoap::exception::HTTPException);
		
	//! send data to an established HTTP connection
	void sendTo
		(
			char * path, 
			char * host, 
			unsigned int port, 
			const char * buf, 
			size_t len,
			const char* soapAction
		) 
		throw (xoap::exception::HTTPException);
	

	//! close connection
	void close();
	
	//! connect to URL 
	void connect(const std::string& host, unsigned int port) throw (xoap::exception::HTTPException);
	
	//! send buffer of given lenght
	void send(const char * buf, size_t len)  throw (xoap::exception::HTTPException);

	protected:
	
	//! receive len characters into buf
	ssize_t receive(char * buf , size_t len )  throw (xoap::exception::HTTPException);
	
	
	//! Helper to re-creating a socket
	void open() throw (xoap::exception::HTTPException);
		
       	std::string extractMIMEBoundary(const char * buf , size_t size) throw (xoap::exception::HTTPException);
       	
	void writeHttpPostMIMEHeader
		(
			char * path,
			char * host,
			unsigned int port,
			std::string & boundaryStr,
			size_t len
		) 
		throw (xoap::exception::HTTPException);
	
	void writeHttpPostMIMEHeader
		(
			char * path,
			char * host,
			unsigned int port,
			std::string & boundaryStr,
			size_t len,
			const char* soapAction
		) 
		throw (xoap::exception::HTTPException);
		
	void writeHttpPostHeader
	(
		char * path,
		char * host,
		unsigned int port,
		size_t len,
		const char* soapAction
	) 
	throw (xoap::exception::HTTPException);
       	
	void writeHttpPostHeader
		(
			char * path,
			char * host,
			unsigned int port,
			size_t len
		) 
		throw (xoap::exception::HTTPException);

	int socket_;
};

}
#endif
