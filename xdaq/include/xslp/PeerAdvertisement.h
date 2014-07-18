// $Id: PeerAdvertisement.h,v 1.2 2008/07/18 15:28:50 gutleber Exp $
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xslp_PeerAdvertisement_h
#define _xslp_PeerAdvertisement_h

#include <string>
#include <map>

#include "xslp/exception/Exception.h"
#include "xslp/AdvertisementImpl.h"

namespace xslp {

//! This class wraps an advertisement and handles peer advertisements (advs), peergroup advs and pipe advs.
/*!
	For a PeerAdvertisement in SLP the following properties are stored:
	name - peer name
	description - textual description
	pid - peer id
	svc - service url used to converse with the peer
	
	The toString function will create a string as follows for this advertisement:
	
	service:peer:<svc>/<name> "(pid=<pid>)"
	
	Example:
	
	service:peer:http://myhost.org:40000/urn:xdaq-application:class=HelloWorld;instance=0 "(pid=<pid>)"
*/
class PeerAdvertisement: public xslp::AdvertisementImpl
{
	public:
	
	//! Minimal constructor. Create with "peer" name as it should appear in the SLP string and id
	//
  	//PeerAdvertisement ();
	
	
	//! Create a PeerAdvertisement from an SLP SAP string (SAP part service:peer:<sap>)
	//
	PeerAdvertisement (const std::string& source)
		throw (xslp::exception::Exception);
	
	~PeerAdvertisement ();
	
	//! Implementation dependent representation of the advertisement
	std::string toString();
	

};

}

#endif


