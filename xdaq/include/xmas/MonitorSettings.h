// $Id: MonitorSettings.h,v 1.5 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_MonitorSettings_h_
#define _xmas_MonitorSettings_h_

#include <vector>
#include <map>
#include <string>
#include "xmas/SamplerSettings.h"
#include "xmas/FlashListDefinition.h"
#include "xmas/exception/Exception.h"
#include "toolbox/Properties.h"
#include "toolbox/net/UUID.h"

namespace xmas
{	
	class MonitorSettings: public toolbox::Properties
	{
		public:
		
		MonitorSettings(DOMNode* monitor) throw (xmas::exception::Exception);
		
		~MonitorSettings();

		toolbox::net::UUID& getId();


		SamplerSettings * createSamplerSettings() throw (xmas::exception::Exception);
		
		SamplerSettings * createSamplerSettings(DOMNode* sampleNode) throw (xmas::exception::Exception);
		
		void removeSamplerSettings(toolbox::net::UUID & id)  throw (xmas::exception::Exception);
		
		SamplerSettings* getSamplerSettings(toolbox::net::UUID & id) throw (xmas::exception::Exception);
		
		std::vector<SamplerSettings*> getSamplerSettings();
		
		xmas::FlashListDefinition * getFlashListDefinition();

		protected:

		std::map<toolbox::net::UUID, SamplerSettings*> samplerSettings_;
		xmas::FlashListDefinition * flashListDefinition_;
		toolbox::net::UUID id_;		

	};
}

#endif
