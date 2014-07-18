// $Id: SOAPPart.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPPart_h
#define xoap_SOAPPart_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

namespace xoap
{

class SOAPEnvelope;

/*! All SOAP messages are required to have a SOAP part, so when a SOAPMessage object is created,
it will automatically have a SOAPPart object. Its contents should be in XML format.

The SOAPPart object of a SOAPMessage object can be accessed by calling the member function
\e SOAPMessage.getSOAPPart(). From the SOAPPart object the SOAPEnvelope object can be retrieved:

- SOAPMessage message;
- SOAPPart soapPart = message.getSOAPPart();
- SOAPEnvelope envelope = soapPart.getSOAPEnvelope();
*/
class SOAPPart 
{
    public:

       /*! 
          \param envelope - A DOM_Node representation of the SOAPEnvelope object
        */
	SOAPPart (DOMNode* envelope);
	
        /*! Returns the SOAPEnvelope object of this SOAPPart object. When the 
            SOAPEnvelope has been obtained, its contents (its SOAPBody object and 
            its SOAPHeader object) may be obtained.
            \return the SOAPEnvelope object of this SOAPPart object
         */
	SOAPEnvelope getEnvelope();
	
    protected:
    
        /*! A DOM_Node representation of a SOAPEnvelope object. This parameter is set when the
            SOAPPart object is created, which happens by default when the SOAPMessage object is
            created.
         */
	DOMNode* envelope_;
};

}

#endif
