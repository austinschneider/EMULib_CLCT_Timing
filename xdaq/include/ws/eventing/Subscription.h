// $Id: Subscription.h,v 1.12 2008/07/21 14:00:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_Subscription_h_
#define _ws_eventing_Subscription_h_

#include "xdata/Serializable.h"

#include "ws/eventing/SubscriptionManager.h"
#include "ws/addressing/EndpointReference.h"
#include "ws/eventing/SubscribeRequest.h"
#include "ws/eventing/Delivery.h"
#include "ws/eventing/Expires.h"
#include "toolbox/TimeVal.h"
#include "ws/eventing/XPathMessageFilter.h"
#include "ws/eventing/TagMessageFilter.h"

namespace ws
{
namespace eventing
{  
	class Subscription: public xdata::Serializable
	{
		public:

		// Subscription();

		Subscription(SubscribeRequest & subscribe, SubscriptionManager  & manager);
		
		virtual ~Subscription();

		bool getIsReadOnly();

		void setIsReadOnly ( bool value );

		SubscriptionManager& getManager();

		void setManager (SubscriptionManager & manager);

		ws::addressing::EndpointReference& getEndTo();

		void setEndTo (ws::addressing::EndpointReference & epa);

		Delivery& getDelivery();

		void setDelivery (Delivery & delivery);

		Expires& getExpires();

		void setExpires (toolbox::TimeVal & expires);

		XPathMessageFilter& getFilter();

		void setFilter (XPathMessageFilter& filter);
		
		TagMessageFilter& getMessageFilter();

		void setMessageFilter (TagMessageFilter& filter);

		bool hasMessageFilter();

		// xdata::Serializable interfaces
		// ------------------------------
		//
		std::string type() const;
	
		void setValue (const xdata::Serializable& s);
	
		// Not yet implemented
		//
		int equals(const xdata::Serializable & s);
	
		// Not yet implemented
		//
		std::string toString() throw (xdata::exception::Exception);

		void fromString(const std::string& value) throw (xdata::exception::Exception);
		
		bool isValid();
		
		void setValid( bool value );

		protected:

		ws::addressing::EndpointReference endTo_;
		Delivery delivery_;
		Expires expires_;
		XPathMessageFilter filter_;
		TagMessageFilter messagefilter_;
		SubscriptionManager manager_;

		bool hasMessageFilter_; // true if message filter on tag, false if xpath
		bool readonly_;
		bool valid_;
	};	
}
}

#endif


