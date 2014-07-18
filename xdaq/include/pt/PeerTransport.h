// $Id: PeerTransport.h,v 1.8 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_PeerTransport_h
#define _pt_PeerTransport_h

#include <string>
#include <vector>
#include <map>

#include "pt/Listener.h"
#include "pt/Address.h"
#include "pt/exception/InvalidAddress.h"

namespace pt
{

typedef enum TransportTypeEnumerated
{
	Sender = 0,
	Receiver = 1,
	SenderReceiver = 2
} TransportType;

class PeerTransport
{
	public:
	virtual ~PeerTransport()
	{
	}

	/*! Returns the type of transport object implemented
	  *  pt::PeerTransport::Sender, pt::PeerTransport:Receiver or pt::PeerTransport::SenderReceiver (both)
	 */
	virtual TransportType getType() = 0;
	
	/*! Create an address object by providing a url. To create an address the associated 
	  * peer transport needs to be installed.
	  */
	virtual pt::Address::Reference createAddress( const std::string & url, const std::string & service ) 
		throw (pt::exception::InvalidAddress)  = 0;
		
	virtual pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress)  = 0;
	
	//! Returns the supported protocol
	//
	virtual std::string getProtocol() = 0;
	
	//! Tells which service type is implemented by this sender or receiver transport
	//
	virtual std::vector<std::string> getSupportedServices() = 0;
	
	//! Returns true is a given service is supported, false otherwise (e.g. "soap", "i2o")
	//
	virtual bool isServiceSupported(const std::string& service ) = 0;
	
};

}

#endif
