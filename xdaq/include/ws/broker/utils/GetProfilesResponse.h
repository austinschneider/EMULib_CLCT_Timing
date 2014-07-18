/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_GetProfilesResponse_h_
#define _ws_broker_utils_GetProfilesResponse_h_

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
	class GetProfilesResponse
	{
		public:
			GetProfilesResponse();
			GetProfilesResponse(xoap::MessageReference msg) throw(xoap::exception::Exception);
			virtual ~GetProfilesResponse();

			void addProfile(const std::string& value);
			const std::list<std::string>& getProfiles();

			xoap::MessageReference toSOAP();
		private:
			std::list<std::string> profiles_;
	};
}
}
}
#endif

