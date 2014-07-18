// $Id: I2OMessenger.h,v 1.2 2008/07/18 15:27:14 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_fifo_I2OMessenger_h
#define _pt_fifo_I2OMessenger_h

#include "i2o/Messenger.h"
#include "toolbox/mem/Reference.h"
#include "pt/Address.h"
#include "pt/exception/Exception.h"

namespace pt
{
	namespace fifo
	{
		class PeerTransport;

		class I2OMessenger: public i2o::Messenger
		{
			public:

			I2OMessenger(fifo::PeerTransport* pt);
			void send (toolbox::mem::Reference* msg, toolbox::exception::HandlerSignature * handler, void * context) throw (pt::exception::Exception);
			pt::Address::Reference getLocalAddress();
			pt::Address::Reference getDestinationAddress();

			private:

			pt::fifo::PeerTransport* pt_;
		};
	}
}

#endif
