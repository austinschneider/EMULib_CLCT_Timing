// $Id: PeerTransportReceiver.h,v 1.2 2008/03/12 10:34:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_PeerTransportReceiver_h
#define _atcp_PeerTransportReceiver_h

#include <string>
#include <vector>

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include "pt/atcp/PeerTransportSender.h" //ADDEDATCP for connection at the beginning

#include "toolbox/mem/Pool.h"
#include "pt/PeerTransportReceiver.h"
#include "pt/exception/Exception.h"
#include "pt/atcp/Address.h"
#include "pt/atcp/ReceiverLoop.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

#include "xdaq/Object.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

namespace pt {
namespace atcp
{

//! There is only one peer transport receiver. It has a number of ReceiverLoop
//! objects, one per receiver port
//
class PeerTransportReceiver: public pt::PeerTransportReceiver, public xdaq::Object
{
	public:
	
	PeerTransportReceiver(bool autoSize, xdata::UnsignedInteger32T maxPacketSize, Logger& logger, bool socketReuseAddr, xdaq::Application* owner);
	~PeerTransportReceiver();
	
	pt::TransportType getType();
	
#ifdef XDAQ31
	pt::Address::Reference createAddress( const std::string& url, const std::string& service ) //NEW XDAQ31
		throw (pt::exception::InvalidAddress);
#else		
	pt::Address::Reference createAddress( const std::string& url )
		throw (pt::exception::InvalidAddress);
}
#endif	
	
	pt::Address::Reference 
	createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);

	void addServiceListener (pt::Listener* listener) throw (pt::exception::Exception);
	void removeServiceListener (pt::Listener* listener ) throw (pt::exception::Exception);
	void removeAllServiceListeners();
	
	std::string getProtocol();
	
	std::vector<std::string> getSupportedServices();	

	bool isServiceSupported(const std::string& service );
	
	void config (pt::Address::Reference address) throw (pt::exception::Exception);
	void start() throw (pt::exception::Exception);
	
	void halt() throw (pt::exception::Exception); //ADDEDATCP

	void setPool(toolbox::mem::Pool * pool);
	void setMaxPacketSize(xdata::UnsignedInteger32T maxPacketSize );
	void setAutoSize(bool autoSize );

	void setTcpNodelay(bool tcpNodelay); //ADDEDATCP
	void setBlockingSend(bool blockingSend); //ADDEDATCP
	void setBlockingReceive(bool blockingReceive); //ADDEDATCP
	void setWritesetRare(bool writesetRare); //ADDEDATCP
	void setMaxWritePerSelect(xdata::UnsignedInteger32T maxWritePerSelect); //ADDEDATCP
	void setMaxReadPerSelect(xdata::UnsignedInteger32T maxReadPerSelect); //ADDEDATCP
	void setConnectAtFirstSend(bool connectAtFirstSend); //ADDEDATCP

	//new 26/1/06
	void setNonBlockingConnection(bool nonBlockingConnection);
	void setNoTimeoutRecv(bool noTimeoutRecv);
	void setTimeoutRecvSec(xdata::UnsignedInteger32T timeoutRecvSec);
	void setTimeoutRecvUsec(xdata::UnsignedInteger32T timeoutRecvUsec);

	// new 30/06/2011
	void setSocketReuseAddr(bool socketReuseAddr);

	void setPointerToSender(pt::atcp::PeerTransportSender* pts); //ADDEDATCP

	void bind() throw (pt::exception::Exception);
		
	protected:
	
	bool autoSize_;
	xdata::UnsignedInteger32T maxPacketSize_;			
	std::vector<pt::atcp::ReceiverLoop*> loop_;
	toolbox::mem::Pool * pool_;
	Logger	logger_;

        private:
	pt::atcp::PeerTransportSender* pts_; //ADDEDATCP for connection at the beginning
	bool tcpNodelay_; //ADDEDATCP
	bool blockingSend_; //ADDEDATCP
	bool blockingReceive_; //ADDEDATCP
	bool writesetRare_; //ADDEDATCP
	bool connectAtFirstSend_; //ADDEDATCP
	xdata::UnsignedInteger32T maxWritePerSelect_; //ADDEDATCP
	xdata::UnsignedInteger32T maxReadPerSelect_; //ADDEDATCP

	//new 26/1/06
	bool nonBlockingConnection_;
	bool noTimeoutRecv_;
	xdata::UnsignedInteger32T timeoutRecvSec_;
	xdata::UnsignedInteger32T timeoutRecvUsec_;

	//new 30/06/2011
	bool socketReuseAddr_;
};

}

}
#endif
