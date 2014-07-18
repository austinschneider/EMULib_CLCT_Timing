// $Id: SOAPBody.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPBody_h
#define xoap_SOAPBody_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>

#include "xoap/SOAPBodyElement.h"
#include "xoap/SOAPFault.h"
#include "xoap/exception/Exception.h"

namespace xoap
{

/*! An object which contains SOAPBodyElement objects. A SOAPBodyElement object
    consists of XML data which is the actual application-specific content that
    should be processed.
  
    A SOAPFault object carries status and/or error information, and is an example
    of a SOAPBodyElement object.

    A SOAPBodyElement object may be added to the already existing SOAPBody object
    by the following procedure:
    - SOAPMessage message;
    - SOAPPart soapPart = message.getSOAPPart();
    - SOAPEnvelope envelope = soapPart.getEnvelope();
    - SOAPBody body = envelope.getBody();
    - SOAPName name = envelope.createName(myLocalName, nsPrefix, nsURI);
    - SOAPBodyElement bodyElement = body.addBodyElement(name);

    The SOAPBody object may  be replaced using the following procedure:
    - envelope.getBody().detachNode();
    - envelope.addBody();
 */
class SOAPBody : public xoap::SOAPElement 
{
    public:
        /*!
            \param node - a DOM_Node representation of the SOAPBody object. This DOM_Node is
                          passed to the constructor of the SOAPNode object.
         */
	SOAPBody(DOMNode* node);
	
        /*! Creates a SOAPBodyElement object and adds it to this SOAPBody object.
           \param name - a SOAPName object with the name of the SOAPBodyElement object
           \return the SOAPBodyElement object
         */
	xoap::SOAPBodyElement addBodyElement(xoap::SOAPName & name)
		throw (xoap::exception::Exception);
	
        /*! Creates a SOAPFault object and adds it to this SOAPBody object.
            \return the SOAPFault object
         */
	xoap::SOAPFault addFault() throw (xoap::exception::Exception);
	
        /*! Retrieves the SOAPFault object if it exists.
	    Otherwise an exception is thrown.
            \return the SOAPFault object of this SOAPBody object
            \throw string - if the SOAPBody object does not contain a SOAPFault object
	 */ 
	xoap::SOAPFault getFault() throw (xoap::exception::Exception);
	
	/*! Tells whether or not a SOAPFault object exists in this SOAPBody object.
            \return \e true if this SOAPBody object contains a SOAPFault object and \e false otherwise.
	*/
	bool hasFault();
};

}
#endif
