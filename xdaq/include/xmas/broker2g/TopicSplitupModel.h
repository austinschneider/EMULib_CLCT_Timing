/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_TopicSplitupModel_h_
#define _xmas_broker2g_TopicSplitupModel_h_

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
	class TopicSplitupModel :
		public xmas::broker2g::Model
	{
		public:
			XMAS_BROKER2G_MODEL_INSTANTIATOR();

			TopicSplitupModel(xdaq::Application * owner, const std::string& name);

			virtual ~TopicSplitupModel();

			virtual void loaded() throw(xmas::broker2g::exception::ParserException);

			virtual void update(xdata::Table::Reference table) throw(xmas::broker2g::exception::ParserException);

			virtual xdata::Properties query(xdata::Properties& plist);

			virtual void cleanup(toolbox::TimeVal t);

			virtual void view(xgi::Output * out);
		private:
			std::map<std::string, std::vector<xmas::broker2g::SensorSettings*> > sensorSettings_;
			std::map<std::string, size_t > sensorCounts_;

			xdata::String settings_;

			xdata::UnsignedInteger32 requests_;
	};
}
}
#endif

