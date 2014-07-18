// $Id: Sampler.h,v 1.7 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_Sampler_h_
#define _xmas_sensor_Sampler_h_

#include <list>
#include <string>
#include "xmas/SamplerSettings.h"
#include "toolbox/ActionListener.h"
#include "toolbox/EventDispatcher.h"
#include "xmas/sensor/MonitorReport.h"
#include "xmas/FlashListDefinition.h"
#include "toolbox/string.h"

namespace xmas
{
	namespace sensor
	{		
		class Sampler: public toolbox::ActionListener, public toolbox::EventDispatcher
		{
			public:
			
			Sampler (xmas::SamplerSettings* settings, xmas::FlashListDefinition* fld);
			
			xmas::SamplerSettings* getSettings();
						
			virtual ~Sampler ();
			
			virtual std::string type() = 0;
			
			virtual xmas::sensor::MonitorReport  getMetrics() = 0;
			
			std::set<std::string>& getTagSet();
			
			bool hasTag (const std::string& tag);
			
			xmas::FlashListDefinition* getFlashListDefinition();
			
			virtual double getLatency() = 0;
			
			protected:
			
			xmas::SamplerSettings* settings_;
			std::set<std::string> tag_;
			xmas::FlashListDefinition* definition_;	
		};
	}
}
#endif

