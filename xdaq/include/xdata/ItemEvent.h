// $Id: ItemEvent.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_ItemEvent_h_
#define _xdata_ItemEvent_h_

#include "xdata/Serializable.h"
#include "xdata/Event.h"
#include <string>

namespace xdata 
{

class Serializable;
class InfoSpace;

class ItemEvent: public xdata::Event
{
	public:
	
	/*! Constructor: Pass the \param type of this event, the \param name of the associated item,
	    the InfoSpace \param is with which it is associated. Optionally, the \param originator of this event may
	    be set.	
	*/
	ItemEvent(const std::string& type, const std::string& name, xdata::Serializable* item, xdata::InfoSpace* is, void* originator=0);
	
	/*! Return name name of the serializable associated with this event */
	std::string itemName();
	
	/*! Return a pointer to the serializable associated with this event */
	xdata::Serializable * item();
	
	/*! Return a pointer to the InfoSpace with which the item has been associated */
	xdata::InfoSpace* infoSpace();	
	
	protected:
	
		std::string itemName_;
		xdata::Serializable* item_;
		xdata::InfoSpace* infoSpace_;
};

class ItemAvailableEvent: public ItemEvent
{
	public:
		ItemAvailableEvent(const std::string& itemName, xdata::Serializable* item, xdata::InfoSpace* is, void* originator=0);
};

class ItemRevokedEvent: public ItemEvent
{
	public:
		ItemRevokedEvent( const std::string& itemName, xdata::Serializable* item, xdata::InfoSpace* is, void* originator=0);
};

class ItemChangedEvent: public ItemEvent
{
	public:
		ItemChangedEvent(const std::string& itemName, xdata::Serializable* item, xdata::InfoSpace* is, void* originator=0);
};

class ItemRetrieveEvent: public ItemEvent
{
	public:
		ItemRetrieveEvent(const std::string& itemName, xdata::Serializable* item, xdata::InfoSpace* is, void* originator=0);
};

}

#endif
