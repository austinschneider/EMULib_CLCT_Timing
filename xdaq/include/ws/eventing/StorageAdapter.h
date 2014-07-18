// $Id: StorageAdapter.h,v 1.11 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_StorageAdapter_h_
#define _ws_eventing_StorageAdapter_h_

#include<list>
#include<vector>
#include<string>

#include "toolbox/net/UUID.h"
#include "xdata/Serializable.h"
#include "ws/eventing/ResourceDescriptor.h"
#include "ws/eventing/exception/NotFound.h"
#include "ws/eventing/exception/InvalidTopic.h"
#include "ws/eventing/exception/LimitExceeded.h"


namespace ws
{

namespace eventing
{

    class StorageAdapter
    {
    	public: 
	virtual ~StorageAdapter()
	{
	}

        //
	// basic
        //
	virtual ResourceDescriptor create(ResourceDescriptor& rd, xdata::Serializable* resource) 
		throw (ws::eventing::exception::LimitExceeded) = 0;
	
        virtual xdata::Serializable* get(ResourceDescriptor& rd) 
		throw (ws::eventing::exception::NotFound) = 0;
			
        virtual xdata::Serializable* remove(ResourceDescriptor& rd) 
		throw (ws::eventing::exception::NotFound) = 0;
	
	//
        // advanced methods
	//
        virtual std::list<xdata::Serializable*> get(const std::string& topic) 
		throw (ws::eventing::exception::InvalidTopic)= 0;
		
	virtual std::list<xdata::Serializable*> get() = 0;
	
        virtual std::list<xdata::Serializable*> remove(const std::string& topic) = 0;
	
        virtual xdata::Serializable* remove (toolbox::net::UUID& id) = 0; 
	
	virtual std::list<ResourceDescriptor> getResourceDescriptors(const std::string& topicPattern) 
		throw (ws::eventing::exception::InvalidTopic) = 0;
		
	virtual std::list<ResourceDescriptor> getResourceDescriptors() = 0;
	
        virtual ResourceDescriptor getResourceDescriptor(ResourceDescriptor& rd) 
		throw (ws::eventing::exception::NotFound) = 0;  

        virtual void expires(ResourceDescriptor& rd) throw (ws::eventing::exception::NotFound) = 0;   
	
	virtual void lock() = 0;
	
	virtual void unlock() = 0;
	
	/*
        virtual void put(ResourceDescriptor rd, xdata::Serializable* resource) = 0;
        virtual void createOrUpdate(ResourceDescriptor rd, xdata::Serializable* resource) = 0;
        virtual std::vector<ResourceDescriptor> getResourceDescriptors(ResourceDescriptor rd) = 0;  
    	*/
    };
}
}

#endif


