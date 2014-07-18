// $Id: Endpoint.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_Endpoint_h_
#define xoap_Endpoint_h_

#include <string>

namespace xoap
{
/*! An opaque representation of an application endpoint. 
 *  Conceptually, an Endpoint object is the mapping of a logical name 
 *  (example, a URI) to a physical location, such as a URL. 
 *
 * For messaging using a provider that supports profiles, an application does not need to specify an endpoint when 
 * it sends a message because destination information will be contained in the profile-specific header. However, 
 * for point-to-point plain SOAP messaging, an application must supply an Endpoint object to the SOAPConnection 
 * method call to indicate the intended destination for the message. The subclass URLEndpoint can be used when an 
 * application wants to send a message directly to a remote party without using a messaging provider. 
 * 
 * The default identification for an Endpoint object is a URI. This defines what JAXM messaging providers need to 
 * support at minimum for identification of destinations. A messaging provider needs to be configured using a 
 * deployment-specific mechanism with mappings from an endpoint to the physical details of that endpoint. 
 *
 * Endpoint objects can be created using the constructor, or they can be looked up in a naming service. 
 * The latter is more flexible because logical identifiers or even other naming schemes (such as DUNS numbers) can 
 * be bound and rebound to specific URIs. 
 * There is no naming service included in XOAP.
 */
    
class Endpoint 
{
	public:
	
        /*! Constructs a Endpoint  object using the given identifier
         */
        Endpoint( const std::string& id);
	
        /*! Retrieves a string representation of this Endpoint object. This string is likely to be provider-specific,
            and programmers are discouraged from parsing and programmatically interpreting the contents of this string.
         */
        std::string toString();
        
        protected:
	
        /*! A string that identifies the party that this Endpoint object represents; a URI is the default.
         */
        std::string id_;
};

}
#endif
