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

#ifndef _xmas_probe_InstantSampler_h_
#define _xmas_probe_InstantSampler_h_

#include <string>
#include "toolbox/Event.h"
#include "xmas/probe/exception/Exception.h"
#include "xmas/SamplerSettings.h"
#include "xmas/probe/Sampler.h"
#include "xmas/probe/Repository.h"
#include "xmas/FlashListDefinition.h"

namespace xmas
{
	namespace probe
	{
		class InstantSampler: public Sampler
		{
			public:
			
			std::string type();
			
			InstantSampler(xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld);
			
		 	xmas::probe::MonitorReport  getMetrics();
			
			void actionPerformed(toolbox::Event & e);
			
			double getLatency();
			
			protected:
			
			xmas::probe::Repository repository_;			
		};
	}
}
#endif

