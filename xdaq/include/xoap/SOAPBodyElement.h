// $Id: SOAPBodyElement.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPBodyElement_h
#define xoap_SOAPBodyElement_h

#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

#include "xoap/SOAPElement.h"

namespace xoap
{
/*! SOAPBodyElement objects are the contents of a SOAPBody object. A SOAPFault object
    is a SOAPBodyElement object which has been defined.

    A SOAPBodyElement object may be added to the already existing SOAPBody object
    by the following procedure:
    - SOAPMessage message;
    - SOAPPart soapPart = message.getSOAPPart();
    - SOAPEnvelope envelope = soapPart.getEnvelope();
    - SOAPBody body = envelope.getBody();
    - SOAPName name = envelope.createName(myLocalName, nsPrefix, nsURI);
    - SOAPBodyElement bodyElement = body.addBodyElement(name);
 */
class SOAPBodyElement : public xoap::SOAPElement 
{
    public:
        /*!
           \param node - a DOM_Node representation of the SOAPBodyElement object. The DOM_Node
                         is passed to the constructor of the SOAPNode object.
         */
	SOAPBodyElement(DOMNode* node);
};

}
#endif
