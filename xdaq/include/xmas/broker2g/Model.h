/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_broker2g_Model_h_
#define _xmas_broker2g_Model_h_

#include <string>
#include <map>

#include "xmas/broker2g/exception/ParserException.h"

#include "xdaq/Object.h"

#include "xdata/InfoSpace.h"
#include "xdata/Properties.h"
#include "xdata/Table.h"
#include "xdata/Vector.h"
#include "xdata/UnsignedInteger32.h"

#include "toolbox/TimeVal.h"

#include "xgi/Output.h"

//
// The following macro instantiates a broker Model.
// An model class cannot have a namespace qualifier. The macro does not work in this case.
//
/*! The XMAS_BROKER2G_MODEL_INSTANTIATOR macro needs to put this macro into the header file (.h) class declaration */
#define XMAS_BROKER2G_MODEL_INSTANTIATOR() \
static xmas::broker2g::Model* instantiate(xdaq::Application * owner, const std::string& name);

/*! the XMAS_BROKER2G_MODEL_INSTANTIATOR_IMPL(ns1::ns2::...) macro needs to be put into the implementation file (.cc) of the broker Model */
#define XMAS_BROKER2G_MODEL_INSTANTIATOR_IMPL(QUALIFIED_CLASS_NAME) \
xmas::broker2g::Model * QUALIFIED_CLASS_NAME::instantiate(xdaq::Application * owner, const std::string& name) \
{\
	return new QUALIFIED_CLASS_NAME(owner, name);\
}

namespace xmas 
{
namespace broker2g 
{
	class Model :
		public xdaq::Object
	{
		public:
			Model(xdaq::Application * owner, const std::string& name);
			virtual ~Model();

			virtual void loaded() throw(xmas::broker2g::exception::ParserException) = 0;

			virtual void update(xdata::Table::Reference table) throw(xmas::broker2g::exception::ParserException) = 0;

			virtual xdata::Properties query(xdata::Properties& plist) = 0;

			virtual void cleanup(toolbox::TimeVal t) = 0;

			virtual void view(xgi::Output * out ) = 0;

			xdata::InfoSpace* getInfoSpace();
			std::string getName();
		private:
			xdata::InfoSpace infospace_;
			std::string name_;
	};
}
}
#endif

