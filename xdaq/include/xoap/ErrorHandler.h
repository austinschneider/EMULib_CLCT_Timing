// $Id: ErrorHandler.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_ErrorHandler_h_
#define xoap_ErrorHandler_h_

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

#include <string>

XERCES_CPP_NAMESPACE_USE

namespace xoap
{

class ErrorHandler : public DOMErrorHandler
{
	bool hasErrors_;
	std::string msg_;

	public:

	ErrorHandler();

	bool handleError (const DOMError &domError);

	bool hasErrors();

	void reset();

	std::string getErrorMessage();

};

}
#endif
