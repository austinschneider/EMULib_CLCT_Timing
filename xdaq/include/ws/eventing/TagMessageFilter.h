// $Id: TagMessageFilter.h,v 1.1 2008/05/20 11:37:41 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_TagMessageFilter_h_
#define _ws_eventing_TagMessageFilter_h_

#include "ws/eventing/MessageFilter.h"

#include "toolbox/string.h"
#include "xoap/MessageReference.h"
#include "xoap/SOAPElement.h"


namespace ws
{
namespace eventing
{
	class TagMessageFilter :
		public MessageFilter
	{      
	public:
		TagMessageFilter();
	
		TagMessageFilter(const std::string& filter);

		TagMessageFilter(const std::set<std::string>& tags);
	
		MessageFilter* clone() const;

		void fromSOAP( xoap::SOAPElement& element);

		void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope);

		const std::string& getFilterDialect() const;
	
		const std::string& toString() const;

		bool matches( xoap::MessageReference msg);

		TagMessageFilter& operator= (const TagMessageFilter & s);

	protected:
		// list of comma separated tags
		std::string filter_;
		// list of tags
		std::set<std::string> tags_;
	};
}
}

#endif

