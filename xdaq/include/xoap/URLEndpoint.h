// $Id: URLEndpoint.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_URLEndpoint_h_
#define xoap_URLEndpoint_h_

#include "xoap/Endpoint.h"

namespace xoap
{
	/*! A special case of the Endpoint class used for simple applications that want 
	  * to communicate directly with another SOAP-based application in a point-to-point fashion 
	  * instead of going through a messaging provider. 
	  * A URLEndpoint object contains a URL, which is used to make connections to the remote party. 
	  * A standalone client can pass a URLEndpoint object to the SOAPConnection method call 
	  * to send a message synchronously. 
	  */
	class URLEndpoint: public Endpoint 
	{
		public:

        	/*! Constructs a new URLEndpoint object using the given URL. */
        	URLEndpoint( const std::string& id);

        	/*!Gets the URL associated with this URLEndpoint object.  */
        	std::string getURL();
	};
}

#endif
