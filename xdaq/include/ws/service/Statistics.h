/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_service_Statistics_h_
#define _ws_service_Statistics_h_

#include <list>
#include <string>

#include "ws/eventing/exception/Exception.h"

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

#include "xoap/MessageReference.h"

#include <map>

namespace ws
{
	namespace service
	{
		class Statistics :
			xdata::ActionListener,
			toolbox::task::TimerListener
		{
			public:
				Statistics(xdaq::Application* app);
				virtual ~Statistics();

				void addIncomingPacket(const std::string& name, xoap::MessageReference msg, bool processing);
				void addServiceTime(const std::string& name, toolbox::TimeVal timedelta);
				void addComponent(const std::string& name);

				void incQueueSize();
				void decQueueSize();
				xdata::UnsignedInteger32 getQueueSize();

			protected:
				void updateStats();

				xdaq::Application* app_;
				xdata::InfoSpace* is_;
				toolbox::BSem mutex_;
				toolbox::ProcessInfo::Reference processinfo_;

				toolbox::TimeVal starttime_;

				// temporary counter variables for statistics data
				std::map<std::string, double> clients_;
				xdata::UnsignedInteger32 messagecount_;
				xdata::UnsignedInteger32 datacount_;
				xdata::UnsignedInteger32 lostmessagecount_;
				xdata::UnsignedInteger32 lostdatacount_;
				xdata::UnsignedInteger32 queueSize_;
				xdata::Vector<xdata::UnsignedInteger32> messages_;
				xdata::Vector<xdata::UnsignedInteger32> flashmessages_;
				xdata::Table components_;

				xdata::Vector<xdata::UnsignedInteger32> messagecounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> lostmessagecounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> datacounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> lostdatacounthisto_;
				xdata::Vector<xdata::UnsignedInteger32> queuehisto_;
			private:
				void actionPerformed (xdata::Event& e);
				void timeExpired (toolbox::task::TimerEvent& e);
		};
	}
}

#endif


