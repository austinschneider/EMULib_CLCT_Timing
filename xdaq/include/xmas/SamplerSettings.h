// $Id: SamplerSettings.h,v 1.5 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_SamplerSettings_h_
#define _xmas_SamplerSettings_h_

#include <vector>
#include <map>
#include <string>
#include "xmas/exception/Exception.h"
// #include "xmas/PublisherSettings.h"
#include "toolbox/net/UUID.h"
#include "toolbox/Properties.h"
#include "xoap/domutils.h"

namespace xmas
{
	
	class SamplerSettings: public toolbox::Properties
	{
		public:
		
		SamplerSettings() throw (xmas::exception::Exception);
		
		SamplerSettings( DOMNode* sampleNode ) throw (xmas::exception::Exception);
		
		~SamplerSettings();

		toolbox::net::UUID& getId();
		
		/*
		PublisherSettings * createPublisherSettings() throw (xmas::exception::Exception);
		
		PublisherSettings * createPublisherSettings(DOMNode* publishNode) throw (xmas::exception::Exception);
		
		void removePublisherSettings(toolbox::net::UUID & id)  throw (xmas::exception::Exception);
		
		PublisherSettings * getPublisherSettings(toolbox::net::UUID & id)  throw (xmas::exception::Exception);
		
		std::vector<PublisherSettings*> getPublisherSettings();
		*/

		protected:

		// std::map<toolbox::net::UUID, xmas::PublisherSettings*> publishList_;
		toolbox::net::UUID id_;		
	};
}
#endif
