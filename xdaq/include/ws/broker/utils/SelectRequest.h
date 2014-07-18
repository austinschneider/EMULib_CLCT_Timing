/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_SelectRequest_h_
#define _ws_broker_utils_SelectRequest_h_

#include "ws/broker/utils/InfoRecord.h"

#include <string>

#include "xoap/SOAPMessage.h"
#include "xoap/MessageReference.h"

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class SelectRequest
	{
		public:
			SelectRequest();
			SelectRequest(xoap::MessageReference msg) throw(xoap::exception::Exception);
			virtual ~SelectRequest();

			void setInfoRecord(const ws::broker::utils::InfoRecord& info);
			const ws::broker::utils::InfoRecord& getInfoRecord();

			xoap::MessageReference toSOAP() throw(xoap::exception::Exception);
		private:
			ws::broker::utils::InfoRecord info_;
	};
}
}
}
#endif

