// $Id: SOAPConnection.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPConnection_h_
#define xoap_SOAPConnection_h_

#include <string>

#include "xoap/Endpoint.h"
#include "xoap/SOAPMessage.h"
#include "xoap/SOAPPart.h"
#include "xoap/AttachmentPart.h"
#include "xoap/HTTPURLConnection.h"
#include "xoap/exception/Exception.h"

namespace xoap
{
/*! A point-to-point connection that a client can use for sending messages directly to a remote 
    party (represented by a URL, for instance). 

 
    A SOAPConnection object can be used to send messages directly to a URL following the request/response 
    paradigm. That is, messages are sent using the method call, which sends the message and then waits until it 
    gets a reply. 
    
    
    E.g.
    Set the destination
    
    URLEndpoint destination = 
              new URLEndpoint("http://localhost:40000/");
    Send the message
    
    SOAPMessage reply = connection.call(message, destination);
*/
    
class SOAPConnection 
{
	public:
        /*! Constructs a SOAPConnection object.
         */
        SOAPConnection();
        /*! Sends the given message to the specified endpoint and blocks until it has returned the 
            response.

            Parameters:
            \request - the SOAPMessage object to be sent
            \endpoint - an Endpoint that identifies where the message should be sent.
            \returns Returns the SOAPMessage object that is the response to the message that was sent
            \throw SOAPException - if there is a SOAP error
	    \throw HTTPException - if there is a HTTP error
         */ 
        xoap::SOAPMessage call(xoap::SOAPMessage & message, Endpoint & endpoint) throw (xoap::exception::Exception);

        protected:
	
	HTTPURLConnection httpURLConnection_;
};

}

#endif
