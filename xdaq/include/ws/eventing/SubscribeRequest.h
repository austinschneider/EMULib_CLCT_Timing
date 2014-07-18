// $Id: SubscribeRequest.h,v 1.15 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_SubscribeRequest_h_
#define _ws_eventing_SubscribeRequest_h_

#include <string>
#include "ws/eventing/XPathMessageFilter.h"
#include "ws/eventing/TagMessageFilter.h"
#include "ws/eventing/Delivery.h"
#include "ws/eventing/Expires.h"
#include "ws/eventing/exception/Exception.h"
#include "ws/eventing/exception/NotPresent.h"
#include "xoap/MessageReference.h"
#include "ws/addressing/EndpointReference.h"
#include "ws/addressing/Headers.h"

namespace ws
{

namespace eventing
{

    class SubscribeRequest
    {
    	public:
	
	SubscribeRequest();
	
        SubscribeRequest(xoap::MessageReference& msg) throw (ws::eventing::exception::Exception);
        
	SubscribeRequest(const SubscribeRequest & s);
	
	SubscribeRequest& operator= (const SubscribeRequest & s);
	
	virtual ~SubscribeRequest();
		
	ws::addressing::Headers & getAddressingHeaders();
	
	ws::addressing::EndpointReference& getEndTo() const
		throw (ws::eventing::exception::NotPresent);
	
	bool hasEndTo();

	void setEndTo (ws::addressing::EndpointReference & value );
	
        Delivery& getDelivery() const throw (ws::eventing::exception::NotPresent);
	
	bool hasDelivery();
	
	void setDelivery ( Delivery & value );
	
        Expires& getExpires() const
        	throw (ws::eventing::exception::NotPresent);
	
	bool hasExpires();
	
	void setExpires ( Expires& value );
	
        XPathMessageFilter& getFilter() const throw (ws::eventing::exception::NotPresent);
	
	bool hasFilter();
	
	void setFilter ( XPathMessageFilter & value );
	
        std::string getFilterDialect();
        
	bool hasMessageFilter();

	ws::eventing::TagMessageFilter& getMessageFilter() const throw (ws::eventing::exception::NotPresent);
	
	void setMessageFilter ( const ws::eventing::TagMessageFilter & value );
	
	std::string getSubscriptionTopic();

 	void setSubscriptionTopic ( const std::string & value );	
      
     	xoap::MessageReference toSOAP();

	private:
	
	ws::addressing::Headers aheaders_;	
	ws::addressing::EndpointReference* endTo_;
	Delivery* delivery_; 
	Expires* expires_;
	std::string subscriptionTopic_;  
	std::string filterDialect_;
	XPathMessageFilter* filter_;
	TagMessageFilter* messageFilter_; 
    };
}
}
#endif


