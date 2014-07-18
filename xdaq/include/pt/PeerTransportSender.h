// $Id: PeerTransportSender.h,v 1.6 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_PeerTransportSender_h
#define _pt_PeerTransportSender_h

#include <string>
#include <vector>

#include "pt/Listener.h"
#include "pt/Messenger.h"
#include "pt/Address.h"
#include "pt/PeerTransport.h"
#include "pt/exception/UnknownProtocolOrService.h"

namespace pt
{

class PeerTransportSender: public virtual pt::PeerTransport
{
	public:
	virtual ~PeerTransportSender()
	{
	}

	//! Returns a messenger object over which messages can be sent for a specific destination address.
	//! In addition a local address can be provided.
	//! The protocol and service in the address need to be supported by the peer transport
	//
	virtual pt::Messenger::Reference getMessenger (pt::Address::Reference destination, pt::Address::Reference local)
	 	throw (pt::exception::UnknownProtocolOrService) = 0;

		
};

}

#endif
