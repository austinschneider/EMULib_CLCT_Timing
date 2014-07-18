// $Id: ContextDescriptor.h,v 1.6 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ContextDescriptor_h_
#define _xdaq_ContextDescriptor_h_

#include <string>

#include "xdaq/exception/InvalidURL.h"

namespace xdaq 
{

class ContextDescriptor
{
	public:
	
	//! Create a new context.
	/*! A context is uniquely identified by its URL, e.g. hostname and port 
	 * 
	*/
	ContextDescriptor (const std::string & url);
	
	//! Retrieve the URL that uniquely identifies a context
	std::string getURL();
	
	
	//! Safe test if the context descriptor matches a given url (hostname, IP)
	/*! The given URL is normalized so that a match can be performed, even if
	    the hostname does not exactly match the provided one, e.g.:
	    lxcmdxxx.cern.ch == lxcmdxxx
	    \throws xdaq::exception::InvalidURL
	*/
	bool matchURL (const std::string& url)
		throw (xdaq::exception::InvalidURL);

	private:
	
	std::string url_;

};

}

#endif
