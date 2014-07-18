// $Id: FlashListMonitor.h,v 1.20 2008/07/18 15:28:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_sensor_FlashListMonitor_h_
#define _xmas_sensor_FlashListMonitor_h_

#include <string>
#include <map>
#include <vector>

#include "xmas/sensor/MetricsScheduler.h"
#include "toolbox/Properties.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/ActionListener.h"
#include "toolbox/ActionListener.h"

#include "xdata/Table.h"
#include "xdata/InfoSpace.h"
#include "xdata/Event.h"

// For calculating functions
#include "xdata/Serializable.h"
#include "xdata/String.h"
#include "xdata/TimeVal.h"
#include "xmas/MonitorSettings.h"
#include "xmas/FlashListDefinition.h"
#include "xmas/sensor/MetricsScheduler.h"
#include "xmas/sensor/exception/Exception.h"
#include "xmas/sensor/exception/FlashListMonitorCreationFailed.h"
#include "xmas/sensor/Sampler.h"
#include "xdaq/Object.h"
#include "xdaq/Application.h"

namespace xmas
{
	namespace sensor
	{
		
		/*! This class is the source of the monitoring data for one flashlist.
		    An object of this class is instantiated for each flashlist
		*/
		class FlashListMonitor: public xdata::ActionListener, 
			public toolbox::EventDispatcher,
			public xdaq::Object
		{
			public:
			
			
			FlashListMonitor
			(
				xmas::MonitorSettings * settings, 
				MetricsScheduler* scheduler,
				xdaq::Application * a
			) 
			throw (xmas::sensor::exception::FlashListMonitorCreationFailed);
			
			std::list<xmas::sensor::Sampler*> getSamplers();
			
			virtual ~FlashListMonitor();
			
			void incrementLossCounter();
			
			xdata::UnsignedInteger64T getLossCounter();
			
			void attachToInfospace(xdata::InfoSpace* infospace);
			
			bool resolveSingleMetrics
				( 
			                   std::vector<xmas::ItemDefinition*>& items,
					   xdata::InfoSpace* infospaces
				);
			
		
			xdata::Table::Reference retrieveSingleMetrics
				(
			 		std::vector<xmas::ItemDefinition*>& items,
					xdata::InfoSpace* infospaces
				)
				throw (xmas::sensor::exception::Exception);
			
			bool resolveMultipleMetrics
				( 
			        	std::map<std::string, std::vector<xmas::ItemDefinition*> > & items,
					std::map<std::string, std::vector<xdata::InfoSpace*> >  & infospaces 
				)
				throw (xmas::sensor::exception::Exception);
			
		
			xdata::Table::Reference retrieveMultipleMetrics
				(
			 		std::map<std::string, std::vector<xmas::ItemDefinition*> > & items,
					std::map<std::string, std::vector<xdata::InfoSpace*> >  & infospaces
				)
				throw (xmas::sensor::exception::Exception);
				
			void addFunctionMetrics(xdata::Table::Reference & table)
				throw (xmas::sensor::exception::Exception);
			
			/*	
			void calculateValue(const std::string& functionName, xdata::Serializable& s)
				throw (xmas::sensor::exception::Exception);
			*/
			
			void actionPerformed( xdata::Event& event);
												
			std::string getFlashListName();
			
			xmas::FlashListDefinition* getFlashListDefinition();
			
			/*! Check if the FlashListMonitor can ressolve the provided infospace name */
			bool belongsTo (const std::string& infospace);
			
			protected:
			
			xdata::Serializable * eval (const std::string& functionName, const std::string& type) 
				throw (xmas::sensor::exception::Exception);
			
			private:
			
			xmas::MonitorSettings * settings_;
			MetricsScheduler* scheduler_;
			xdata::UnsignedInteger64T monitorReportLossCounter_;
		};
	}
}
#endif


