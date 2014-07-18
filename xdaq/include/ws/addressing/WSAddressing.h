// $Id: WSAddressing.h,v 1.5 2008/07/18 15:27:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_addressing_WSAddressing_h_
#define _ws_addressing_WSAddressing_h_

#include <string>

namespace ws
{
	namespace addressing
	{

	       const std::string NamespacePrefix = "wsa";
	       const std::string NamespaceUri[] = { "http://schemas.xmlsoap.org/ws/2004/08/addressing", "http://www.w3.org/2005/08/addressing" };
         const size_t NamespaceVersions = 2;
	}
}

#endif


