// $Id: domutils.h,v 1.7 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_domutils_h_
#define _xoap_domutils_h_

#include <string>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMException.hpp>
#include "xoap/exception/Exception.h"

XERCES_CPP_NAMESPACE_USE

namespace xoap
{
	//! Return the value of an attribute name that belongs to the given node
	std::string getNodeAttribute(DOMNode* node, const std::string & name);
	
	/*! Simple dump of a DOM into a string
		This simple routine does not cover
		the use of special characters.
	*/
	void dumpTree(DOMNode* node, std::string & str);
	
	/*! Append a simple node with name and text value to the target node.
		Appending tag="example", value="1" to node <target> 
		results in:
		<target>
		<example> 1 </example>
		</target>
		
		The newly created tag element is returned.
	*/
	// DOMElement* appendNode ( DOMNode* target, const std::string& tag, const std::string& value);
	
	/*! Helper function that converts a Xerces XMLCh string representation into a standard C++ string */
	std::string XMLCh2String (const XMLCh* ch);

	/*! Helper class that converst a standard C++ string into a Xerces XMLCh string representation */
	class XStr
	{
		public :
		    XStr (const char* const toTranscode);
		    XStr (std::string toTranscode);     
		    ~XStr();
		    const XMLCh* unicodeForm() const;
		    operator const XMLCh*();

		private :		 
		    XMLCh*   fUnicodeForm; // the Unicode XMLCh format of the string.
	};
}

#endif
