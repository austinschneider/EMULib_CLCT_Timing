// $Id: InstantSampler.h,v 1.6 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_InstantSampler_h_
#define _xmas_sensor_InstantSampler_h_

#include <string>
#include "toolbox/Event.h"
#include "xmas/sensor/exception/Exception.h"
#include "xmas/SamplerSettings.h"
#include "xmas/sensor/Sampler.h"
#include "xmas/sensor/Repository.h"
#include "xmas/FlashListDefinition.h"

namespace xmas
{
	namespace sensor
	{
		class InstantSampler: public Sampler
		{
			public:
			
			std::string type();
			
			InstantSampler(xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld);
			
		 	xmas::sensor::MonitorReport  getMetrics();
			
			void actionPerformed(toolbox::Event & e);
			
			double getLatency();
			
			protected:
			
			xmas::sensor::Repository repository_;			
		};
	}
}
#endif

