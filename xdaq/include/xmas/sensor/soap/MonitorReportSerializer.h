// $Id: MonitorReportSerializer.h,v 1.3 2008/07/18 15:28:30 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_soap_MonitorReportSerializer_h_
#define _xmas_sensor_soap_MonitorReportSerializer_h_

#include "xmas/sensor/MonitorReport.h"
#include "xoap/MessageReference.h"
#include "xmas/exception/Exception.h"
#include "xmas/sensor/exception/Exception.h"
#include "toolbox/net/URL.h"
#include <string>

namespace xmas
{
	namespace sensor
	{
		namespace soap
		{
			class MonitorReportSerializer
			{
				public:

				MonitorReportSerializer ();

				virtual ~MonitorReportSerializer();

				void serialize
				( 
					xmas::sensor::MonitorReport & report, 
					xoap::MessageReference & msg, 
					toolbox::net::URL & url,
					const std::string& xmlTagName 
				) throw (xmas::sensor::exception::Exception);
		
			};
		}
	}
}
#endif
