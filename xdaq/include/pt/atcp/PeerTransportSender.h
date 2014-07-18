// $Id: PeerTransportSender.h,v 1.4 2008/07/23 15:11:46 apetro Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_PeerTransportSender_h
#define _atcp_PeerTransportSender_h

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include <vector>
#include <map>
#include <string>

#include "pt/exception/Exception.h" //ADDEDATCP

#include "pt/PeerTransportSender.h"
#include "pt/PeerTransportReceiver.h"
#include "pt/PeerTransportAgent.h"
#include "toolbox/squeue.h"
#include "pt/atcp/Channel.h"
#include "pt/atcp/PostDescriptor.h"
#include "toolbox/mem/Reference.h"
#include "i2o/Messenger.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/Action.h"
#include "toolbox/lang/Class.h"

#include "i2o/i2o.h" //ADDEDATCP
#include "pt/atcp/Transmitter.h" //ADDEDATCP
#include <sys/select.h> //ADDEDATCP

//for the send sockets
#define RSBEFORESEND 0 //ADDEDATCP
#define RSSEND 1 //ADDEDATCP

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

class PeerTransportSender: public pt::PeerTransportSender, public toolbox::lang::Class, public xdaq::Object
{
	public:
	
	PeerTransportSender(Logger& logger, xdaq::Application* owner);
	virtual ~PeerTransportSender();
	
