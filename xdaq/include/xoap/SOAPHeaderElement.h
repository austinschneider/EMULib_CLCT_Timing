// $Id: SOAPHeaderElement.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPHeaderElement_h
#define xoap_SOAPHeaderElement_h

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include "xoap/SOAPElement.h"

namespace xoap
{

/*! An object representing the contents in the SOAP header part of the SOAP envelope. 
The immediate children of a SOAPHeader object can be represented only as SOAPHeaderElement objects.
 
 A SOAPHeaderElement object can have other SOAPElement objects as its children. 
 */
class SOAPHeaderElement: public SOAPElement 
{
    public:
        /*!
           \param node - a DOM_Node representation of the SOAPHeaderElement object. The DOM_Node
                         is passed to the constructor of the SOAPNode object.
         */
	SOAPHeaderElement(DOMNode* node);
	
	
	/*!Returns the uri of the actor associated with this SOAPHeaderElement object.
	 */
	std::string getActor();
	    
	/*!Returns whether the mustUnderstand attribute for this SOAPHeaderElement object is turned on.
	*/
	bool getMustUnderstand();
	
	
	/*!Sets the actor associated with this SOAPHeaderElement object to the specified actor.
	*/
	void setActor(const std::string & URI) ;
	
	/*!Sets the mustUnderstand attribute for this SOAPHeaderElement object to be on or off.
	*/
	void setMustUnderstand(bool mustUnderstand);
};
	
}
#endif
