// $Id: EndpointAdvertisement.h,v 1.2 2008/07/18 15:28:50 gutleber Exp $
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xslp_EndpointAdvertisement_h
#define _xslp_EndpointAdvertisement_h

#include <string>
#include <map>

#include "xslp/exception/Exception.h"
#include "xslp/AdvertisementImpl.h"

namespace xslp {

//! This class wraps an advertisement and handles peer advertisements (advs), peergroup advs and pipe advs.
/*!
	For a PeerAdvertisement in SLP the following properties are stored:
	name - peer name (currently ignored)
	description - textual description
	address - address URL of this endpoint
	
	The toString function will create a string as follows for this advertisement:
	
	service:endpoint:<address>
	
	Example:
	
	service:peer:http://myhost.org:40000
	service:peer:tcp://myhost.org:50000;network=secondTCP
*/
class EndpointAdvertisement: public xslp::AdvertisementImpl
{
	public:
	
	EndpointAdvertisement();
	
  	EndpointAdvertisement (const std::string& source)
		throw (xslp::exception::Exception);
	
	~EndpointAdvertisement ();
	
	//! Implementation dependent representation of the advertisement
	std::string toString();
	

};

}

#endif


