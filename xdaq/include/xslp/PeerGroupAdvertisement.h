// $Id: PeerGroupAdvertisement.h,v 1.2 2008/07/18 15:28:50 gutleber Exp $
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xslp_PeerGroupAdvertisement_h
#define _xslp_PeerGroupAdvertisement_h

#include <string>
#include <map>

#include "xslp/exception/Exception.h"
#include "xslp/AdvertisementImpl.h"

namespace xslp {

//! This class wraps an advertisement and handles peer advertisements (advs), peergroup advs and pipe advs.
/*!
	For a PeerGroupAdvertisement in SLP the following properties are stored:
	name - group name
	description - textual description
	gid - group id
	svc - Service URL of the group, by default: http://localhost
	
	The toString function will create a string as follows for this advertisement:
	
	service:group:<svc>/<name> "(gid=<gid>)"
	
	Example:
	
	service:peer:http://localhost/DepartmentPH "(gid=<pid>)"
*/
class PeerGroupAdvertisement: public xslp::AdvertisementImpl
{
	public:
	
	PeerGroupAdvertisement();
	
  	PeerGroupAdvertisement (const std::string& source)
		throw (xslp::exception::Exception);
	
	~PeerGroupAdvertisement ();
	
	//! Implementation dependent representation of the advertisement
	std::string toString();

};

}

#endif


