// $Id: Transmitter.h,v 1.4 2008/10/06 10:08:38 apetro Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_Transmitter_h_
#define _atcp_Transmitter_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include <netinet/in.h>

#include "pt/atcp/Address.h"
#include "pt/atcp/exception/Exception.h"
#include "pt/atcp/Channel.h"

#include "toolbox/squeue.h" //ADDEDATCP
#include "pt/atcp/PostDescriptor.h" //ADDEDATCP

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

#include "xdata/UnsignedInteger32.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;


namespace pt {
namespace atcp
{

const xdata::UnsignedInteger32T MaxRetry = 3;

class Transmitter : public pt::atcp::Channel
{
	public:
	
	Transmitter(pt::Address::Reference remote, pt::Address::Reference local, xdata::UnsignedInteger32T queueSize, Logger& logger) throw (pt::atcp::exception::Exception);
		
	~Transmitter();

	//! connect channel according configuration
	void connect() throw (pt::atcp::exception::Exception);

	int connectParallelStart() throw (pt::atcp::exception::Exception);
	int connectParallelContinue() throw (pt::atcp::exception::Exception);
	
	//! disconnect but keep channel alive
	void disconnect() throw (pt::atcp::exception::Exception);
	
	//! receive len characters into buf
	int receive(char * buf ,int len ) throw (pt::atcp::exception::Exception);
	
	//! receive non blocking len characters into buf
	int receiveNonBlocking(char * buf ,int len ) throw (pt::atcp::exception::Exception); //ADDEDATCP
	
	//! send buffer of given lenght
	void send(const char * buf, int len) throw (pt::atcp::exception::Exception);

	//! send non blocking buffer of given lenght
	int sendNonBlocking(const char * buf, int len) throw (pt::atcp::exception::Exception); //ADDEDATCP
	
	//! Close a connection definitely
	void close() throw (pt::atcp::exception::Exception);
		
	//! Check if the connection is up
	bool isConnected() throw (pt::atcp::exception::Exception);
	
	bool isConnected_;
	xdata::UnsignedInteger32T retry_;

	volatile bool connectionInProgress_; //ADDEDATCP

	void setTcpNodelayOption() throw (pt::atcp::exception::Exception); //ADDEDATCP
	void setTcpNodelay(bool tcpNodelay) throw (pt::atcp::exception::Exception); //ADDEDATCP

	bool firstPacket() throw (pt::atcp::exception::Exception); //ADDEDATCP
	void setfirstPacketDone() throw (pt::atcp::exception::Exception); //ADDEDATCP
	int getsocket() throw (pt::atcp::exception::Exception); //ADDEDATCP

	void setBlockingSend(bool blockingSend); //ADDEDATCP

	//new 26/1/06
	void setNonBlockingConnection(bool nonBlockingConnection);

	// new 6/04/2010
	void setTryToReconnect(bool tryToReconnect);
	void setNTriesToReconnect(xdata::UnsignedInteger32T nTriesToReconnect);
	void setNTriesToCheckReconnect(xdata::UnsignedInteger32T nTriesToCheckReconnect);

	void setNoTimeoutSend(bool noTimeoutSend);
	void setTimeoutSendSec(xdata::UnsignedInteger32T timeoutSendSec);
	void setTimeoutSendUsec(xdata::UnsignedInteger32T timeoutSendUsec);
	
	void setSocketReuseAddr(bool socketReuseAddr);

	//Get and Set network name for the trasmitter
	std::string getNetwork();
	void setNetwork(std::string network);
	
	//moved outputQueueTransmitter_ to private object
	void pushOutputQueueTransmitter(pt::atcp::PostDescriptor outputDescriptor);
	pt::atcp::PostDescriptor popOutputQueueTransmitter();
	bool outputQueueTransmitterIsEmpty();
	
	//Get the size of output queue Trasmiter
	size_t getNOutputQueueTransmitter();
	
	//Get the remote address
	pt::Address::Reference getRemoteAddress();
	
	map<int,int> getErrnoOccurrences();

        private:

        	
    toolbox::squeue<pt::atcp::PostDescriptor> outputQueueTransmitter_;
    
    //Added Name of the network
    std::string network_;  	
	// not used pt::atcp::PostDescriptor currentPostDescriptor; //ADDEDATCP

	bool isFirstPacket_; //ADDEDATCP
	bool tcpNodelay_; //ADDEDATCP
	int tcpNodelayNet_; //ADDEDATCP //this is the one from the local EndPoint
	int thread_; //ADDEDATCP //this is the one from the local EndPoint
	bool blockingSend_; //ADDEDATCP

	//new 26/1/06
	bool nonBlockingConnection_;

	// new 6/04/2010
	bool tryToReconnect_;
	xdata::UnsignedInteger32T nTriesToReconnect_;
	xdata::UnsignedInteger32T nTriesToCheckReconnect_;

	//new 30/06/2011
	bool socketReuseAddr_;

	bool noTimeoutSend_;
	xdata::UnsignedInteger32T timeoutSendSec_;
	xdata::UnsignedInteger32T timeoutSendUsec_;

	//struct timeval  timeout; //ADDEDATCP

	map<int,int> errnoOccurrences_;

	Logger logger_;

	pt::Address::Reference remoteAddress_;
	pt::Address::Reference localAddress_;

};


}

}
#endif
