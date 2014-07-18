// $Id: MonitorReport.h,v 1.6 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_MonitorReport_h_
#define _xmas_sensor_MonitorReport_h_

#include <string>
#include <map>
#include "xdata/Table.h"
#include "xmas/FlashListDefinition.h"
#include "xmas/exception/Exception.h"

namespace xmas
{
	namespace sensor
	{
		class MonitorReport: public toolbox::Properties
		{
			public:
			
			MonitorReport
			(
				xmas::FlashListDefinition* definition
			);
			
			/* Destructor of the report deletes the tables that have passed to it */
			virtual ~MonitorReport();
			
			std::map<std::string, xdata::Table::Reference> getMetrics();
			
			void addMetrics (const std::string& name, xdata::Table::Reference & table)
				throw (xmas::exception::Exception);
				
			std::string getFlashListName();
			
			xmas::FlashListDefinition* getFlashListDefinition();
			
			private:
			
			std::map<std::string, xdata::Table::Reference> metrics_;
			std::string name_;
			xmas::FlashListDefinition* flashListDefinition_;
		};
	}
}
#endif
