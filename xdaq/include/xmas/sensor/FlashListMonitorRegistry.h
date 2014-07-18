// $Id: FlashListMonitorRegistry.h,v 1.9 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_FlashListMonitorFactory_h_
#define _xmas_sensor_FlashListMonitorFactory_h_

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "xmas/FlashListDefinition.h"
#include "xmas/MonitorSettings.h"
#include "xmas/sensor/FlashListMonitor.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "xmas/sensor/exception/FlashListMonitorCreationFailed.h"
#include "xmas/sensor/exception/FlashListMonitorDeletionFailed.h"
#include "xmas/sensor/exception/FlashListMonitorNotFound.h"
#include "toolbox/net/UUID.h"
#include "toolbox/BSem.h"
#include "xdaq/Object.h"

namespace xmas
{
	namespace sensor
	{		
		class FlashListMonitorRegistry: public xdaq::Object
		{
			public:			
			
			FlashListMonitorRegistry(xdaq::Application* owner);
			
			~FlashListMonitorRegistry();
			
			void lock();
			
			void unlock();
			
			bool exists(const std::string& name);

			std::vector<xmas::sensor::FlashListMonitor*> getFlashListMonitors();

			std::vector<xmas::sensor::FlashListMonitor*> getFlashListMonitors
				(const std::string& infospace);

			xmas::sensor::FlashListMonitor* get(const std::string& name)
				throw (xmas::sensor::exception::FlashListMonitorNotFound);
						
			xmas::sensor::FlashListMonitor*
				install (xmas::MonitorSettings* settings, xmas::sensor::MetricsScheduler * scheduler)
				throw (xmas::sensor::exception::FlashListMonitorCreationFailed);
								
			void uninstall(const std::string& name)
				throw (xmas::sensor::exception::FlashListMonitorDeletionFailed);
			
			private:
						
			std::map<std::string, xmas::sensor::FlashListMonitor*> monitors_;
			toolbox::BSem mutex_;			
		};
	}
}
#endif


