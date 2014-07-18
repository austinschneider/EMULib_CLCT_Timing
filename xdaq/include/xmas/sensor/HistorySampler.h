// $Id: HistorySampler.h,v 1.9 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_HistorySampler_h_
#define _xmas_sensor_HistorySampler_h_

#include <string>
#include "toolbox/ActionListener.h"
#include "toolbox/Event.h"
#include "xdata/Table.h"
#include "xmas/sensor/Sampler.h"
#include "xmas/SamplerSettings.h"
#include "xmas/sensor/exception/Exception.h"
#include "xmas/sensor/Repository.h"
#include "xmas/FlashListDefinition.h"

namespace xmas
{
	namespace sensor
	{
		class HistorySampler: public Sampler
		{
			public:
			
			std::string type();
			
			HistorySampler(xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld);
			
			void actionPerformed(toolbox::Event & e);
			
			xmas::sensor::MonitorReport  getMetrics();
			
			double getLatency();
			
			protected:
			
			xmas::sensor::Repository repository_;
			toolbox::TimeVal cursor_;	
		};
	}
}
#endif

