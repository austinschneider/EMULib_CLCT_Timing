// $Id: MemoryStorageAdapter.h,v 1.12 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_MemoryStorageAdapter_h_
#define _ws_eventing_MemoryStorageAdapter_h_

#include<string>
#include<list>

#include "toolbox/Properties.h"
#include "toolbox/task/TimerEvent.h"
#include "toolbox/BSem.h"
#include "xdata/Serializable.h"
#include "ws/eventing/StorageAdapter.h"
#include "ws/eventing/ResourceDescriptor.h"
#include "ws/eventing/Subscription.h"
#include "ws/eventing/PersistedObject.h"
#include "ws/eventing/Storage.h"
#include "ws/eventing/exception/InvalidTopic.h"
#include "ws/eventing/exception/LimitExceeded.h"
#include "ws/eventing/exception/NotFound.h"
namespace ws
{
namespace eventing
{
    class MemoryStorageAdapter: public StorageAdapter
    {
	public:
	
        toolbox::Properties& getProperties();
	
        Storage& getStorage();
	
        MemoryStorageAdapter();
	
	virtual ~MemoryStorageAdapter() {}
	
        MemoryStorageAdapter(toolbox::Properties& config);
      
        ResourceDescriptor create(ResourceDescriptor& rd, xdata::Serializable * resource) 
		throw (ws::eventing::exception::LimitExceeded);

        xdata::Serializable * get(ResourceDescriptor& rd)  
		throw (ws::eventing::exception::NotFound);
	
        std::list<xdata::Serializable*> get(const std::string& topicPattern)
		throw (ws::eventing::exception::InvalidTopic);
		
	std::list<xdata::Serializable*> get();
	
	std::list<ResourceDescriptor> getResourceDescriptors(const std::string& topicPattern) 
		throw (ws::eventing::exception::InvalidTopic);
		
	std::list<ResourceDescriptor> getResourceDescriptors();
	
        xdata::Serializable* remove (toolbox::net::UUID& id)
		throw (ws::eventing::exception::NotFound);
	
        xdata::Serializable* remove(ResourceDescriptor& rd)
		throw (ws::eventing::exception::NotFound);
        
	std::list<xdata::Serializable*> remove(const std::string& topic)
		throw (ws::eventing::exception::InvalidTopic);
	
	// Takes a partially filled ResourceDescriptor object and
	// tries to find a matching ResourceDescriptor in the storage that it returns.
	// Throws an exception if no match is found
	//
	ResourceDescriptor getResourceDescriptor(ResourceDescriptor& rd) 
		throw (ws::eventing::exception::NotFound);

	
	// Not implemented
/*
        void put(ResourceDescriptor rd, xdata::Serializable * resource)
        {
            throw new NotImplementedException("Put");
        }

        void createOrUpdate(ResourceDescriptor rd, xdata::Serializer * resource) 
        {
            throw new NotImplementedException("CreateOrUpdate");
        }

        std::vector<ResourceDescriptor GetResourceDescriptors(ResourceDescriptor rd)
        {
            throw new NotImplementedException("GetResourceDescriptors");
        }
*/
        void expires(ResourceDescriptor& rd) throw (ws::eventing::exception::NotFound);

     
        void init();
	
	void lock();
	void unlock();
	
	protected:
	
	 
	std::string createStorageKeyword(ResourceDescriptor& rd, toolbox::Properties& properties);
	PersistedObject* getPersistedObject(ResourceDescriptor& rd) throw (ws::eventing::exception::NotFound);
	
	//public event EventHandler<ResourceDeletedEventArgs> ResourceDeleted;
	
	protected:	

        Storage storage_; // may be persistently serialized for recovery (post mortem)
        std::string strStorageName_;
        toolbox::Properties properties_;
        size_t maxNumberOfSubscriptions_;
	
	toolbox::BSem mutex_;
    };
}

}

#endif


