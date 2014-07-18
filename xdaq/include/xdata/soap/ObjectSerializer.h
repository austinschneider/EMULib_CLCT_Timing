// $Id: ObjectSerializer.h,v 1.3 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_soap_ObjectSerializer_h_
#define _xdata_soap_ObjectSerializer_h_

#include <xercesc/dom/DOM.hpp>

#include "xdata/Serializable.h"
#include "xdata/ObjectSerializer.h"
#include "xdata/exception/Exception.h"
#include "xdata/Serializer.h"


XERCES_CPP_NAMESPACE_USE

namespace xdata {
namespace soap {

class ObjectSerializer : public xdata::ObjectSerializer 
{
	public:
	virtual ~ObjectSerializer()
	{
	}

	virtual DOMElement * exportAll( xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMElement * targetNode) = 0;
	
	virtual void exportQualified (xdata::Serializer * serializer,  xdata::Serializable * serializable,
	DOMNode* queryNode, DOMElement* resultNode) throw (xdata::exception::Exception) = 0;			
	
	virtual void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMNode* targetNode) throw (xdata::exception::Exception) = 0;
};

}}

#endif
