// $Id: HashSampler.h,v 1.6 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_HashSampler_h_
#define _xmas_sensor_HashSampler_h_

#include <string>
#include "toolbox/Event.h"
#include "xmas/sensor/exception/Exception.h"
#include "xmas/SamplerSettings.h"
#include "xmas/sensor/Sampler.h"
#include "xmas/FlashListDefinition.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/BSem.h"
#include "xdaq/Object.h"

namespace xmas
{
	namespace sensor
	{
		class HashSampler: public Sampler,  public toolbox::task::TimerListener, public xdaq::Object
		{
			public:
			
			std::string type();
			
			HashSampler(xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld, xdaq::Application * owner);
			
		 	xmas::sensor::MonitorReport  getMetrics();
			
			void actionPerformed(toolbox::Event & e);
			
			void timeExpired(toolbox::task::TimerEvent& e);
			
			double getLatency();

			protected:
			
			xdata::Table::Reference current_;
			toolbox::BSem mutex_;
			std::vector<double> incomingReportTimes_;		
		};
	}
}
#endif

