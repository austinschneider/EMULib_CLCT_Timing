/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _b2in_eventing_Statistics_h_
#define _b2in_eventing_Statistics_h_

#include <list>
#include <string>

#include "toolbox/task/TimerListener.h"
#include "toolbox/ProcessInfo.h"
#include "toolbox/TimeVal.h"

//#include "xdaq/Object.h"
#include "xdaq/Application.h"

#include "xdata/InfoSpace.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Table.h"
#include "xdata/Vector.h"
#include "xdata/Double.h"
#include "xdata/String.h"

#include <map>

namespace b2in
{
	namespace eventing
	{
		class Statistics :
			xdata::ActionListener,
			toolbox::task::TimerListener
		{
			public:
				Statistics(xdaq::Application* app, const std::string & endpointURL);
				virtual ~Statistics();

				void addIncomingPacket(toolbox::TimeVal& receivetimestamp, size_t length, const std::string& sourceid );
				void addServiceTime(toolbox::TimeVal& receivetimestamp );
				void addLostPacket(size_t length);
				
				//void incQueueSize();
				//void decQueueSize();
				//xdata::UnsignedInteger32 getQueueSize();
				
				xdata::UnsignedInteger32 getTotalMessageCount();
				xdata::UnsignedInteger32 getTotalLostMessageCount();
				toolbox::TimeVal getLastMsgReceived();
				xdata::Double getRate(); // average rate over measurement period
				xdata::Double getMessageServiceTime(); // in seconds.milliseconds

			protected:
				void addServiceTime(const std::string& name, toolbox::TimeVal timedelta);
				void addComponent(const std::string& name);
				void updateStats();

				xdaq::Application* app_;
				xdata::InfoSpace* is_;
				toolbox::BSem mutex_;
				toolbox::ProcessInfo::Reference processinfo_;

				toolbox::TimeVal starttime_;
				toolbox::TimeVal lastMsgReceived_;

				// temporary counter variables for statistics data
				std::map<std::string, double> clients_;
				xdata::UnsignedInteger32 messagecount_;
				xdata::UnsignedInteger32 totalmessagecount_;
				xdata::UnsignedInteger32 datacount_;
				xdata::UnsignedInteger32 lostmessagecount_;
				xdata::UnsignedInteger32 totallostmessagecount_;
				xdata::UnsignedInteger32 lostdatacount_;
				xdata::UnsignedInteger32 queueSize_;
				xdata::Vector<xdata::UnsignedInteger32> messages_;
				xdata::Table components_;

				xdata::Vector<xdata::UnsignedInteger32> messagecounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> lostmessagecounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> datacounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> lostdatacounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> queuehisto_;

				// old snapshot of measurements in peer transport
				xdata::Double servicetimeincoming_;
				xdata::Double servicetimeoutgoing_;
			private:
				void actionPerformed (xdata::Event& e);
				void timeExpired (toolbox::task::TimerEvent& e);
		};
	}
}

#endif


