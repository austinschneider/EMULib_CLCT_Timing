// $Id: xmas.h,v 1.3 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_xmas_h_
#define _xmas_xmas_h_

#include <string>

namespace xmas
{
   
	const std::string NamespacePrefix = "xmas";
	const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2006/xmas-10";

	namespace sensor
	{
		const std::string NamespacePrefix = "xmas-sensor";
		const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2006/xmas-sensor-10";
	}

	namespace pulser
	{
		const std::string NamespacePrefix = "xmas-pulser";
		const std::string NamespaceUri = "http://xdaq.web.cern.ch/xdaq/xsd/2006/xmas-pulser-10";
	}
}
#endif

