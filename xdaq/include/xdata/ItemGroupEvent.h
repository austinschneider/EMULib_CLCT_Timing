// $Id: ItemGroupEvent.h,v 1.2 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_ItemGroupEvent_h_
#define _xdata_ItemGroupEvent_h_

#include "xdata/Serializable.h"
#include "xdata/Event.h"
#include <string>
#include <map>

namespace xdata 
{

class Serializable;
class InfoSpace;

class ItemGroupEvent: public xdata::Event
{
	public:
	
	/*! Constructor: Pass the \param type of this event, the \param name of the associated item,
	    the InfoSpace \param is with which it is associated. Optionally, the \param originator of this event may
	    be set.	
	*/
	ItemGroupEvent(const std::string& type, xdata::InfoSpace* is, void* originator);
	
	void addItem (const std::string& name, xdata::Serializable* item);

	std::map<std::string, xdata::Serializable*>& getItems();
		
	/*! Return a pointer to the InfoSpace with which the item has been associated */
	xdata::InfoSpace* infoSpace();	
	
	protected:
	
		std::map<std::string, xdata::Serializable*> items_;
		xdata::InfoSpace* infoSpace_;
};


class ItemGroupChangedEvent: public ItemGroupEvent
{
	public:
		ItemGroupChangedEvent(xdata::InfoSpace* is, void* originator);
};

class ItemGroupRetrieveEvent: public ItemGroupEvent
{
	public:
		ItemGroupRetrieveEvent(xdata::InfoSpace* is, void* originator);
};

}

#endif
