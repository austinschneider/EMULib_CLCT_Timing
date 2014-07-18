/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_MinLoadModel_h_
#define _xmas_broker2g_MinLoadModel_h_

#include <string>
#include <map>
#include <vector>

#include "xdata/Double.h"
#include "xdata/String.h"
#include "xdata/Table.h"
#include "xdata/Vector.h"
#include "xdata/Bag.h"
#include "xdata/Properties.h"

#include "xmas/broker2g/Model.h"
#include "xmas/broker2g/SensorSettings.h"

namespace xmas
{
namespace broker2g
{
	class MinLoadModel :
		public xmas::broker2g::Model
	{
		public:
			XMAS_BROKER2G_MODEL_INSTANTIATOR();

			MinLoadModel(xdaq::Application * owner, const std::string& name);

			virtual ~MinLoadModel();

			virtual void loaded() throw(xmas::broker2g::exception::ParserException);

			virtual void update(xdata::Table::Reference table) throw(xmas::broker2g::exception::ParserException);

			virtual xdata::Properties query(xdata::Properties& plist);

			virtual void cleanup(toolbox::TimeVal t);

			virtual void view(xgi::Output * out);
		private:
			std::map<std::string, xdata::Table::Reference> services_;
			std::map<std::string, std::vector<xmas::broker2g::SensorSettings*> > sensorSettings_;
			std::map<std::string, size_t > sensorCounts_;

			xdata::String settings_;
			xdata::String service_;
			xdata::String group_;
			xdata::Double maximumLoad_;
			xdata::Double increaseLoad_;
			xdata::UnsignedInteger32 maximumClients_;

			xdata::UnsignedInteger32 requests_;
			xdata::UnsignedInteger32 results_;
	};
}
}
#endif

