// $Id: WSEventing.h,v 1.4 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_WSEventing_h_
#define _ws_eventing_WSEventing_h_

#include <string>

namespace ws
{
namespace eventing
{
	namespace ElementNames
	{
	   const std::string Code = "Code";
	   const std::string Delivery = "Delivery";
	   const std::string Dialect = "Dialect";
	   const std::string EndTo = "EndTo";
	   const std::string Eventing = "Eventing";
	   const std::string EventSource = "EventSource";
	   const std::string Expires = "Expires";
	   const std::string Filter = "Filter";
	   const std::string GetStatus = "GetStatus";
	   const std::string GetStatusResponse = "GetStatusResponse";
	   const std::string Identifier = "Identifier";
	   const std::string Mode = "Mode";
	   const std::string NotifyTo = "NotifyTo";
	   const std::string Reason = "Reason";
	   const std::string Renew = "Renew";
	   const std::string RenewResponse = "RenewResponse";
	   const std::string Status = "Status";
	   const std::string Subscribe = "Subscribe";
	   const std::string SubscriptionEnd = "SubscriptionEnd";
	   const std::string SubscriptionManager = "SubscriptionManager";
	   const std::string SubscribeResponse = "SubscribeResponse";
	   const std::string Unsubscribe = "Unsubscribe";
	   const std::string UnsubscribeResponse = "UnsubscribeResponse";
	   const std::string SupportedDeliveryMode = "SupportedDeliveryMode";
	   const std::string SupportedDialect = "SupportedDialect";

	    // misc - extenstion
	    const std::string Subscription = "Subscription";
	    const std::string EventTopic = "EventTopic";
	}
       
       
	const std::string NamespacePrefix = "wse";
	const std::string NamespaceUri = "http://schemas.xmlsoap.org/ws/2004/08/eventing";

	const std::string SubscribeAction = NamespaceUri + "/" + ElementNames::Subscribe;
	const std::string SubscribeResponseAction = NamespaceUri + "/" + ElementNames::SubscribeResponse;
	const std::string UnsubscribeAction = NamespaceUri + "/" + ElementNames::Unsubscribe;
	const std::string UnsubscribeResponseAction = NamespaceUri + "/" + ElementNames::UnsubscribeResponse;
	const std::string RenewAction = NamespaceUri + "/" + ElementNames::Renew;
	const std::string RenewResponseAction = NamespaceUri + "/" + ElementNames::RenewResponse;
	const std::string GetStatusAction = NamespaceUri + "/" + ElementNames::GetStatus;
	const std::string GetStatusResponseAction = NamespaceUri + "/" + ElementNames::GetStatusResponse;
	const std::string SubscriptionEndAction = NamespaceUri + "/" + ElementNames::SubscriptionEnd;     
	const std::string PushDeliveryMode = NamespaceUri + "/DeliveryModes/Push";
	const std::string WrappedDeliveryMode = NamespaceUri + "/DeliveryModes/Wrap";
	const std::string XPathDialect = "http://www.w3.org/TR/1999/REC-xpath-19991116";
	const std::string TagDialect = "http://xdaq.web.cern.ch/xdaq/xsd/2008/xmas-TagDialect";
	const std::string DeliveryFailure = NamespaceUri + "/DeliveryFailure";
	const std::string SourceShuttingDown = NamespaceUri + "/SourceShuttingDown";
	const std::string SourceCanceling = NamespaceUri + "/SourceCanceling";

        

	// Subscribe fault
	namespace DeliveryModeRequestedUnvailable
	{
	   const std::string SubCode = "DeliveryModeRequestedUnvailable";
	   const std::string Reason = "The requested delivery mode is not supported.";     
	}

	// Subscribe fault 
	namespace InvalidExpirationType
	{
	    const std::string SubCode = "InvalidExpirationType";
	    const std::string Reason = "The expiration time requested is invalid.";
	}

	// Subscribe fault
	namespace UnsupportedExpirationType
	{
	    const std::string SubCode = "UnsupportedExpirationType";
	    const std::string Reason = "Only expiration durations are supported.";
	}

	// Subscribe fault
	namespace FilteringNotSupported
	{
	    const std::string SubCode = "FilteringNotSupported";
	    const std::string Reason = "Filtering is not supported.";
	}

	// Subscribe fault
	namespace FilteringRequestedUnavailable
	{
	    const std::string SubCode = "FilteringRequestedUnavailable";
	    const std::string Reason = "The requested filter dialect is not supported.";
	}

	// Subscribe fault
	namespace EventSourceUnableToProcess
	{
	    const std::string SubCode = "EventSourceUnableToProcess";
	}

	// Renew fault
	namespace UnableToRenew
	{
	    const std::string SubCode = "UnableToRenew";
	}

	// Any
	namespace InvalidMessage
	{
	    const std::string SubCode = "InvalidMessage";
	    const std::string Reason = "The message is not valid and cannot be processed.";
	}

	namespace Extension
	{
	    // extension
	    const std::string SubscriptionTopic = "SubscriptionTopic";
	    const std::string NamespaceUri = "http://www.rkiss.net/schemas/sb/2004/08/servicebus";
	    const std::string NamespacePrefix = "rksb";
	}

	/*
	enum SubscriptionEndCode
	{
		DeliveryFailure,
		SourceShuttingDown,
		SourceCanceling,
		None
	}
	*/
}
}
#endif

