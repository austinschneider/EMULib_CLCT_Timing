// $Id: SOAPFault.h,v 1.5 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPFault_h
#define xoap_SOAPFault_h

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOM.hpp>

#include "xoap/SOAPBodyElement.h"

namespace xoap
{

/*! An element in the SOAPBody object which contains error and/or status information.
    This information may relate to errors in the SOAPMessage object or to problems
    which are not related to the content of the message itself. Problems not related to 
    the message itself are generally errors in processing, such as the inability to
    communicate with an upstream server.
    This class provides member functions to set and retrieve the fault code and fault
    string. 

    A faultcode is intended to identify the fault and may be
    used by the software in further algorithmic processing.
    A faultstring is meant to provide a human readable explanation of the fault.
    For further explanation of faultcode and faultstring see the SOAP specification.
 */
class SOAPFault : public xoap::SOAPBodyElement 
{
    public:
	SOAPFault (DOMNode* node);
	
        /*! Retrieves the fault code of this SOAPFault object.
           \return a string with the fault code
         */
	std::string getFaultCode();
	
        /*! Retrieves the fault string of this SOAPFault object.
           \return a string with the fault string
         */
	std::string getFaultString();
	
        /*! Sets the fault code of this SOAPFault object.
           \param code - a string with the fault code to be set
         */
	void setFaultCode(const std::string& code)
		throw (xoap::exception::Exception);
	
        /*! Sets the fault string of this SOAPFault object.
           \param str - a string giving an explanation of the fault
         */
	void setFaultString(const std::string& str)
		throw (xoap::exception::Exception);
		
		
	SOAPElement addDetail()
		throw (xoap::exception::Exception);	
	
	SOAPElement getDetail()
		throw (xoap::exception::Exception);	
		
	bool hasDetail()
		throw (xoap::exception::Exception);		
};

}
#endif
