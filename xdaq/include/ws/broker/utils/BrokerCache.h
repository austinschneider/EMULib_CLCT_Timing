// $Id: BrokerCache.h,v 1.2 2008/04/21 11:59:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_BrokerCache_h_
#define _ws_broker_utils_BrokerCache_h_

#include <string>
#include <list>

#include "ws/broker/utils/InfoRecord.h"
#include "ws/broker/utils/exception/BrokerException.h"
#include "ws/broker/utils/exception/DescriptorCreationException.h"
#include "ws/broker/utils/exception/ServiceNotFoundException.h"

#include "xdaq/Application.h"
#include "xdaq/ApplicationDescriptorImpl.h"
#include "xdaq/ContextTable.h"

#include "xdata/Table.h"

#include "toolbox/BSem.h"

namespace ws
{
namespace broker
{
namespace utils
{
	class BrokerCache
	{     
		public:
			BrokerCache();
			virtual ~BrokerCache();

			void setProfile(const std::string& profile);
			void setBroker(xdaq::ApplicationDescriptorImpl& broker);

			xdaq::ApplicationDescriptorImpl getApplication(
				xdaq::Application& app, const std::string& group, const std::string& service, bool queryBroker)
			  throw(ws::broker::utils::exception::BrokerException, ws::broker::utils::exception::ServiceNotFoundException);

			void removeApplication(const std::string& group, const std::string& service)
				throw(ws::broker::utils::exception::ServiceNotFoundException);

		protected:

			std::list<xdata::Table::Reference> select(xdaq::Application& app, const ws::broker::utils::InfoRecord& info)
			  throw(ws::broker::utils::exception::BrokerException);

			xdaq::ApplicationDescriptorImpl* createApplicationDescriptor(xdata::Table::Reference t)
			  throw(ws::broker::utils::exception::DescriptorCreationException);

			std::list<xdaq::ApplicationDescriptorImpl*> services_;
			xdaq::ContextTable contextTable_;
			std::string profile_;
			xdaq::ApplicationDescriptorImpl* broker_;

			toolbox::BSem mutex_;
	};
}}
}

#endif

