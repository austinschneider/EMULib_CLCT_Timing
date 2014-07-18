// $Id: MessageFactory.h,v 1.10 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_MessageFactory_h_
#define _xoap_MessageFactory_h_

#include "xoap/MessageReference.h"
#include "xoap/exception/Exception.h"

namespace xoap
{

	/*! Create an empty SOAP message and return a reference that points to the empty message. */
	MessageReference createMessage();

	/*! Create a SOAP message from a character buffer.
	  * \param buf, a text buffer that contains a SOAP message in XML ASCII or UTF-8 format. 
	  * \param size, the size of the SOAP message contained in \param buf in bytes
	  */
	MessageReference createMessage(char* buf, int size) 
		throw (xoap::exception::Exception);

	/*! Create a SOAP message from a DOM node.
	  *  \param node, contains a DOM document that corresponds to a SOAP message
	  */
	MessageReference createMessage(DOMNode* node) 
		throw (xoap::exception::Exception);
		
	/*! Create a SOAP message from a text file
	  * \param filename, a text file that contains a SOAP message in XML ASCII or UTF-8 format.
	  */
	MessageReference createMessage(const std::string& filename) 
		throw (xoap::exception::Exception);

	/*! Create a new message from the SOAP message contained in \param msg		
	  */
	MessageReference createMessage(MessageReference msg)
		throw (xoap::exception::Exception);


	
}

#endif
