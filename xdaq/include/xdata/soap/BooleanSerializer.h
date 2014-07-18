// $Id: BooleanSerializer.h,v 1.3 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_soap_BooleanSerializer_h_
#define _xdata_soap_BooleanSerializer_h_

#include "xdata/soap/ObjectSerializer.h"
#include "xdata/Boolean.h"

namespace xdata {
namespace soap {

class BooleanSerializer : public xdata::soap::ObjectSerializer  
{	
	public:
	virtual ~BooleanSerializer();

	std::string type() const;
	
	DOMElement * exportAll( xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMElement * targetNode);	
	void exportQualified (xdata::Serializer * serializer,  xdata::Serializable * serializable,
	DOMNode* queryNode, DOMElement* resultNode) throw (xdata::exception::Exception);
	void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMNode* targetNode) throw (xdata::exception::Exception);
};

}}

#endif