	pt::TransportType getType();
	
#ifdef XDAQ31
	pt::Address::Reference createAddress( const std::string& url, const std::string& service ) //NEW XDAQ31
		throw (pt::exception::InvalidAddress);
#else		
	pt::Address::Reference createAddress( const std::string& url )
		throw (pt::exception::InvalidAddress);
}
#endif	
	
	pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);
	
	std::string getProtocol();
	
	std::vector<std::string> getSupportedServices();	

	bool isServiceSupported(const std::string& service );
	
	pt::Messenger::Reference getMessenger (pt::Address::Reference destination, pt::Address::Reference local)
		throw (pt::exception::UnknownProtocolOrService);
	
	//! sender loop service routine, run in a thread
	bool process(toolbox::task::WorkLoop * wl) 
	  throw (pt::exception::Exception) //ADDEDATCP the exception (probably not used //TOBECHANGED)
	  ;
	
	
	//! queue a request for send
	void post(toolbox::mem::Reference * ref, 
			pt::atcp::Channel * channel, 
			toolbox::exception::HandlerSignature * handler, 
			void * context)
		throw (pt::exception::Exception);

	void start() 
	  throw (pt::exception::Exception) //ADDEDATCP the exception
	  ;
	
	void halt() throw (pt::exception::Exception); //ADDEDATCP for halt

	void setTcpNodelay(bool tcpNodelay); //ADDEDATCP
	void setBlockingSend(bool blockingSend); //ADDEDATCP
	void setBlockingReceive(bool blockingReceive); //ADDEDATCP
	void setWritesetRare(bool writesetRare); //ADDEDATCP
	void setMaxWritePerSelect(xdata::UnsignedInteger32T maxWritePerSelect); //ADDEDATCP
	void setMaxReadPerSelect(xdata::UnsignedInteger32T maxReadPerSelect); //ADDEDATCP
	void setConnectAtFirstSend(bool connectAtFirstSend); //ADDEDATCP
	void setSyncronousSend(bool syncronousSend_); //ADDEDATCP
	void setQueueSize(xdata::UnsignedInteger32T queueSize); //ADDEDATCP


	//new 26/1/06
	void setNonBlockingConnection(bool nonBlockingConnection);
	void setNoTimeoutSend(bool noTimeoutSend);
	void setTimeoutSendSec(xdata::UnsignedInteger32T timeoutSendSec);
	void setTimeoutSendUsec(xdata::UnsignedInteger32T timeoutSendUsec);

	// new 29/09/2009
	void setNTriesToConnect(xdata::UnsignedInteger32T nTriesToConnect);

	// new 6/04/2010
	void setTryToReconnect(bool tryToReconnect);
	void setNTriesToReconnect(xdata::UnsignedInteger32T nTriesToReconnect);
	void setNTriesToCheckReconnect(xdata::UnsignedInteger32T nTriesToCheckReconnect);

	// new 30/06/2011
	void setSocketReuseAddr(bool socketReuseAddr);

	void addAddress(pt::Address::Reference allAddresses, bool isLocal, std::string network); //ADDEDATCP

	void connectAllSocketsParallel() throw (pt::exception::Exception); //ADDEDATCP
	void connectAllSockets() throw (pt::exception::Exception); //ADDEDATCP
	void disconnectAllSockets() throw (pt::exception::Exception); //ADDEDATCP
	
	int nmissing;
	
	//Added map with size of all output quew
	typedef map<std::string, int> myMap;
	myMap nMissingSocketNetworks;
	myMap getMissingConnection();
	
	typedef struct //ADDEDATCP
		{ //ADDEDATCP
		  int             socketNum; //ADDEDATCP Contains the assigned socket number 
		  //int             socketType; //ADDEDATCP UNUSED Type of socket (eg.:Listen/Input/OUTPUT/PENDING)
		  volatile int             socketStatus;  //ADDEDATCP USED 0 not started, 1 in progress
		  int             dataLen; //ADDEDATCP USED
		  //int             totalBytes; //ADDEDATCP UNUSED
		  int             nBytes;     //ADDEDATCP USED
		  pt::atcp::Transmitter* Transmitter; //ADDEDATCP link to the transmitter for this socket
		  pt::atcp::PostDescriptor request; //ADDEDATCP USED //PostDescriptor for this socket
		  toolbox::mem::Reference* ref; //ADDEDATCP USED 
		  //int requestStatus; //ADDEDATCP USED //0 FREE, 1 BUSY
		  PI2O_MESSAGE_FRAME frame; //ADDEDATCP USED
		  xdata::UnsignedInteger32T size; //ADDEDATCP USED
		} SocketData; //ADDEDATCP
	
	std::vector<SocketData> getSocketData();
	
	private:
	
	bool tcpNodelay_; //ADDEDATCP
	bool blockingSend_; //ADDEDATCP
	bool blockingReceive_; //ADDEDATCP
	bool writesetRare_; //ADDEDATCP
	bool connectAtFirstSend_; //ADDEDATCP
	bool syncronousSend_; //ADDEDATCP
	xdata::UnsignedInteger32T maxWritePerSelect_; //ADDEDATCP
	xdata::UnsignedInteger32T maxReadPerSelect_; //ADDEDATCP

	//new 26/1/06
	bool nonBlockingConnection_;
	bool noTimeoutSend_;
	xdata::UnsignedInteger32T timeoutSendSec_;
	xdata::UnsignedInteger32T timeoutSendUsec_;

	//new 29/09/2009
	xdata::UnsignedInteger32 nTriesToConnect_;

	// new 6/04/2010
	bool tryToReconnect_;
	xdata::UnsignedInteger32T nTriesToReconnect_;
	xdata::UnsignedInteger32T nTriesToCheckReconnect_;

	//new 30/06/2011
	bool socketReuseAddr_;

	xdata::UnsignedInteger32T queueSize_;

		//! synchronous queue, waits till at least one element present in queue
		toolbox::squeue<pt::atcp::PostDescriptor> outputQueue_;
		toolbox::task::ActionSignature* process_; 
		bool activated_;

		bool workLoopActivated_; //ADDEDATCP for the halt //TOBETESTED


	SocketData socketDataTemp_; //ADDEDATCP
	std::vector<SocketData> socketData_; //ADDEDATCP
	//int numberOfSockets_; //ADDEDATCP //TOBETESTED perhaps should be used

	//std::vector<int> sockets_;

	//ATTENTION, it is still using this transmitter vector here //TOBECHANGED
	//std::vector<pt::atcp::Transmitter*> transmitter_; //ADDEDATCP //TOBECHANGED 

	fd_set fdset_; //ADDEDATCP
	fd_set allset_; //ADDEDATCP 
	int maxfd_; // ADDEDATCP
	int nready_; // ADDEDATCP

	struct timeval  timeout; //ADDEDATCP

	//ADDEDATCP this is to connect immediately
	std::vector<pt::Address::Reference> allAddresses_; //ADDEDATCP
	std::vector<bool> isLocal_; //ADDEDATCP
	std::vector<std::string> network_; //ADDEDATCP

	std::vector<pt::Messenger::Reference> messengers_; //ADDEDATCP
	std::vector<pt::Address::Reference> destinations_; //ADDEDATCP
	std::vector<pt::Address::Reference> locals_; //ADDEDATCP

	Logger logger_;
};

}

}
#endif
