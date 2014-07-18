// $Id: XMLDOM.h,v 1.8 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_XMLDOM_h_
#define _xdata_XMLDOM_h_

#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/TranscodingException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <string>
#include <stdlib.h>

#include "xdata/exception/Exception.h"

XERCES_CPP_NAMESPACE_USE

namespace xdata {

class XMLDOMErrorHandler : public DOMErrorHandler
{
	public:
		XMLDOMErrorHandler();
		bool handleError (const DOMError &domError);
		bool hasErrors();
		void resetErrors();
		std::string getErrors();
	protected:
	
	bool hasErrors_;	
	std::string errorMessages_;
	private:
	XMLDOMErrorHandler(const XMLDOMErrorHandler & );
	void operator=(const XMLDOMErrorHandler & );
	
};

class XMLDOMLoader {
		
	
	public:
	
	//
	//     valScheme = AbstractDOMParser::Val_Never
        //       valScheme = AbstractDOMParser::Val_Auto
        //       valScheme = AbstractDOMParser::Val_Always
	//
	XMLDOMLoader( AbstractDOMParser::ValSchemes valScheme = AbstractDOMParser::Val_Auto);
	
	~XMLDOMLoader();
	
	
	DOMDocument * load(const std::string & url) throw (xdata::exception::Exception);

	void release(DOMDocument* doc);
		
	protected:
	
	DOMBuilder        *parser;
	xdata::XMLDOMErrorHandler errorHandler;
};


class XMLDOMSerializer : public XMLFormatTarget 
{
    public:
    
        XMLDOMSerializer(std::string& s, bool escapes = false);
    
        ~XMLDOMSerializer();
	
	void serialize(DOMNode* node);
	

    void writeChars(const XMLByte* const toWrite,
    			const unsigned int count,
			XMLFormatter* const formatter)
    {	
	stream_ += (char*) toWrite;
    }
    
    private:
    	// helper to output n space characters
  	void chTab(unsigned long n, XMLFormatter* f);
    
	XMLFormatter*             	gFormatter_;
 	char*				gXmlFile	;
 	bool			  	gDoNamespaces ;
 	bool			  	gDoExpand	;
 	XMLCh* 		  	  	gEncodingName ;
     	XMLFormatter::UnRepFlags  	gUnRepFlags	;
	std::string&			stream_       ;
	XMLFormatter::EscapeFlags 	escapeStyle_;	
	unsigned long			indent_;	
};

}

#endif
