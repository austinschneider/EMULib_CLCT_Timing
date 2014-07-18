/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_SelectResponse_h_
#define _ws_broker_utils_SelectResponse_h_

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
	class SelectResponse
	{
		public:
			SelectResponse();
			SelectResponse(xoap::MessageReference msg) throw(xoap::exception::Exception);
			virtual ~SelectResponse();

			void addServiceInformation(xdata::Table::Reference t);
			const std::list<xdata::Table::Reference> getServiceInformation();

			xoap::MessageReference toSOAP() throw(xoap::exception::Exception);
		private:
			std::list<xdata::Table::Reference> tables_;
	};
}
}
}
#endif

