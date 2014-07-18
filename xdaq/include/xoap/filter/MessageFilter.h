// $Id: MessageFilter.h,v 1.3 2008/07/18 15:28:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_filter_MessageFilter_h_
#define _xoap_filter_MessageFilter_h_

#include "toolbox/string.h"
#include "xoap/MessageReference.h"
#include "xoap/SOAPElement.h"
#include "xoap/exception/Exception.h"

namespace xoap
{
namespace filter
{
    class MessageFilter
    {      
      	public:
	
	MessageFilter(const std::string& filterExpression);
	
     	MessageFilter( xoap::SOAPElement& element );
	
	std::string getFilterExpression();
	
	/*! Apply filter expression to the \param message provided and
	    \returns true if the filter matches any of the elements in
	    the message. \returns false if no element in the \param message
	    matches the expression.
	*/
	bool match(xoap::MessageReference & message) throw (xoap::exception::Exception);
	
	/*! Apply filter expression to the \param message provided and
	    \returns true if the filter matches any of the elements in
	    the message. \returns false if no element in the \param message
	    matches the expression.
	*/
	std::string evaluate(xoap::MessageReference & message) throw (xoap::exception::Exception);
	
	/*! Apply filter expression to the \param message provided. Return a list of
	    nodes in the message that match the filter expression. The returned list
	    may be empty if no node matched the filter expression.
	 */
	std::list<xoap::SOAPElement> extract (xoap::MessageReference & message) throw (xoap::exception::Exception);
     
        protected:
      
   	std::string filter_;
    };
}
}

#endif
