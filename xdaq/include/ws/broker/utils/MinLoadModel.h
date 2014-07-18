/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_MinLoadModel_h_
#define _ws_broker_utils_MinLoadModel_h_

#include <string>
#include <map>

#include "xdata/Double.h"
#include "xdata/String.h"
#include "xdata/Table.h"

#include "ws/broker/utils/Model.h"

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class MinLoadModel :
		public ws::broker::utils::Model
	{
		public:
			WS_BROKER_UTILS_MODEL_INSTANTIATOR();

			MinLoadModel(const std::string& name);

			virtual ~MinLoadModel();

			virtual void update(xdata::Table::Reference table) throw(ws::broker::utils::exception::ParserException);

			virtual std::list<xdata::Table::Reference> get();

			virtual std::list<xdata::Table::Reference> select(const ws::broker::utils::InfoRecord &info);

			virtual void cleanup(toolbox::TimeVal t);

		private:
			std::map<std::string, xdata::Table::Reference> services_;

			xdata::String service_;
			xdata::String group_;
			xdata::Double maximumLoad_;
			xdata::Double increaseLoad_;
	};
}
}
}
#endif

