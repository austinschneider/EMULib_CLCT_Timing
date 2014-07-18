// $Id: Headers.h,v 1.2 2008/07/18 15:27:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_addressing_Headers_h_
#define _ws_addressing_Headers_h_

#include <string>
#include "xoap/SOAPEnvelope.h"
#include "ws/addressing/exception/Exception.h"
#include "xoap/MessageReference.h"

namespace ws
{
namespace addressing
{
    class Headers
    {
    	public:
	
	Headers();
	        
	bool hasAction();
	std::string getAction();	
	void setAction ( const std::string & value );
	
	bool hasFaultTo();
	std::string getFaultTo();	
	void setFaultTo ( const std::string & value );
	
	bool hasFrom();
	std::string getFrom();	
	void setFrom ( const std::string & value );
	
	bool hasMessageId();
	std::string getMessageId();	
	void setMessageId(const std::string & id);
	
	bool hasRelatesTo();
	std::string getRelatesTo();	
	void setRelatesTo ( const std::string & value );
	
	bool hasReplyAfter();
	std::string getReplyAfter();	
	void setReplyAfter ( const std::string & value );
	
	bool hasReplyTo();
	std::string getReplyTo();	
	void setReplyTo ( const std::string & value );
		
	bool hasTo();
	std::string getTo();	
	void setTo ( const std::string & value );
	
	void fromSOAP(xoap::MessageReference& msg) throw (ws::addressing::exception::Exception);
	void toSOAP(xoap::MessageReference& msg) throw (ws::addressing::exception::Exception);
      
	private:
	
	std::string action_;
	std::string faultTo_;
	std::string from_;
	std::string messageId_;
	std::string relatesTo_;
	std::string replyAfter_;
	std::string replyTo_;	
	std::string to_;
    };
}
}
#endif


