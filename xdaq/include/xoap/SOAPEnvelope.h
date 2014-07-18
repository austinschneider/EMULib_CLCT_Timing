// $Id: SOAPEnvelope.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPEnvelope_h
#define xoap_SOAPEnvelope_h

#include <string>

#include "xoap/SOAPElement.h"
#include "xoap/SOAPBody.h"
#include "xoap/SOAPHeader.h"
#include "xoap/exception/Exception.h"

XERCES_CPP_NAMESPACE_USE

namespace xoap
{

/*! The container of the SOAPHeader object and the SOAPBody object. When a SOAPMessage object
    is created, it by default contains a SOAPPart object, which contains a SOAPEnvelope object.

    The SOAPBody object can be accessed by calling the member function getBody():
    - SOAPMessage message;
    - SOAPPart soapPart = message.getSOAPPart();
    - SOAPEnvelope envelope = soapPart.getEnvelope();
    - SOAPBody body = envelope.getBody();

    The SOAPBody object of a SOAPEnvelope object may be changed by first deleting the current
    SOAPBody object, and then adding a new SOAPBody object:
    - envelope.getBody().detachNode();
    - envelope.addBody();    

    The detachNode() member function is a member function of the SOAPNode class which is inherited
    by the SOAPEnvelope class via the SOAPElement class (see the inheritance diagram above).

    Note that a SOAPEnvelope may only have one SOAPBody at a time.
 */
class SOAPEnvelope : public xoap::SOAPElement 
{
    public:
        /*!
            \param node - a DOM_Node representation of the SOAPEnvelope object.
                          This DOM_Node is passed to the constructor of the SOAPNode object.
         */
	SOAPEnvelope(DOMNode* node);
	
        /*! Creates a SOAPName object initialized with the given name.

            \param name - a string giving the name of the object.

            \return a SOAPName object initialized with the given name
         */
	xoap::SOAPName createName (const std::string& name);
	
         /*! Creates a SOAPName object initialized with the given local name, namespace, and namespace URI.
            \param name - a string giving the local name
            \param ns - a string giving the namespace
            \param uri - a string giving the URI of the namespace
            \return a SOAPName object initialized with the given local name, namespace, and namespace URI
         */
	xoap::SOAPName createName (const std::string& name, const std::string& ns, const std::string& uri);
	
        /*! Returns the SOAPBody object associated with this SOAPEnvelope object. When a SOAPMessage
            object is created, it by default contains a SOAPEnvelope object which again contains an
            empty SOAPBody object. Thus, the method getBody() will always return a SOAPBody object unless
            the SOAPBody object has been removed.
            \return the SOAPBody object of this SOAPEnvelope object
            \throw SOAPException - if no SOAPBody object has been found.
         */
	xoap::SOAPBody getBody() throw (xoap::exception::Exception);
	
        /*! Creates a SOAPBody object and adds it to this SOAPEnvelope object. Note that a SOAP envelope must
            only contain one SOAPBody object. Thus, this method should only be called after the initial SOAPBody
            object has been removed (see the example above).
            \return the created SOAPBody object
            \throw SOAPException - if this SOAPEnvelope object already contains a valid
                   SOAPBody object
         */
	xoap::SOAPBody addBody() throw (xoap::exception::Exception);
	
	
	 /*! 
            \return true  if this SOAPEnvelope object contains an header, false otherwise
         */
	bool  hasHeader();
	
	 /*! 
            \return the SOAPHeader object for this SOAPEnvelope object
            \throw if no SOAPHeader object has been found
         */
	xoap::SOAPHeader getHeader() throw (xoap::exception::Exception);
	
	/*! 
            \create a SOAPHeader object and sets it as the SOAPHeader object of this SOAPEnvelope
            \throw SOAPException - if this SOAPEnvelope object already contains a valid
                   SOAPHeader object
         */
	xoap::SOAPHeader addHeader() throw (xoap::exception::Exception);
};

}
#endif
