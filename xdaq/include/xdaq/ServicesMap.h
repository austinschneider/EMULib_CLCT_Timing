// $Id: ServicesMap.h,v 1.2 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ServicesMap_h_
#define _xdaq_ServicesMap_h_

#include <map>
#include <string>

#include "xdaq/exception/Exception.h"
#include "xoap/domutils.h"
namespace xdaq
{	
	const std::string  ServicesMapNamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2007/ServicesMap-10";
	
	class ServicesMap
	{
		public:
		
		void import(DOMDocument* document) throw (xdaq::exception::Exception);
		
		std::string getProfile(size_t port) throw (xdaq::exception::Exception);
		
		std::string getConfiguration(size_t port) throw (xdaq::exception::Exception);

		protected:

		bool hasDefault_;
		std::pair<std::string,std::string> default_;
		
		std::map<size_t, std::pair<std::string,std::string> > services_;
	
	};
}

#endif
