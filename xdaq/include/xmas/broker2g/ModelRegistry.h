/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_ModelRegistry_h_
#define _xmas_broker2g_ModelRegistry_h_

#include <string>
#include <map>

#include "xmas/broker2g/Model.h"
#include "xmas/broker2g/exception/ParserException.h"
#include "xmas/broker2g/exception/ModelNotFoundException.h"

#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"

#include "xdaq/Application.h"
#include "xdaq/exception/Exception.h"

#include "toolbox/BSem.h"
#include "toolbox/task/Timer.h"
#include "toolbox/task/TimerFactory.h"
#include "toolbox/TimeInterval.h"

namespace xmas
{
namespace broker2g
{
	class ModelRegistry :
		public xdaq::Object,
		public toolbox::task::TimerListener
	{
		public:
			ModelRegistry(xdaq::Application * owner, toolbox::TimeInterval& interval, const std::string & autoloadpath) throw (xmas::broker2g::exception::ParserException);
			virtual ~ModelRegistry();

			void update(xdata::Table::Reference table);
			std::map<std::string, xmas::broker2g::Model*> getModels();

			xdata::Properties query(xdata::Properties& plist) throw (xmas::broker2g::exception::ModelNotFoundException);
//			std::list<xdata::Table::Reference> get(const std::string &name) throw (xmas::broker2g::exception::ModelNotFoundException);
			virtual void view(const std::string& name, xgi::Output * out );
		protected:
			void getProperties(DOMNode *modelNode, xdata::InfoSpace *is) throw (xmas::broker2g::exception::ParserException);

			void timeExpired (toolbox::task::TimerEvent& e);

			std::map<std::string, xmas::broker2g::Model*> models_;

			toolbox::BSem mutex_;
			toolbox::TimeInterval interval_;
	};
}
}
#endif

