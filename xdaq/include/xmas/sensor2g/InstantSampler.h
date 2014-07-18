// $Id: InstantSampler.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor2g_InstantSampler_h_
#define _xmas_sensor2g_InstantSampler_h_

#include <string>
#include "toolbox/Event.h"
#include "xmas/sensor2g/exception/Exception.h"
#include "xmas/SamplerSettings.h"
#include "xmas/sensor2g/Sampler.h"
#include "xmas/sensor2g/Repository.h"
#include "xmas/FlashListDefinition.h"

namespace xmas
{
	namespace sensor2g
	{
		class InstantSampler: public Sampler
		{
			public:
			
			std::string type();
			
			InstantSampler(xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld);
			
		 	xmas::sensor2g::MonitorReport  getMetrics();
			
			void actionPerformed(toolbox::Event & e);
			
			double getLatency();
			
			protected:
			
			xmas::sensor2g::Repository repository_;			
		};
	}
}
#endif

