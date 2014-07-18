// $Id: URI.h,v 1.3 2008/07/18 15:27:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_URI_h_
#define _toolbox_net_URI_h_

#include "toolbox/net/URL.h"

namespace toolbox {
namespace net {

/**
 * The class URI is for the time being the same as the class URL.
 * See class URN for more information on this.
 */
class URI: public URL 
{
  public:

    URI(const std::string& uri) throw (toolbox::exception::Exception): URL(uri)
	{

	}
};

}}

#endif
