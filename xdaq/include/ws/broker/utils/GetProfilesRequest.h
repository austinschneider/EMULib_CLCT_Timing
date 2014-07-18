/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_GetProfilesRequest_h_
#define _ws_broker_utils_GetProfilesRequest_h_

#include <string>
#include <map>

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"

#include "xoap/SOAPMessage.h"
#include "xoap/MessageReference.h"

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class GetProfilesRequest
	{
		public:
			GetProfilesRequest();
			GetProfilesRequest(xoap::MessageReference msg) throw(xoap::exception::Exception);
			virtual ~GetProfilesRequest();

			xoap::MessageReference toSOAP();
	};
}
}
}
#endif

