// $Id: SOAPElement.h,v 1.6 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPElement_h
#define xoap_SOAPElement_h

#include <xercesc/dom/DOM.hpp>

#include <string>
#include <vector>

XERCES_CPP_NAMESPACE_USE

#include "xoap/SOAPNode.h"
#include "xoap/SOAPName.h"
#include "xoap/exception/Exception.h"

namespace xoap
{

class SOAPElement;

/*! This class is the base class for all classes which represent SOAP objects. Thus, the
    classes SOAPBody, SOAPBodyElement, SOAPEnvelope, and SOAPHeader all inherit from this
    class.
 */
class SOAPElement: public xoap::SOAPNode 
{
    public:
        /*! \param element - a DOM_Node representation of the SOAPElement object. It is
                             passed to the constructor of the SOAPNode object.
         */
	SOAPElement(DOMNode* element);
	
        /*! Creates an attribute with the given name and value and adds it to
            this SOAPElement object.
           \param name - a SOAPName object with the name of the attribute
           \param value - a string giving the value of the attribute
         */
	void addAttribute(xoap::SOAPName& name, const std::string& value)
		throw (xoap::exception::Exception);
	
        /*! Creates a new SOAPElement object initialized with the given SOAPName object
            and adds it to this SOAPElement object.
           \param name - a SOAPName object containing the name of the new element
           \return the new SOAPElement object which has been added
         */
	xoap::SOAPElement addChildElement(xoap::SOAPName& name)
		throw (xoap::exception::Exception);
	
        /*! Creates a new SOAPElement object and adds it to this SOAPElement object.
           \param node - a DOM_Node representation of the child element which should
                         be added to this SOAPElement object
           \return the new SOAPElement object which has been added
         */
	xoap::SOAPElement addChildElement(DOMNode* node)
		throw (xoap::exception::Exception);
	
        /*! Adds the given text string to this SOAPElement object.
           \param value - a string with the text to be added
         */
	void addTextNode(const std::string& value)
		throw (xoap::exception::Exception);
	
        /*! Sets the text content of the SOAPElement. Equivalent to addTextNode() if
	    the SOAPElement has no text content. setTextContent() will overwrite an
	    existing text content node. addTextNode() would append a second text content
	    node if one is already existing.
           \param value - a string with the text to be added
         */
	void setTextContent(const std::string& value)
		throw (xoap::exception::Exception);

	/*! \returns the text content of a SOAP element */
	std::string getTextContent()
		throw (xoap::exception::Exception);

        /*! Retrieves the value of the attribute with the given name.
           \param name - a SOAPName object with the name of the attribute to be retrieved
           \return a string giving the value of the specified attribute
         */
	std::string getAttributeValue(xoap::SOAPName& name)
		throw (xoap::exception::Exception);
	
        /*! Retrieves all child elements of this SOAPElement object.
           \return a vector with the contents of this SOAPElement object
         */
	std::vector<xoap::SOAPElement> getChildElements();
	
        /*! Retrieves all child elements with the specified name.
           \param name - a SOAPName object with the name of the child elements which should be returned
           \return a vector with all elements in this SOAPElement object of the specified name
         */
	std::vector<xoap::SOAPElement> getChildElements(xoap::SOAPName& name);
	
        /*! Retrieves the name of this SOAPElement object.
            \return a SOAPName object containing the name of this SOAPElement object
         */
	xoap::SOAPName getElementName();
	
        /*! Retrieves a DOM_Node representation of this SOAPElement object.
            \return A DOM_Node representation of this SOAPElement object
         */
	DOMNode* getDOM();
	
	/*!
	* Adds a namespace declaration with the specified prefix and URI to this SOAPElement object.
	* Parameters:
	* prefix - a String giving the prefix of the namespace
	* uri - a String giving the uri of the namespace
	* Returns:
	* void
	* Throws:
	* SOAPException - if there is an error in creating the namespace	
	*/
	void addNamespaceDeclaration (const std::string& prefix, const std::string& uri)
		throw (xoap::exception::Exception);

	/*!
	 * Removes the namespace declaration corresponding to the given prefix.
	 * Parameters:
	 * prefix - a String giving the prefix for which to search
	 * Returns:
	 * void
	*/
	void removeNamespaceDeclaration (const std::string& prefix)
		throw (xoap::exception::Exception);
	
    protected:
    
    	void appendNodeWithPrefix (const std::string& name, const std::string& value)
		throw (xoap::exception::Exception);
};

}

#endif
