// $Id: FlashListMonitor.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_FlashListMonitor_h_
#define _xmas_probe_FlashListMonitor_h_

#include <string>
#include <map>
#include <vector>

#include "xmas/probe/MetricsScheduler.h"
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
#include "xmas/probe/MetricsScheduler.h"
#include "xmas/probe/exception/Exception.h"
#include "xmas/probe/exception/FlashListMonitorCreationFailed.h"
#include "xmas/probe/Sampler.h"
#include "xdaq/Object.h"
#include "xdaq/Application.h"

namespace xmas
{
	namespace probe
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
			throw (xmas::probe::exception::FlashListMonitorCreationFailed);
			
			std::list<xmas::probe::Sampler*> getSamplers();
			
			virtual ~FlashListMonitor();

			void incrementPulseCounter();
			void incrementFireCounter();
			void incrementInternalLossCounter();
			void incrementCommunicationLossCounter();
			void incrementMemoryLossCounter();
			void incrementUnassignedLossCounter();
			
			xdata::UnsignedInteger64T getPulseCounter();
			xdata::UnsignedInteger64T getFireCounter();
			xdata::UnsignedInteger64T getInternalLossCounter();
			xdata::UnsignedInteger64T getCommunicationLossCounter();
			xdata::UnsignedInteger64T getMemoryLossCounter();
			xdata::UnsignedInteger64T getUnassignedLossCounter();
			
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
				throw (xmas::probe::exception::Exception);
			
			bool resolveMultipleMetrics
				( 
			        	std::map<std::string, std::vector<xmas::ItemDefinition*> > & items,
					std::map<std::string, std::vector<xdata::InfoSpace*> >  & infospaces 
				)
				throw (xmas::probe::exception::Exception);
			
		
			xdata::Table::Reference retrieveMultipleMetrics
				(
			 		std::map<std::string, std::vector<xmas::ItemDefinition*> > & items,
					std::map<std::string, std::vector<xdata::InfoSpace*> >  & infospaces
				)
				throw (xmas::probe::exception::Exception);
				
			void addFunctionMetrics(xdata::Table::Reference & table)
				throw (xmas::probe::exception::Exception);
			
			/*	
			void calculateValue(const std::string& functionName, xdata::Serializable& s)
				throw (xmas::probe::exception::Exception);
			*/
			
			void actionPerformed( xdata::Event& event);
												
			std::string getFlashListName();
			
			xmas::FlashListDefinition* getFlashListDefinition();
			
			/*! Check if the FlashListMonitor can ressolve the provided infospace name */
			bool belongsTo (const std::string& infospace);
			
			protected:
			
			xdata::Serializable * eval (const std::string& functionName, const std::string& type) 
				throw (xmas::probe::exception::Exception);
			
			private:
			
			xmas::MonitorSettings * settings_;
			MetricsScheduler* scheduler_;

			xdata::UnsignedInteger64T monitorPulseCounter_;
			xdata::UnsignedInteger64T monitorFireCounter_;

			xdata::UnsignedInteger64T monitorInternalLossCounter_;
			xdata::UnsignedInteger64T monitorCommunicationLossCounter_;
			xdata::UnsignedInteger64T monitorMemoryLossCounter_;
			xdata::UnsignedInteger64T monitorUnassignedLossCounter_;
		};
	}
}
#endif


