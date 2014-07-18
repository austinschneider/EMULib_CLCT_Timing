// $Id: SOAPNode.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPNode_h
#define xoap_SOAPNode_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>

namespace xoap
{

class SOAPElement;

/*! A DOM representation of a node (element) in an XML document which provides
    tree manipulation methods. This class provides member functions to retrieve the value and parent
    element of a node, and to remove a node. It is inherited by
    the SOAPEnvelope, SOAPBody, SOAPBodyElement, and SOAPFault objects.
 */
class SOAPNode 
{
    public:
        /*!
           \param node - A DOM_Node representation of the SOAPNode object.
         */
	SOAPNode(DOMNode* node);
	
        /*! Returns the value of the first
            child of this SOAPNode object, if there is a child and its a text node.
            \return a string with the text of the first child of this SOAPNode object if (1) there is a child
                    and (2) the child is a text node
         */
	std::string getValue();
	
        /*! Retrieves the parent element of this SOAPNode object.
            \return the SOAPElement object which is the parent of this SOAPNode object
         */
	SOAPElement getParentElement();
	
        /*! Removes this SOAPNode object from the tree.
         */
	void detachNode();
	
        /*! Retrieves the DOM_Node representation of the SOAPNode object.
            \return a DOM_Node representation of the SOAPNode object
         */
	DOMNode* getDOMNode();
	
    protected:
        /*! A DOM_Node representation of the SOAPNode object. For internal use in this class.
         */
	DOMNode* node_;
};

}

#endif
