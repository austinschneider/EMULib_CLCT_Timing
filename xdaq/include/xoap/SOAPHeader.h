// $Id: SOAPHeader.h,v 1.7 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPHeader_h
#define xoap_SOAPHeader_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>

#include "xoap/SOAPHeaderElement.h"
#include "xoap/SOAPFault.h"
#include "xoap/exception/Exception.h"

namespace xoap
{

/*! A representation of the SOAP header element. A SOAP header element consists of XML data 
   that affects the way the application-specific content is processed by the message provider. 
   For example, transaction semantics, authentication information, and so on, can be specified 
   as the content of a SOAPHeader object. A SOAPEnvelope object contains an empty
    SOAPHeader object by default. If the SOAPHeader object, which is optional, is not needed, 
    it can be retrieved and deleted with the following line of code. The variable se is a 
    SOAPEnvelope object.
    
    	se.getHeader().detachNode();
	
     A SOAPHeader object is created with the SOAPEnvelope method addHeader. This method, 
     which creates a new header and adds it to the envelope, may be called only after the 
     existing header has been removed.
        
	se.getHeader().detachNode();
        SOAPHeader sh = se.addHeader();

    A SOAPHeader object can have only SOAPHeaderElement objects as its immediate children. 
    The method addHeaderElement creates a new HeaderElement object and adds it to the
     SOAPHeader object. In the following line of code, the argument to the method 
     addHeaderElement is a Name object that is the name for the new HeaderElement object. 
       
     	SOAPHeaderElement shElement = sh.addHeaderElement(name);
 */
class SOAPHeader : public xoap::SOAPElement 
{
    public:
        /*!
            \param node - a DOM_Node representation of the SOAPHeader object. This DOM_Node is
                          passed to the constructor of the SOAPHEader object.
         */
	SOAPHeader(DOMNode* node);
	
         /*! Creates a new SOAPHeaderElement object initialized with the specified name and adds it to this 
	 SOAPHeader object
           \param name - a SOAPName object with the name of the SOAPHeaderElement object
           \return the SOAPHeaderElement object
         */
	xoap::SOAPHeaderElement addHeaderElement(xoap::SOAPName & name)
		throw (xoap::exception::Exception);
	
	void removeHeaderElements(const std::string & namespaceURI)
		throw (xoap::exception::Exception);
	
	void removeHeaderElement(xoap::SOAPName & name)
		throw (xoap::exception::Exception);	
	
	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object that have the the
	 specified actor.
	*/
	std::vector<xoap::SOAPHeaderElement> examineHeaderElements(const std::string & actorURI)
		throw (xoap::exception::Exception);
		
	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object that match the the
	 specified name.
	*/
	std::vector<xoap::SOAPHeaderElement> examineHeaderElements(xoap::SOAPName& name)
		throw (xoap::exception::Exception);
	
	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object that have the 
	the specified actor and detaches them from this SOAPHeader object. 
	*/
	std::vector<xoap::SOAPHeaderElement> extractHeaderElements(const std::string & actor)
		throw (xoap::exception::Exception); 
		
	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object 
	*/
	std::vector<xoap::SOAPHeaderElement> examineHeaderElements()
		throw (xoap::exception::Exception);
	
	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object 
	 according the specified namespace URI
	*/	
	std::vector<xoap::SOAPHeaderElement> examineHeaderElementsByNamespace(const std::string & uri)
		throw (xoap::exception::Exception);

	/*! Returns a list of all the SOAPHeaderElement objects in this SOAPHeader object 
	*/
	std::vector<xoap::SOAPHeaderElement> extractHeaderElements()
		throw (xoap::exception::Exception); 
};

}

#endif
