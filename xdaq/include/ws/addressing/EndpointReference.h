// $Id: EndpointReference.h,v 1.9 2008/07/18 15:27:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_addressing_EndpointReference_h_
#define _ws_addressing_EndpointReference_h_

#include <string>
#include "toolbox/net/UUID.h"
#include "toolbox/net/URL.h"
#include "xoap/SOAPElement.h"
#include "xoap/SOAPEnvelope.h"
#include "ws/addressing/exception/Exception.h"

namespace ws
{
namespace addressing
{
	class EndpointReference
	{
		public:
		
		// Uninitialized empty CTOR
		//
		EndpointReference();
		
		EndpointReference (xoap::SOAPElement& element)
			throw (ws::addressing::exception::Exception);
			
		EndpointReference (const toolbox::net::URL& url)
			throw (ws::addressing::exception::Exception);
		
		EndpointReference (const EndpointReference & epr);
									
		virtual ~EndpointReference();
		
		ws::addressing::EndpointReference& operator= (const EndpointReference & epr);
	
		/**
		* Returns the Address from the EPR as a String.
		*
		* @return Address
		*/
		std::string getAddress(  );

		/**
		* Returns the PortName associated with the Service in the EPR as a String
		*
		* @return Service's Port Name
		*/
		std::string getPortName(  );

		/**
		* Returns the PortType QName
		*
		* @return PortType QName
		*/
		std::string getPortType(  );

		/**
		* Returns the ReferenceParameters Object.
		*
		* @return Object[] The ReferenceParameters
		*
		* @throws an exception if there are no reference parameters
		*/
		DOMElement* getReferenceParameters(  ) throw (ws::addressing::exception::Exception);
		
		/**
		* @return true if the endpoint has reference parameters
		*
		* @return false otherwise
		*/
		bool hasReferenceParameters ( );

		/**
		* Returns the ReferenceProperties Object.
		*
		* @return Object[] The ReferenceProperties
		*
		* @throws an exception if there are no reference properties
		*/
		DOMElement* getReferenceProperties(  ) throw (ws::addressing::exception::Exception);
		
		/**
		* @return true if the endpoint has reference properties
		*
		* @return false otherwise
		*/
		bool hasReferenceProperties(  );

		/**
		* Service QName
		*
		* @return Service QName
		*/
		std::string getServiceName(  );

		/**
		*
		* @param refProp
		*/
		// void addReferenceParameter( DOMNode* parameters );

		/**
		*
		* @param refProp
		*/
		// void addReferenceProperty( DOMNode* properties );
		
		/**
		*
		* @param element holds a SOAP message into which the EndpointReference is serialized as XML
		* @param envelope is the envelope of the SOAP message into which this class is serialized
		*/
		void toSOAP(xoap::SOAPElement& element, xoap::SOAPEnvelope& envelope);		
		
		//! Returns the universal unique identifier of the application desciptor
		//
		toolbox::net::UUID getUUID();
		
		protected:
		
			std::string serviceName_;
			std::string portType_;
			std::string portName_;
			std::string address_;
			
			DOMDocument* parameters_;
			DOMDocument* properties_;
			toolbox::net::UUID uuid_;
	};
}
}

#endif


