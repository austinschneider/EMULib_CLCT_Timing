// $Id: FlashListMonitorRegistry.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_FlashListMonitorFactory_h_
#define _xmas_probe_FlashListMonitorFactory_h_

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "xmas/FlashListDefinition.h"
#include "xmas/MonitorSettings.h"
#include "xmas/probe/FlashListMonitor.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "xmas/probe/exception/FlashListMonitorCreationFailed.h"
#include "xmas/probe/exception/FlashListMonitorDeletionFailed.h"
#include "xmas/probe/exception/FlashListMonitorNotFound.h"
#include "toolbox/net/UUID.h"
#include "toolbox/BSem.h"
#include "xdaq/Object.h"

namespace xmas
{
	namespace probe
	{		
		class FlashListMonitorRegistry: public xdaq::Object
		{
			public:			
			
			FlashListMonitorRegistry(xdaq::Application* owner);
			
			~FlashListMonitorRegistry();
			
			void lock();
			
			void unlock();
			
			bool exists(const std::string& name);

			std::vector<xmas::probe::FlashListMonitor*> getFlashListMonitors();

			std::vector<xmas::probe::FlashListMonitor*> getFlashListMonitors
				(const std::string& infospace);

			xmas::probe::FlashListMonitor* get(const std::string& name)
				throw (xmas::probe::exception::FlashListMonitorNotFound);
						
			xmas::probe::FlashListMonitor*
				install (xmas::MonitorSettings* settings, xmas::probe::MetricsScheduler * scheduler)
				throw (xmas::probe::exception::FlashListMonitorCreationFailed);
								
			void uninstall(const std::string& name)
				throw (xmas::probe::exception::FlashListMonitorDeletionFailed);
			
			private:
						
			std::map<std::string, xmas::probe::FlashListMonitor*> monitors_;
			toolbox::BSem mutex_;			
		};
	}
}
#endif


