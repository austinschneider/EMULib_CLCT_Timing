/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _ws_broker_utils_Model_h_
#define _ws_broker_utils_Model_h_

#include <string>
#include <map>

#include "ws/broker/utils/InfoRecord.h"
#include "ws/broker/utils/exception/ParserException.h"

#include "xdata/InfoSpace.h"
#include "xdata/Table.h"

#include "toolbox/TimeVal.h"

//
// The following macro instantiates a ws-broker Model.
// An model class cannot have a namespace qualifier. The macro does not work in this case.
//
/*! The WS_BROKER_UTILS_MODEL_INSTANTIATOR macro needs to put this macro into the header file (.h) class declaration */
#define WS_BROKER_UTILS_MODEL_INSTANTIATOR() \
static ws::broker::utils::Model* instantiate(const std::string& name);

/*! the WS_BROKER_UTILS_MODEL_INSTANTIATOR_IMPL(ns1::ns2::...) macro needs to be put into the implementation file (.cc) of the ws-broker Model */
#define WS_BROKER_UTILS_MODEL_INSTANTIATOR_IMPL(QUALIFIED_CLASS_NAME) \
ws::broker::utils::Model * QUALIFIED_CLASS_NAME::instantiate(const std::string& name) \
{\
	return new QUALIFIED_CLASS_NAME(name);\
}

namespace ws 
{
namespace broker 
{
namespace utils 
{
	class Model
	{
		public:
			Model(const std::string& name);
			virtual ~Model();

			virtual void update(xdata::Table::Reference table) throw(ws::broker::utils::exception::ParserException) = 0;

			virtual std::list<xdata::Table::Reference> select(const ws::broker::utils::InfoRecord &info) = 0;

			virtual std::list<xdata::Table::Reference> get() = 0;

			virtual void cleanup(toolbox::TimeVal t) = 0;

			xdata::InfoSpace* getInfoSpace();
			std::string getName();
		private:
			xdata::InfoSpace infospace_;
			std::string name_;
	};
}
}
}
#endif

