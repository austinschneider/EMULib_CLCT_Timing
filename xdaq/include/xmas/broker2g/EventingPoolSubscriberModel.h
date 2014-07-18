/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_EventingPoolSubscriberModel_h_
#define _xmas_broker2g_EventingPoolSubscriberModel_h_

#include <string>
#include <map>

#include "xdata/Double.h"
#include "xdata/String.h"
#include "xdata/Table.h"
#include "xdata/Vector.h"
#include "xdata/Bag.h"
#include "xdata/Properties.h"

#include "xmas/broker2g/Model.h"

namespace xmas
{
namespace broker2g
{
	class EventingPoolSubscriberModel :
		public xmas::broker2g::Model
	{
		public:
			XMAS_BROKER2G_MODEL_INSTANTIATOR();

			EventingPoolSubscriberModel(xdaq::Application * owner, const std::string& name);

			virtual ~EventingPoolSubscriberModel();

			virtual void loaded() throw(xmas::broker2g::exception::ParserException);

			virtual void update(xdata::Table::Reference table) throw(xmas::broker2g::exception::ParserException);

			virtual xdata::Properties query(xdata::Properties& plist);

			virtual void cleanup(toolbox::TimeVal t);

			virtual void view(xgi::Output * out);
		private:
			std::map<std::string, xdata::Table::Reference> services_;

			xdata::UnsignedInteger32 requests_;
			xdata::UnsignedInteger32 results_;
	};
}
}
#endif

