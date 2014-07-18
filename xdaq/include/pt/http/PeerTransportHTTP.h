// $Id: PeerTransportHTTP.h,v 1.3 2008/07/18 15:27:16 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_http_PeerTransportHTTP_h_
#define _pt_http_PeerTransportHTTP_h_

#include "xdaq/Application.h"
#include "pt/http/Alias.h"
#include "pt/http/HeaderField.h"
#include "pt/http/PeerTransportSender.h"
#include "pt/http/PeerTransportReceiver.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"

namespace pt
{
namespace http 
{

//! this is the XDAQ Peer Transport Appliction Wrapper
//
class PeerTransportHTTP: public xdaq::Application
{
	public:
	
	XDAQ_INSTANTIATOR();

	
	PeerTransportHTTP(xdaq::ApplicationStub * s) throw(xdaq::exception::Exception);
	virtual ~PeerTransportHTTP();
	
	private:
	
	http::PeerTransportSender* pts_;
	http::PeerTransportReceiver* ptr_;
	
	//! Temporary possibility to define an alias, e.g.:
	//! http://x.y/z -> http://x.y/myPath
	xdata::Vector< xdata::Bag<pt::http::Alias> > aliases_;
	xdata::Vector< xdata::Bag<pt::http::HeaderField> > headers_;
	xdata::String documentRoot_;
	xdata::String aliasName_;
	xdata::String aliasPath_;
	xdata::Boolean autoFooter_; //default is true

};
}
}
#endif
