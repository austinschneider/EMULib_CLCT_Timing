// $Id: Delivery.h,v 1.9 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_Delivery_h_
#define _ws_eventing_Delivery_h_

#include <string>
#include "xoap/SOAPElement.h"
#include "xoap/SOAPName.h"
#include "ws/addressing/EndpointReference.h"
#include "ws/eventing/WSEventing.h"
#include "ws/eventing/exception/NotPresent.h"
// #include "ws/eventing/HeaderCollection.h"

namespace ws
{
	namespace eventing
	{
		class Delivery // : public HeaderCollection
		{
			public: 
			Delivery();
	
			Delivery(const std::string & mode, ws::addressing::EndpointReference& to)
				throw (ws::eventing::exception::Exception );

			virtual ~Delivery();

			Delivery(xoap::SOAPElement& element)
				throw (ws::eventing::exception::Exception);
			
			Delivery(const Delivery & d);

			std::string getDeliveryMode();

			void setDeliveryMode(const std::string & value);

			ws::addressing::EndpointReference& getNotifyTo()
				throw (ws::eventing::exception::NotPresent);

			void setNotifyTo (ws::addressing::EndpointReference& value) throw (ws::eventing::exception::Exception );

			void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope);

			Delivery& operator= (const Delivery & d);

			protected:

			std::string mode_;
			ws::addressing::EndpointReference* notifyTo_;     
		};
	}
}

#endif


