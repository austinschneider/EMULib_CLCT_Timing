// $Id: DescriptorsCache.h,v 1.2 2008/07/18 15:28:46 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_utils_DescriptorsCache_h_
#define _xplore_utils_DescriptorsCache_h_

#include <string>
#include <list>

#include "toolbox/ActionListener.h"
#include "toolbox/BSem.h"
#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Application.h" 
#include "xdaq/Object.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdaq/ContextTable.h"


namespace xplore 
{
	namespace utils 
	{
		class DescriptorsCache : public xdaq::Object, public toolbox::ActionListener
		{
			public:
			
			DescriptorsCache(xdaq::Application* owner);

			void actionPerformed( toolbox::Event& event );

			std::list<xdaq::ApplicationDescriptorImpl> getDescriptors(std::set<std::string>& groups, const std::string & service);
						
			private:

			std::list<xdaq::ApplicationDescriptor*> services_; 
			xdaq::ContextTable discoveredContexts_; 
			toolbox::BSem mutex_;			
		};
	}
}
#endif
