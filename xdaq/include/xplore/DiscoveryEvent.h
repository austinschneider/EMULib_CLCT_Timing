// $Id: DiscoveryEvent.h,v 1.5 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_DiscoveryEvent_h_
#define _xplore_DiscoveryEvent_h_

#include <string>
#include <vector>

#include "toolbox/Event.h"
#include "xplore/Advertisement.h"

namespace xplore 
{

class DiscoveryEvent: public toolbox::Event
{
	public:
		
	DiscoveryEvent(std::vector<xplore::Advertisement::Reference>& resultSet, 
					const std::string& service,
					const std::string& filter)
		: toolbox::Event("xplore::DiscoveryEvent", 0),
		resultSet_(resultSet),
		service_(service),
		filter_(filter)
	{
	}
	
	DiscoveryEvent(std::vector<xplore::Advertisement::Reference>& resultSet, 
			void* originator,
			const std::string& service,
			const std::string& filter)
		: toolbox::Event("xplore::DiscoveryEvent", originator), 
		resultSet_(resultSet),
		service_(service),
		filter_(filter)
	{
	}
	
	std::vector<xplore::Advertisement::Reference> & getResultSet()
	{
		return resultSet_;
	}
	
	std::string& getService()
	{
		return service_;
	}
	
	std::string& getFilter()
	{
		return filter_;
	}
		
	protected:
	
	std::vector<xplore::Advertisement::Reference> & resultSet_;
	std::string service_;
	std::string filter_;
	
};

}

#endif
