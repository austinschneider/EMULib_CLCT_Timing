// $Id: SOAPSerializer.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_SOAPSerializer_h_
#define xoap_SOAPSerializer_h_

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/TranscodingException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>

#include "xoap/exception/Exception.h"

XERCES_CPP_NAMESPACE_USE

#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>

namespace xoap
{

/*! This class serializes a SOAPMessage object. It is used internally in the XOAP
    library when writing a SOAP message to screen or to a file.
    The syntax is as follows: 
    - string soapString
    - SOAPSerializer s(soapString)
    - s.serialize(envelope_)

    The \e envelope_ is a DOM_Node representation of the SOAPEnvelope object.
    The entire SOAP message is contained in the \e soapString.
 */
class SOAPSerializer : public XMLFormatTarget 
{
    public:
    
        SOAPSerializer(std::string& s);
    
        ~SOAPSerializer();
	
	void serialize(DOMNode* node) throw (xoap::exception::Exception);
	
// -----------------------------------------------------------------------
//  Implementations of the format target interface
// -----------------------------------------------------------------------

    void writeChars(const XMLByte* const toWrite,
    			const unsigned int count,
			XMLFormatter* const formatter)
    {	
	stream_ += (char*) toWrite;
    }
    
    private:
	XMLFormatter*             gFormatter_;
 	char*			 gXmlFile;
 	bool			  gDoNamespaces;
 	bool			  gDoExpand;
 	XMLCh* 		  	  gEncodingName;
     	XMLFormatter::UnRepFlags  gUnRepFlags;
       	XMLFormatter*		  gFormatter;
	std::string&              stream_;
};

}

#endif
