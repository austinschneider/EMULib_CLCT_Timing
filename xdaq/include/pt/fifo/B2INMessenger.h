// $Id: B2INMessenger.h,v 1.3 2008/07/18 15:27:14 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_fifo_B2INMessenger_h
#define _pt_fifo_B2INMessenger_h

#include "b2in/nub/Messenger.h"
#include "pt/Address.h"
#include "pt/fifo/PeerTransport.h"
#include "toolbox/mem/Reference.h"
#include "b2in/nub/exception/InternalError.h"
#include "b2in/nub/exception/QueueFull.h"
#include "b2in/nub/exception/OverThreshold.h"

namespace pt
{
	namespace fifo
	{
		class PeerTransport;

		class B2INMessenger: public b2in::nub::Messenger
		{
			public:

			B2INMessenger(pt::fifo::PeerTransport * pt);
			virtual ~B2INMessenger();

			pt::Address::Reference getLocalAddress();
			pt::Address::Reference getDestinationAddress();

			void send 
			(
				toolbox::mem::Reference* msg,
				xdata::Properties & plist,
				toolbox::exception::HandlerSignature* handler,
				void* context
			) 
			throw (
				b2in::nub::exception::InternalError,
				b2in::nub::exception::QueueFull,
				b2in::nub::exception::OverThreshold
			);

			private:

			pt::fifo::PeerTransport * pt_;
			pt::Address::Reference local_;
		};
	}
}

#endif

