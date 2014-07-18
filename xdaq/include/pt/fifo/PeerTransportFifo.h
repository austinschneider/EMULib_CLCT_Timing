// $Id: PeerTransportFifo.h,v 1.2 2008/07/18 15:27:14 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_fifo_PeerTransportFifo_h_
#define _pt_fifo_PeerTransportFifo_h_

#include "xdaq/Application.h"
#include "pt/fifo/PeerTransport.h"

//! this is the XDAQ Peer Transport Appliction Wrapper
//
namespace pt
{
	namespace fifo
	{
		class PeerTransportFifo: public xdaq::Application
		{
			public:

			XDAQ_INSTANTIATOR();

			PeerTransportFifo(xdaq::ApplicationStub * s) throw(xdaq::exception::Exception);
			~PeerTransportFifo();

			private:

			pt::fifo::PeerTransport* pt_;
		};
	}
}
#endif
