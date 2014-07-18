// $Id: ReceiverLoop.h,v 1.2 2008/03/12 10:34:35 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_ReceiverLoop_h_
#define _atcp_ReceiverLoop_h_

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include <vector>
#include <sys/select.h>

#include "toolbox/Task.h"
#include "pt/atcp/Address.h"
#include "pt/atcp/Channel.h"
#include "pt/atcp/exception/Exception.h"
#include "pt/Listener.h" 
#include "i2o/Listener.h" 
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/lang/Class.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

#include  "i2o/i2o.h" //ADDEDATCP

//for the receive sockets //ADDEDATCP
#define RSBEFOREHEAD 0 //ADDEDATCP
#define RSREADHEAD 1 //ADDEDATCP
#define RSBEFOREDATA 2 //ADDEDATCP
#define RSREADDATA 3 //ADDEDATCP

#include "xdata/UnsignedInteger32.h"

#include "xdaq/Object.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;


namespace pt {
namespace atcp
{

class ReceiverLoop:  public pt::atcp::Channel, public toolbox::lang::Class, public xdaq::Object
{
  //enum { MaxNoChannels = 1024 }; //ADDEDATCP removed

	public:
	
	ReceiverLoop(pt::Address::Reference address, Logger& logger, xdaq::Application* owner) 
		throw (pt::atcp::exception::Exception);
	
	~ReceiverLoop();
		
	// override channel receive
	int receive(char * buf ,int len ) throw (pt::atcp::exception::Exception);

	int receiveNonBlocking(char * buf ,int len ) throw (pt::atcp::exception::Exception); //ADDEDATCP
	
	void send(const char * buf, int len) throw (pt::atcp::exception::Exception);

	int sendNonBlocking(const char * buf, int len) throw (pt::atcp::exception::Exception); //ADDEDATCP
	
	void disconnect() throw (pt::atcp::exception::Exception);
	
	void connect() throw (pt::atcp::exception::Exception); 
	
	void close() throw (pt::atcp::exception::Exception);
	void bind() throw (pt::exception::Exception);
	
	//! work loop job routine
	bool process(toolbox::task::WorkLoop * wl);

	//! Get the address of this receiver (can be casted to a pt::atcp::Address&)
	pt::Address::Reference getAddress();
	
	void addServiceListener (pt::Listener* listener);
	void removeServiceListener (pt::Listener* listener);
	void removeAllServiceListeners();
	
	void setPool(toolbox::mem::Pool * pool);
	void setMaxPacketSize(xdata::UnsignedInteger32T maxPacketSize );
	void setAutoSize(bool autoSize );

	void setBlockingReceive(bool blockingReceive); //ADDEDATCP
	void setMaxReadPerSelect(xdata::UnsignedInteger32T maxReadPerSelect); //ADDEDATCP

	//new 26/1/06
	void setNonBlockingConnection(bool nonBlockingConnection);
	void setNoTimeoutRecv(bool noTimeoutRecv);
	void setTimeoutRecvSec(xdata::UnsignedInteger32T timeoutRecvSec);
	void setTimeoutRecvUsec(xdata::UnsignedInteger32T timeoutRecvUsec);


	void activate();
	void deactivate(); //ADDEDATCP for halt //TOBETESTED
	
	private:
	
	int accept() throw (pt::atcp::exception::Exception);
	
	bool isConnected() throw (pt::atcp::exception::Exception);
	bool isActive() throw (pt::atcp::exception::Exception);
	
	void onRequest() throw (pt::atcp::exception::Exception);
	
	void safeReceive(char * buf, int len) throw (pt::atcp::exception::Exception);
	int safeReceiveNonBlocking(char * buf, int len) throw (pt::atcp::exception::Exception); //ADDEDATCP

	//std::vector<int> sockets_;

	typedef struct //ADDEDATCP
	{ //ADDEDATCP
	  int             socketNum; //ADDEDATCP Contains the assigned socket number 
	  //int             socketType; //ADDEDATCP UNUSED Type of socket (eg.:Listen/Input/OUTPUT/PENDING)
	  int             socketStatus;  //ADDEDATCP 0 not started, 1 in progress
	  //int             maskSet; //ADDEDATCP UNUSED
	  int             dataLen; // for read
	  //int             totalBytes; //ADDEDATCP UNUSED
	  int             nBytes;     //ADDEDATCP 
	  toolbox::mem::Reference* ref; //ADDEDATCP  
	  //int             requestStatus; //ADDEDATCP //0 FREE, 1 BUSY
	  //xdata::UnsignedInteger32T   size; //ADDEDATCP UNUSED
	  I2O_MESSAGE_FRAME header; //ADDEDATCP for receive
	} SocketData; //ADDEDATCP

	SocketData socketDataTemp_; //ADDEDATCP
	std::vector<SocketData> socketData_;  //ADDEDATCP
	//int numberOfSockets_; //ADDEDATCP //TOBETESTED unused for now, perhaps should be put

	pt::Address::Reference  address_; // reference counted pt address
	fd_set fdset_;
	fd_set allset_;
	int maxfd_;
	int current_;
	int listenfd_;
	int accepted_;
	int nochannels_;
	int nready_;
	bool autoSize_; // use variable size allocation of incoming messages
	xdata::UnsignedInteger32T maxPacketSize_; // if autoSize_ is true, then this package size is always used for receiving packets. Otherwise it is an upper limit
	
	bool blockingReceive_; //ADDEDATCP
	xdata::UnsignedInteger32T maxReadPerSelect_; //ADDEDATCP

	//new 26/1/06
	bool nonBlockingConnection_;
	bool noTimeoutRecv_;
	xdata::UnsignedInteger32T timeoutRecvSec_;
	xdata::UnsignedInteger32T timeoutRecvUsec_;


	struct timeval timeout; //ADDEDATCP

	i2o::Listener* listener_;
	toolbox::mem::Pool * pool_;
	toolbox::mem::MemoryPoolFactory * manager_;
	toolbox::task::ActionSignature* process_;		
	Logger logger_;	

	bool workLoopActivated_; //ADDEDATCP for the halt //TOBETESTED
};

}

}
#endif
