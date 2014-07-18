// $Id: ResourceDescriptor.h,v 1.6 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_ResourceDescriptor_h_
#define _ws_eventing_ResourceDescriptor_h_

#include "toolbox/TimeVal.h"
#include "toolbox/net/UUID.h"

namespace ws
{
namespace eventing
{
    class ResourceDescriptor
    {
	public:

	// ResourceDescriptor();

	ResourceDescriptor(toolbox::net::UUID& id);
        
	ResourceDescriptor(toolbox::net::UUID& id, toolbox::TimeVal& expires);

	// Copy CTOR
	ResourceDescriptor(const ResourceDescriptor& rd);

	toolbox::net::UUID& getId();

	void setId(toolbox::net::UUID& id);

	std::string& getName();

	void setName(const std::string& value);

	std::string& getKey();

	void setKey (const std::string& value);

	std::string& getTopic();

	void setTopic (const std::string& value);

	toolbox::TimeVal& getExpires();

	void setExpires (toolbox::TimeVal& value);

	toolbox::TimeVal& getCreated();

	void setCreated(toolbox::TimeVal& value);

	toolbox::TimeVal& getUpdated();

	void setUpdated(toolbox::TimeVal& value);

	protected:

	toolbox::net::UUID id_;
	std::string name_;
	std::string key_;
	std::string topic_;
	toolbox::TimeVal expires_;
	toolbox::TimeVal created_;
	toolbox::TimeVal updated_;
    };
}
}

#endif


