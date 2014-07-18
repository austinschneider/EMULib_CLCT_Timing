// $Id: IntegerSerializer.h,v 1.3 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_soap_IntegerSerializer_h_
#define _xdata_soap_IntegerSerializer_h_

#include <xercesc/dom/DOM.hpp>
#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/soap/ObjectSerializer.h"
#include "xdata/soap/Serializer.h"
#include "xdata/XStr.h"
#include "xdata/Integer.h"

XERCES_CPP_NAMESPACE_USE

namespace xdata {
namespace soap {

class IntegerSerializer : public xdata::soap::ObjectSerializer  
{	
	public:
	virtual ~IntegerSerializer();

	std::string type()  const;
	DOMElement *  exportAll(xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMElement * targetNode);
	void exportQualified (xdata::Serializer * serializer,  xdata::Serializable * serializable,
	DOMNode* queryNode, DOMElement* resultNode) throw (xdata::exception::Exception);
	void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, DOMNode* targetNode) throw (xdata::exception::Exception);
	
	/* !!!!!!!!!!!!   THIS IS THE NEXT STEP AFTER WE HAVE CREATED THE REGRESSION TESTS  !!!!!!!!!!!!!!!
	
	std::string toString (long int * value) throw (xdata::exception::Exception)
	{
		char tmp[255];
		sprintf (tmp, "%d", value);
		return tmp;
	}

	long int  fromString (std::string value) throw (xdata::exception::Exception)
	{	
		// The following code will convert an integer
		// from any represenation, e.g. hex, oct, bin or decimal
		//
		char* firstWrong = 0;

		long int val = strtol ( value.c_str(), &firstWrong, 0 );

		if (	(value_ == LONG_MIN) || 
			(value_ == LONG_MAX) ||
			(*firstWrong != '\0') )
		{
			std::string msg = "Invalid long integer format. Value ";
			msg = value;
			msg += ", error at ";
			msg += firstWrong;
			XCEPT_RAISE (xdata::exception::Exception, msg);
		}
		return val;
	}	
	
	*/

	
};


}}

#endif
