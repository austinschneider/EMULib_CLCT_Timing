// $Id: ContextTable.h,v 1.7 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ContextTable_h_
#define _xdaq_ContextTable_h_

#include <string>
#include <map>
#include <vector>

#include "xdaq/ContextDescriptor.h"
#include "xdaq/exception/HostNotFound.h"
#include "xdaq/exception/DuplicateHost.h"
#include "xdaq/exception/CreationFailed.h"

namespace xdaq 
{
	class ContextTable
	{
		public:

		// DTOR
		~ContextTable();

		//! Create a new context
		/*! A context is uniquely identified by its URL, e.g. hostname and port 
		 *  A sessionId different from empty string "" may be provided. It can be used
		 *   to associate a running context (= a session) with other running contexts
		 */
		xdaq::ContextDescriptor* createContextDescriptor (const std::string& url) 
			throw  (xdaq::exception::DuplicateHost, xdaq::exception::CreationFailed);

		//! Remove a context descriptor by URL
 		void removeContext(const std::string & url) throw (xdaq::exception::HostNotFound);

		//! Retrieve a ContextDescriptor by indicating the URL
 		xdaq::ContextDescriptor*  getContextDescriptor(const std::string & url) throw (xdaq::exception::HostNotFound);

		//! Retrieve all context descriptors
 		std::vector<xdaq::ContextDescriptor*>  getContextDescriptors();


		bool hasContextDescriptor(const std::string & url);

		private:

		std::map<std::string, xdaq::ContextDescriptor*, std::less<std::string> > contexts_;

	};
}

#endif
