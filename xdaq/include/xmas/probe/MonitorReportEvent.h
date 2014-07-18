// $Id: MonitorReportEvent.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_MonitorReportEvent_h_
#define _xmas_probe_MonitorReportEvent_h_

#include <string>
#include <map>
#include "toolbox/Event.h"
#include "xdata/Table.h"
#include "xmas/FlashListDefinition.h"
#include "xmas/exception/Exception.h"
#include "xmas/probe/MonitorReport.h"

namespace xmas
{
	namespace probe
	{
		class MonitorReportEvent: public xmas::probe::MonitorReport, public toolbox::Event
		{
			public:
			
			MonitorReportEvent(xmas::FlashListDefinition* definition);
			
			~MonitorReportEvent();
			
			std::string name_;
		
		};
	}
}
#endif
