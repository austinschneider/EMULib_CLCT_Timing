// $Id: Sentinel.h,v 1.6 2008/07/18 15:27:25 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_h_
#define _sentinel_h_

#include <string>

namespace sentinel
{
       const std::string NamespacePrefix = "en";
       const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2005/ErrorNotification-11.xsd";
       
	namespace qualified
	{
		const std::string NamespacePrefix = "qen";
		const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2007/QualifiedSoftwareErrorRecord-11.xsd";
	}
	
	namespace news
	{
		const std::string NamespacePrefix = "sn";
		const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2008/SentinelNews-10.xsd";
	}
}

#endif


