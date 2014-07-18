// $Id: Application.h,v 1.14 2008/11/14 14:35:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_Application_h_
#define _xmas_probe_Application_h_

#include <string>
#include "xdaq/ApplicationDescriptorImpl.h" 
#include "xdaq/Application.h" 
#include "xdaq/ApplicationContext.h" 
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Boolean.h"
#include "xdata/Double.h"
#include "xdata/ActionListener.h"
#include "xdata/exdr/Serializer.h"

#include "xgi/Method.h"
#include "xgi/Utils.h"
#include "xgi/exception/Exception.h"
#include "xmas/PulserSettings.h"
#include "xmas/exception/Exception.h"
#include "xmas/probe/FlashListMonitorRegistry.h"
#include "xmas/probe/MetricsScheduler.h"
#include "xmas/probe/MonitorReportEvent.h"

#include "xmas/probe/exception/DuplicateConsumer.h"
#include "xmas/probe/exception/ConsumerNotFound.h"
#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/task/TimerListener.h"
#include "toolbox/mem/Pool.h"

#include "b2in/nub/Method.h"
#include "b2in/utils/MessengerCache.h"

namespace xmas 
{
	namespace probe
	{
	
		class Application
			:public xdaq::Application, 
			 public toolbox::ActionListener, 
			 public xdata::ActionListener,
			 public toolbox::task::TimerListener,
			 public b2in::utils::MessengerCacheListener
		{
		
			public:

			XDAQ_INSTANTIATOR();

			Application(xdaq::ApplicationStub* s) throw (xdaq::exception::Exception);
			~Application();

			void actionPerformed ( xdata::Event& e );
			
			void actionPerformed( toolbox::Event& event );
			void timeExpired(toolbox::task::TimerEvent& e);

			
			void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
			void browseSelection(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

				

					
			protected:
			
			void FlashlistsTabPage( xgi::Output * out );
			void StatisticsTabPage( xgi::Output * out );
			void InfospacesTabPage( xgi::Output * out );
			void TabPanel( xgi::Output * out );

			private:
			void heartbeat();
			void publishReport(xmas::probe::MonitorReportEvent & report);
			void loadPulserEvents(const std::string& path) throw (xmas::probe::exception::Exception);
			void schedulePulseEvents(toolbox::task::Timer * timer);
			void processPulse (const std::string& flashListName, const std::string& tagName) throw (xmas::probe::exception::Exception);
			void asynchronousExceptionNotification(xcept::Exception& e);


			std::set<std::string> scanLocalServices();
			void applySensorSettings(const std::string & path);

			void displayTableToCSV( xdata::Table*  table );
			
			xdata::Vector<xdata::String> settingsURLs_; // path pattern for configuration file
			
			xmas::probe::FlashListMonitorRegistry flashListMonitorRegistry_;
			xmas::probe::MetricsScheduler scheduler_;
						
			xdata::String publishGroup_;
			xdata::String heartbeatGroup_;
			
			xdata::Boolean autoConfigure_;
			xdata::String autoConfSearchPath_;
			toolbox::task::AsynchronousEventDispatcher dispatcher_;			
			
			// cgi
			std::string selectedInfoSpace_; // remember last selected InfoSpace in combo box
			std::vector<std::string> monitorableSearchModes_; // the possible search modes (startsWith, endsWith, contains)
			std::string selectedFlashList_; // remember last selected FlashList in combo box
			std::string selectedMonitorableSearchMode_; // last selected search mode
			std::string selectedMonitorableSearchString_;
			xdata::UnsignedInteger32  lossReportCounter_; // only print send errors every (msg % lossReportCounter) = 1		
			
			xdata::String  heartbeatWatchdog_;

			
			xdata::exdr::Serializer serializer_;
			toolbox::mem::Pool* pool_;
			xmas::PulserSettings pulserSettings_;
			
			bool deadBand_;
			xdata::Double committedPoolSize_;
			xdata::Double highThreshold_;
			xdata::Double lowThreshold_;
			xdata::UnsignedInteger32 maxReportMessageSize_;

			 b2in::utils::MessengerCache * sensorMessengerCache_;
			xdata::UnsignedInteger64 outgoingHeartbeatCounter_;
			xdata::UnsignedInteger64 outgoingHeartbeatLostCounter_;
			xdata::UnsignedInteger64 outgoingReportLostCounter_;
			xdata::UnsignedInteger64 outgoingReportCounter_;

		};
	}
}
#endif
