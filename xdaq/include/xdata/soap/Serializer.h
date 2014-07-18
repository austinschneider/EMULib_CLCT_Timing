// $Id: Serializer.h,v 1.8 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_serializer_soap_Serializer_h_
#define _xdata_serializer_soap_Serializer_h_

#include <xercesc/dom/DOM.hpp>

#include "xdata/exception/Exception.h"
#include "xdata/soap/ObjectSerializer.h"
#include "xdata/Serializer.h"

XERCES_CPP_NAMESPACE_USE



namespace xdata {
namespace soap {

class Serializer : public xdata::Serializer 
{	
	public:
	
	Serializer();
	
	/*! Export the data type into an existing
	DOM document. The target node may be exchanged
	if necessary and a valid reference to the place
	at which the data type has been inserted is returned.
	*/
	DOMElement * exportAll
		(
			xdata::Serializable * s,
			DOMElement * targetNode,
			bool createNS = false
		) 
		throw (xdata::exception::Exception);

	/*! Export the data type into an existing DOM document.
	The subtree of this existing document, given as
	a DOM_Node parameter n contains the tags that are
	expected to be written. E.g. if a structured data
	type is exported, the existing DOM tree provided
	serves as a template, indicating, which elements
	of the structure should be exported.
	*/
	void exportQualified
		(
			xdata::Serializable * s,
			DOMNode* queryNode,
			DOMElement* resultNode,
			bool createNS = false
		) 
		throw (xdata::exception::Exception);
	
	/*! Creates an in memory representation of the
	data type from an XML document given as
	a DOM_Node n
	*/
	void import
		(
			xdata::Serializable * s,
			DOMNode* targetNode
		) 
		throw (xdata::exception::Exception);
};



}}

#endif

