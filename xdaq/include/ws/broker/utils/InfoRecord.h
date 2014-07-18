/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_InfoRecord_h_
#define _ws_broker_utils_InfoRecord_h_

#include <string>
#include <map>

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class InfoRecord
	{
		public:
			InfoRecord();
			virtual ~InfoRecord();

			bool matching(xdata::Table::Reference t) const throw(xdata::exception::Exception);

			const std::string& getProfile() const;
			const std::string& getService() const;
			const std::string& getGroup() const;

			void setProfile(const std::string& value);
			void setService(const std::string& value);
			void setGroup(const std::string& value);
		private:
			std::string profile_;
			std::string service_;
			std::string group_;
	};
}
}
}
#endif

