/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_ModelRegistry_h_
#define _ws_broker_utils_ModelRegistry_h_

#include <string>
#include <map>

#include "ws/broker/utils/Model.h"
#include "ws/broker/utils/exception/ParserException.h"
#include "ws/broker/utils/exception/ProfileNotFoundException.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "ws/addressing/EndpointReference.h"

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"

#include "xdaq/Application.h"
#include "xdaq/exception/Exception.h"

#include "toolbox/BSem.h"
#include "toolbox/task/Timer.h"
#include "toolbox/task/TimerFactory.h"
#include "toolbox/TimeInterval.h"

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class ModelRegistry :
		public toolbox::task::TimerListener
	{
		public:
			ModelRegistry(xdaq::Application& app, toolbox::TimeInterval& interval) throw (ws::broker::utils::exception::ParserException);
			virtual ~ModelRegistry();

			void update(xdata::Table::Reference table);
			std::map<std::string, ws::broker::utils::Model*> getModels();
			std::list<xdata::Table::Reference> select(const ws::broker::utils::InfoRecord &info) throw (ws::broker::utils::exception::ProfileNotFoundException);
			std::list<xdata::Table::Reference> get(const std::string &name) throw (ws::broker::utils::exception::ProfileNotFoundException);
		protected:
			DOMDocument* loadDOM( const std::string& pathname) throw (ws::broker::utils::exception::ParserException);
			void getProperties(DOMNode *modelNode, xdata::InfoSpace *is) throw (ws::broker::utils::exception::ParserException);

			void timeExpired (toolbox::task::TimerEvent& e);

			std::map<std::string, ws::broker::utils::Model*> models_;
			xdaq::Application& app_;

			toolbox::BSem mutex_;
			toolbox::TimeInterval interval_;
	};
}
}
}
#endif

